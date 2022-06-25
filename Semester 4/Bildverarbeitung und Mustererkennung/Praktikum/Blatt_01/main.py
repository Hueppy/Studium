import cv2
import numpy as np


def rgb_to_yuv(r, g, b):
    """Converts supplied RGB value to YUV and returns it as a tuple"""
    r = r / 255
    g = g / 255
    b = b / 255
    y = 0.299 * r + 0.587 * g + 0.114 * b
    u = 0.493 * (b - y)
    v = 0.877 * (r - y)
    return y, u, v


def bgr_to_yuv(b, g, r):
    """Converts supplied BGR value to YUV and returns it as a tuple"""
    return rgb_to_yuv(r, g, b)


def average(list):
    """Calculates arithmetic mean of supplied list"""
    return sum(list) / len(list)


def threshold(list, high):
    """Calculates the threshold of the image supplied as 2-dimensional list"""
    flat = [point for row in list for point in row]
    avg = average(flat)
    std = average([x * x for x in flat]) - avg * avg

    if high:
        t = 255
        f = 0
    else:
        t = 0
        f = 255
        std = -std

    return [[t if point > avg + std else f for point in row] for row in list]


def main():
    # Load image
    img = cv2.imread("praktikum_01_schatten.jpg")
    # Convert each pixel in image to its yuv representation
    yuv = [[bgr_to_yuv(*point) for point in row] for row in img]

    # Strip each channel from yuv representation
    y = [[y for (y, _, _) in row] for row in yuv]
    u = [[u for (_, u, _) in row] for row in yuv]
    v = [[v for (_, _, v) in row] for row in yuv]

    # Display each channel
    cv2.imshow("Y-Kanal", np.array(y))
    cv2.waitKey()
    cv2.imshow("U-Kanal", np.array(u))
    cv2.waitKey()
    cv2.imshow("V-Kanal", np.array(v))
    cv2.waitKey()

    # Calculate threshold of u and v
    t1 = threshold(u, True)
    t2 = threshold(v, False)
    # Calculate shadowmap by multiplying each threshold value
    s = [[x * y for (x, y) in zip(r1, r2)] for (r1, r2) in zip(t1, t2)]

    # Display threshold and shadowmap
    cv2.imshow("Threshold 1", np.array(t1, np.uint8))
    cv2.waitKey()
    cv2.imshow("Threshold 2", np.array(t2, np.uint8))
    cv2.waitKey()
    cv2.imshow("Schattenregion", np.array(s, np.uint16))
    cv2.waitKey()


if __name__ == "__main__":
    main()