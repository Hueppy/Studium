import cv2
import numpy as np

REGION = 15
FULL_ROTATION = 360
SAMPLES = 100
THRESHOLD = 0.4

CENT_1_MIN = 23
CENT_1_MAX = 25
CENT_2_MIN = 27
CENT_2_MAX = 29
CENT_5_MIN = 31
CENT_5_MAX = 33


def get_max_index(a):
    """Get indices of maxima in array"""
    return np.unravel_index(np.argmax(a), a.shape)


def hough_circles(edges, rmin, rmax):
    """Apply hough transformation for circles"""
    (height, width) = edges.shape
    # initialize accumulator
    accumulator = np.zeros((rmax - rmin, height + 2 * rmax, width + 2 * rmax))

    # for each possible radius...
    for r in range(rmin, rmax):
        # ... compute each angle
        angles = np.radians(np.arange(0, FULL_ROTATION, FULL_ROTATION / SAMPLES))
        # ... compute x and y coordinates for each angle
        circle = np.column_stack((r * np.sin(angles),
                                  r * np.cos(angles))).astype(np.int8)

        rl, rh = r - rmax + 1, r + rmax + 1
        # for each edge ...
        for y, x in np.argwhere(edges):
            # ... and point in circle ...
            for [cy, cx] in circle:
                # ... increment accumulator at center of suspected circle
                accumulator[r - rmin, y - cy, x - cx] += 1

    detected = list()
    # find maxima
    r, y, x = get_max_index(accumulator)
    while accumulator[r, y, x] > THRESHOLD * SAMPLES:
        radius = r + rmin
        detected.append((radius, y, x))
        # remove surrounding values
        accumulator[:, y-radius:y+radius, x-radius:x+radius] = 0
        # get next maxima
        r, y, x = get_max_index(accumulator)

    return detected


def main():
    # load image
    img = cv2.imread("p08_muenzen.png")
    # apply gauss filter
    gauss = cv2.GaussianBlur(img, (3, 3), 2)
    # apply canny edge detector
    edges = cv2.Canny(gauss, 100, 200)

    # find circles
    circles = hough_circles(edges, 20, 40)
    sum = 0
    for (r, y, x) in circles:
        color = (0, 0, 0)
        # categorize circle
        if CENT_1_MIN <= r <= CENT_1_MAX:
            color = (255, 0, 0)
            sum += 1
        elif CENT_2_MIN <= r <= CENT_2_MAX:
            color = (0, 255, 0)
            sum += 2
        elif CENT_5_MIN <= r <= CENT_5_MAX:
            color = (0, 0, 255)
            sum += 5

        # draw circle
        cv2.circle(img, (x, y), r, color)
        # draw center marker
        cv2.drawMarker(img, (x, y), (255, 255, 255))

    # output total
    print("Total value:", sum, "ct")

    # display image
    cv2.imshow("Output", img)
    cv2.waitKey()


if __name__ == "__main__":
    main()
