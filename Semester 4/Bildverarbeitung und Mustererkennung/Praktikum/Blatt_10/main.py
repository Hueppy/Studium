import math

import cv2
import numpy as np

MAX_ITER = 10
MIN_VALUE = 0
MAX_VALUE = 255


def kmeans(img, k):
    """Applies k-means clustering to supplied image with k-clusters"""
    height = img.shape[0]
    width = img.shape[1]
    channels = 1

    if len(img.shape) == 3:
        channels = img.shape[2]

    # generate random cluster
    cluster = np.random.randint(MIN_VALUE, MAX_VALUE, (k, channels))

    r = None
    for i in range(MAX_ITER):
        r = np.zeros((height, width, k))
        # E-Step
        for y in range(height):
            for x in range(width):
                d = np.sqrt(np.sum((img[y, x] - cluster) ** 2, axis=1))
                r[y, x, np.argmin(d)] = 1

        # M-Step
        for j in range(k):
            sum = np.sum(r[:, :, j])
            if sum:
                if channels == 1:
                    cluster[j] = np.sum(r[:, :, j] * img[:, :]) / sum
                else:
                    for c in range(channels):
                        cluster[j, c] = np.sum(r[:, :, j] * img[:, :, c]) / sum

        print('Done: ', i + 1, ' / ', MAX_ITER)

    # apply clustering to image
    clustering = np.zeros(img.shape, np.uint8)
    for y in range(height):
        for x in range(width):
            for j in range(k):
                if r[y, x, j] > 0:
                    clustering[y, x] = cluster[j]

    return clustering


def main():
    # load image
    img = cv2.imread("p10_testbild.jpg")

    for k in [2, 4]:
        # apply clustering to color image
        clustering_color = kmeans(img, k)
        cv2.imshow("Color image", clustering_color)
        cv2.waitKey()
        cv2.destroyAllWindows()

        # convert color image to grayscale
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # apply clustering to grayscale image
        clustering_gray = kmeans(gray, k)
        cv2.imshow("Grayscale image", clustering_gray)
        cv2.waitKey()
        cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
