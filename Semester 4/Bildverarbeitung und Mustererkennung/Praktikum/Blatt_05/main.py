from math import floor, sqrt, e, atan, degrees, isnan
from collections import defaultdict

import cv2
import numpy as np

INPUT_WINDOW_NAME = "Seed selection"
OUTPUT_WINDOW_NAME = "Region growing"

HIST_SIZE = 256
THRESH_HIGH = 255

VISITED = 255
GRAY_VARIANCE = 15


def histogram(img):
    """Calculate histogram of supplied grayscale image"""
    # initialize new histogram
    hist = np.zeros((HIST_SIZE))

    # go through each pixel
    for row in img:
        for point in row:
            # increment value of point in histogram
            hist[point] += 1

    return hist


def sums(hist, thresh):
    """Calulates the sums of the values of the supplied histogram left and right of the threshold"""
    return sum(hist[:thresh]), sum(hist[thresh+1:])


def medians(whist, thresh, n1, n2):
    """Calculate median values of the supplied weighted histogram left and right of the threshold"""
    # initialize medians
    mu1 = 0
    mu2 = 0

    # if there are no pixel on either side of threshold the specific median should be zero
    if n1 > 0:
        mu1 = sum(whist[:thresh]) / n1
    if n2 > 0:
        mu2 = sum(whist[thresh+1:]) / n2

    return mu1, mu2


def variance(factor, n1, n2, mu1, mu2):
    """Calculate variance of threshold using precalculated values"""
    return factor * n1 * n2 * (mu1 - mu2) ** 2


def otsu(img):
    """Determines optimal threshold of image using Otsu's method """
    # calculate histogram
    hist = histogram(img)
    # calculate weighted histogram
    whist = [i * h for (i, h) in enumerate(hist)]
    # calculate factor (inverse of the sum of pixels squared)
    factor = 1 / sum(hist) ** 2

    # initialize variances array
    variances = np.zeros((len(hist)))
    for t in range(len(hist)):
        # calculate sums
        (n1, n2) = sums(hist, t)
        # calculate medians
        (mu1, mu2) = medians(whist, t, n1, n2)

        # calculate variance using sums and medians and add to array
        variances[t] = variance(factor, n1, n2, mu1, mu2)

    # return index of max value
    return variances.argmax()


def thresh(img, thresh):
    """Thresholds supplied image using supplied threshold value"""
    (height, width) = img.shape
    # initialize output image
    result = np.zeros((height, width))

    # go through each pixel in input image
    for y in range(height):
        for x in range(width):
            # if value in input image is below threshold, set output value to threshold high
            if img[y, x] < thresh:
                result[y, x] = THRESH_HIGH

    return result


def aufgabe_1(img):
    # calculate optimal threshold
    t = otsu(img)
    # threshold image
    output = thresh(img, t)

    # display output
    cv2.imshow("Otsu threshold", output)
    cv2.waitKey()


def region_growth(input, x, y):
    """Grows the region around seed pixel based on the variance to the seed"""
    (height, width) = input.shape

    # get seed value
    seed_value = input[y, x]

    # create output image
    output = np.zeros((height, width))
    # set seed in output to be visited
    output[y, x] = VISITED

    # until nothing has changed in output
    changed = True
    while changed:
        changed = False

        # go through each pixel
        for y in range(height):
            for x in range(width):
                # if pixel is part of region
                if output[y, x] == VISITED:
                    neighbors = [
                        (x - 1, y - 1),
                        (x, y - 1),
                        (x + 1, y - 1),
                        (x - 1, y),
                        (x + 1, y),
                        (x - 1, y + 1),
                        (x, y + 1),
                        (x + 1, y + 1)
                    ]

                    # visited the 8 surrounding neighbor pixels
                    for (nx, ny) in neighbors:
                        # if neighbor pixel is in image
                        if 0 < nx < width and 0 < ny < height:
                            # and it has not been visisted and it's value is within specified variance
                            if output[ny, nx] != VISITED and seed_value - GRAY_VARIANCE < input[ny, nx] < seed_value + GRAY_VARIANCE:
                                # set output to be visited
                                output[ny, nx] = VISITED
                                # mark output as changed
                                changed = True

    return output


def aufgabe_2(img):
    def mouse_callback(event, x, y, flags, data):
        """Callback for cv2 mouse event"""
        # left click
        if event == cv2.EVENT_LBUTTONDOWN:
            # grow region around clicked pixel
            img_out = region_growth(img, x, y)

            # display output
            cv2.imshow(OUTPUT_WINDOW_NAME, img_out)
            cv2.waitKey()
            cv2.destroyWindow(OUTPUT_WINDOW_NAME)

    # show image
    cv2.namedWindow(INPUT_WINDOW_NAME)
    cv2.setMouseCallback(INPUT_WINDOW_NAME, mouse_callback)
    cv2.imshow(INPUT_WINDOW_NAME, img)
    cv2.waitKey()


def main():
    img = cv2.imread("p05_gummibaeren.png", cv2.IMREAD_GRAYSCALE)

    aufgabe_1(img)
    aufgabe_2(img)


if __name__ == "__main__":
    main()
