from math import floor, sqrt, e, atan, degrees, isnan

import cv2
import numpy as np

# angles for 8 different directions
SLICE = 45
HALF_SLICE = SLICE / 2
SOUTH = 0
SOUTHEAST = 1
EAST = 2
NORTHEAST = 3
NORTH = 4
NORTHWEST = 5
WEST = 6
SOUTHWEST = 7


def generate_gauss_mask(sigma, n):
    """Returns gauss kernel of size (2n+1)^2"""
    size = 2 * n + 1
    half = floor(size / 2)
    # generate 1d coefficients using standard distribution function
    coeff = [e ** -((x - half) ** 2 / (2 * sigma ** 2)) / sqrt(2 * sigma ** 2) for x in range(size)]

    # normalize all values, so their sum will be 1
    factor = sum(coeff)
    normalized = [x / factor for x in coeff]

    # multiply normalized values with itself resulting in 2d kernel
    return np.array([[x * y for x in normalized] for y in normalized])


def detect_edges(img):
    """Returns gradient value and direction, calculated using sobel filter"""
    # Step a. apply sobel filter
    sobel_mask_x = np.array([
        [-1, 0, 1],
        [-2, 0, 2],
        [-1, 0, 1]
    ])
    sobel_mask_y = np.array([
        [-1, -2, -1],
        [0, 0, 0],
        [1, 2, 1]
    ])
    filter_x = cv2.filter2D(img, -1, sobel_mask_x)
    filter_y = cv2.filter2D(img, -1, sobel_mask_y)

    # Step b. calculate gradient value and direction
    gradient_value = np.array(
        [[sqrt(x[0] ** 2 + y[0] ** 2) for (x, y) in zip(rx, ry)] for (rx, ry) in zip(filter_x, filter_y)])
    gradient_direction = np.array(
        [[atan(y[0] / x[0]) for (x, y) in zip(rx, ry)] for (rx, ry) in zip(filter_x, filter_y)])

    return gradient_value, gradient_direction


def suppress_gradient(value, direction):
    """Applies non maxima suppression to supplied gradient"""
    (width, height) = value.shape

    # create new array of size width * height with all elements initialized as 0
    suppressed = np.zeros((width, height), np.uint8)
    for y in range(height):
        for x in range(width):
            neighbor_max = 0

            # NaN direction means no gradiant at position
            if not isnan(direction[x, y]):
                # divide direction into 8 possible values
                slice_direction = floor((degrees(direction[x, y]) + HALF_SLICE) / SLICE)

                # get larger value from neighbors in gradient direction
                if slice_direction == SOUTH or slice_direction == NORTH:
                    if y > 0:
                        neighbor_max = max(neighbor_max, value[x, y - 1])
                    if y < height - 1:
                        neighbor_max = max(neighbor_max, value[x, y + 1])
                elif slice_direction == SOUTHEAST or slice_direction == NORTHWEST:
                    if x > 0 and y > 0:
                        neighbor_max = max(neighbor_max, value[x - 1, y - 1])
                    if x < width - 1 and y < height - 1:
                        neighbor_max = max(neighbor_max, value[x + 1, y + 1])
                elif slice_direction == EAST or slice_direction == WEST:
                    if x > 0:
                        neighbor_max = max(neighbor_max, value[x - 1, y])
                    if x < width - 1:
                        neighbor_max = max(neighbor_max, value[x + 1, y])
                elif slice_direction == NORTHEAST or slice_direction == SOUTHWEST:
                    if x < width - 1 and y > 0:
                        neighbor_max = max(neighbor_max, value[x + 1, y - 1])
                    if x > 0 and y < height - 1:
                        neighbor_max = max(neighbor_max, value[x - 1, y + 1])

            # only set value if the current value is greater than the neighbors
            if value[x, y] > neighbor_max:
                suppressed[x, y] = floor(value[x, y])

    return suppressed


def hysteresis(value, low, high):
    """Applies hysteresis to supplied (suppressed) gradient, with supplied threshold values"""
    (width, height) = value.shape

    # resulting values
    MIN = 0
    MAX = 255

    # copy gradient values
    hysteresis_value = np.array(value, np.uint8)
    changed = True
    while changed:
        # repeat until no value has been changed
        changed = False

        for y in range(height):
            for x in range(width):
                if hysteresis_value[x, y] > high:
                    # look at all values that are greater than high threshold
                    if hysteresis_value[x, y] < MAX:
                        # if value is less than the max result, set it to max
                        hysteresis_value[x, y] = MAX
                        changed = True

                    # look at each neighbor, if the neighbor is between low and high, set them to max
                    if x > 0 and low < hysteresis_value[x - 1, y] < high:
                        # left neighbor
                        hysteresis_value[x - 1, y] = MAX
                        changed = True
                    if x < width - 1 and low < hysteresis_value[x + 1, y] < high:
                        # right neighbor
                        hysteresis_value[x + 1, y] = MAX
                        changed = True
                    if y > 0 and low < hysteresis_value[x, y - 1] < high:
                        # top neighbor
                        hysteresis_value[x, y - 1] = MAX
                        changed = True
                    if y < height - 1 and low < hysteresis_value[x, y + 1] < high:
                        # bottom neighbor
                        hysteresis_value[x, y + 1] = MAX
                        changed = True
                    if x > 0 and y > 0 and low < hysteresis_value[x - 1, y - 1] < high:
                        # top left neighbor
                        hysteresis_value[x - 1, y - 1] = MAX
                        changed = True
                    if x < width - 1 and y > 0 and low < hysteresis_value[x + 1, y - 1] < high:
                        # top right neighbor
                        hysteresis_value[x + 1, y - 1] = MAX
                        changed = True
                    if x > 0 and y < height - 1 and low < hysteresis_value[x - 1, y + 1] < high:
                        # bottom left neighbor
                        hysteresis_value[x - 1, y + 1] = MAX
                        changed = True
                    if x < width - 1 and y < height - 1 and low < hysteresis_value[x + 1, y + 1] < high:
                        # bottom right neighbor
                        hysteresis_value[x + 1, y + 1] = MAX
                        changed = True

    # filter out remaining values between low and high
    for y in range(height):
        for x in range(width):
            if low < hysteresis_value[x, y] < high:
                hysteresis_value[x, y] = MIN

    return hysteresis_value


def main():
    img = cv2.imread("p04_apfelbaum.png")
    (width, height, _) = img.shape

    # Step 1. filter using a gauss filter
    gauss_mask = generate_gauss_mask(0.5, 1)
    gauss_filtered = cv2.filter2D(img, -1, gauss_mask)

    cv2.imshow("Gauss 0.5 3x3", gauss_filtered)
    cv2.waitKey()

    # Step 2. detect edges in x and y direction using sobel filter
    (gradient_value, gradient_direction) = detect_edges(gauss_filtered)

    cv2.imshow("Sobel value 3x3", np.array(gradient_value, np.uint8))
    cv2.waitKey()
    cv2.imshow("Sobel direction 3x3", gradient_direction)
    cv2.waitKey()

    # Step 3. thin edges using non maxima suppression
    supressed_value = suppress_gradient(gradient_value, gradient_direction)

    cv2.imshow("Non maximal suppression", supressed_value)
    cv2.waitKey()

    # Step 4. apply hysteresis
    hysteresis_value = hysteresis(supressed_value, 50, 100)
    cv2.imshow("Hysteresis", hysteresis_value)
    cv2.waitKey()


if __name__ == "__main__":
    main()
