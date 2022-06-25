from math import floor, ceil

import cv2
import numpy as np


def generate_average_mask(n):
    """Generates a new matrix of size (2n + 1)^2, where each element is 1 / (2n + 1)^2"""
    size = 2 * n + 1
    element = 1 / (size * size)
    return np.array([[element for _ in range(size)] for _ in range(size)])


def generate_binominal_mask(n):
    """Generates a binominal mask of size (2n + 1)^2"""
    # first we need to generate a 1d mask of size (2n + 1)
    # the order p will be 2 * n, since the result of the function is a vector of size (p + 1)
    p = 2 * n
    first_dim = (np.poly1d([0.5, 0.5]) ** p).coeffs

    # next we need to multiply the vector with itself, the result will be a matrix
    second_dim = [[row * column for column in first_dim] for row in first_dim]
    return np.array(second_dim)


def calculate_elementwise_product(a, b):
    """Calculates a new matrix, where each element is the product of the corresponding values of a and b"""
    n = len(a)
    return [[a[x, y] * b[x, y] for x in range(n)] for y in range(n)]


def calculate_linear_filter(clip, mask):
    """Calculates the inner product of the supplied clip mask"""
    product = calculate_elementwise_product(clip, mask)
    return sum([sum(row) for row in product])


def apply_linear_filter(img, mask):
    """Applies a linear filter to the supplied image with the supplied mask"""
    (width, height, _) = img.shape
    n = len(mask)

    return \
        [
            [
                calculate_linear_filter(img[x:x + n, y:y + n], mask) for x in range(width - n + 1)
            ] for y in range(height - n + 1)
        ]


def flatten(a):
    """Flattens a two dimensional array so [[1, 2], [3, 4]] is converted to [1, 2, 3, 4]"""
    return [value for row in a for value in row]


def calculate_median(a):
    """Calculates the median from a two dimensional array"""
    flat = sorted(flatten(a))
    n = len(flat)
    index = floor(n / 2)
    if n % 2 == 0:
        # Even number of elements, return average of middle elements
        return floor(flat[index] / 2 + flat[index + 1] / 2)
    else:
        # Odd number of elements, return middle element
        return flat[index]


def calculate_median_filter(clip, weights):
    product = calculate_elementwise_product(clip, weights)
    return calculate_median(product)


def apply_median_filter(img, weights):
    (width, height, _) = img.shape
    n = len(weights)

    return \
        [
            [
                calculate_median_filter(img[x:x + n, y:y + n, 0:1], weights) for x in range(width - n + 1)
            ] for y in range(height - n + 1)
        ]


def filter_average(img, n):
    mask = generate_average_mask(n)
    return np.array(apply_linear_filter(img, mask), np.uint8)


def filter_binominal(img, n):
    mask = generate_binominal_mask(n)
    return np.array(apply_linear_filter(img, mask), np.uint8)


def aufgabe_1(img):
    # calculate average filter for n = 1
    average_result_1 = filter_average(img, 1)

    # calculate average filter for n = 3
    average_result_3 = filter_average(img, 3)

    # calculate binominal filter for n = 1
    binominal_result_1 = filter_binominal(img, 1)

    # calculate binominal filter for n = 2
    binominal_result_2 = filter_binominal(img, 2)

    # show results
    cv2.imshow("Mittelwert N=1", average_result_1)
    cv2.waitKey()
    cv2.imshow("Mittelwert N=3", average_result_3)
    cv2.waitKey()
    cv2.imshow("Gauss N=1", binominal_result_1)
    cv2.waitKey()
    cv2.imshow("Gauss N=2", binominal_result_2)
    cv2.waitKey()


def aufgabe_2(img):
    n = 1
    size = 2 * n + 1
    # get identity weight matrix
    weights = np.ones((size, size), np.uint8)
    # calculate median filter with weights
    result = np.array(apply_median_filter(img, weights), np.uint8)

    # show results
    cv2.imshow("Median N=1", result)
    cv2.waitKey()


def main():
    img = cv2.imread("p03_nilpferd.jpg")
    aufgabe_1(img)
    aufgabe_2(img)


if __name__ == "__main__":
    main()
