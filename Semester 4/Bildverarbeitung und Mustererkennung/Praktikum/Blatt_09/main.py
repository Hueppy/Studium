import math

import cv2
import numpy as np
import matplotlib.pyplot as plt


ALPHAS = np.deg2rad([0, 45, 90, 135])
DISTANCE = 1
VALUE_RANGE = 256

IMG_COUNT = 15

PERCENTAGES = np.array([0.2, 0.4, 0.8])


def calculate_cooccurrence(img, alpha):
    """calculate co-occurrence matrix of supplied image with angle alpha and distance = 1"""
    (height, width) = img.shape

    # calculate offset of neighbor
    noff_x = math.ceil(math.cos(alpha) * DISTANCE)
    noff_y = -math.ceil(math.sin(alpha) * DISTANCE)

    # create output matrix
    cooccurrence = np.zeros((VALUE_RANGE, VALUE_RANGE))

    for y in range(-noff_y, height):
        for x in range(0, width - noff_x):
            # get pixel and neighbor value
            value = img[y, x]
            neighbor = img[y + noff_y, x + noff_x]

            # increment co-occurrence value
            cooccurrence[value, neighbor] += 1

    return cooccurrence / np.sum(cooccurrence)


def contrast(cooccurrence):
    """Calculate contrast texture measure"""
    (k, _) = cooccurrence.shape

    contrast = 0
    for i in range(k):
        for j in range(k):
            contrast += (i - j) ** 2 * cooccurrence[i, j]

    return contrast


def entropy(cooccurrence):
    """Calculate entropy texture measure"""
    (k, _) = cooccurrence.shape

    entropy = 0
    for i in range(k):
        for j in range(k):
            if cooccurrence[i, j] != 0:
                entropy += cooccurrence[i, j] * math.log10(cooccurrence[i, j])
    entropy *= -1

    return entropy


def homogeneity(cooccurrence):
    """Calculate homogeneity texture measure"""
    (k, _) = cooccurrence.shape

    homogeneity = 0
    for i in range(k):
        for j in range(k):
            homogeneity += cooccurrence[i, j] / (1 + math.fabs(i - j))

    return homogeneity


def aufgabe_1():
    # load images
    imgs = [
        cv2.imread('p09_teil1_gras.jpg', cv2.IMREAD_GRAYSCALE),
        cv2.imread('p09_teil1_ziegel.jpg', cv2.IMREAD_GRAYSCALE)
    ]

    for img in imgs:
        for alpha in ALPHAS:
            # calculate co-occurrence matrix
            cooccurrence = calculate_cooccurrence(img, alpha)

            # print texture measures
            print("Kontrast:", contrast(cooccurrence))
            print("Entropie:", entropy(cooccurrence))
            print("Homogenität:", homogeneity(cooccurrence))
            print()

            # show coocurrence
            cv2.imshow("Co-occurence", cooccurrence / np.max(cooccurrence))
            cv2.waitKey()


def aufgabe_2():
    # load images
    imgs = np.array([cv2.imread(f'{i}.jpg', cv2.IMREAD_GRAYSCALE) for i in range(IMG_COUNT)])
    (n, height, width) = imgs.shape

    # calculate mean image
    avg = np.average(imgs, axis=0).astype(np.uint8)

    # redistribute images around 0
    normalized = np.array([img - avg for img in imgs])

    # horizontally concat all images
    concat = cv2.hconcat(normalized.reshape((n, height * width)))

    # calculate covariance matrix
    covariance = np.matmul(concat, np.transpose(concat))

    # calculate eigenvalues and eigenvectors
    _, s, vh = np.linalg.svd(covariance)

    # sort eigenvectors by eigenvalues
    vh = vh[np.argsort(-s)]
    (components, _) = vh.shape

    # load test image
    test_img = cv2.imread('test.jpg', cv2.IMREAD_GRAYSCALE)
    test_img = test_img.reshape((height * width, 1))
    for n in (PERCENTAGES * components).astype(np.uint16):
        # get subset of eigenvectors
        subset = vh[:n, :]

        # reduce image using subset of eigenvectors
        reduced = np.matmul(subset, test_img)

        # reconstruct image using subset of eigenvectors
        reconstructed = np.matmul(subset.transpose(), reduced)

        # reshape and normalize reconstructed image
        reconstructed = reconstructed.reshape((height, width))
        reconstructed += avg
        reconstructed += np.min(reconstructed)
        reconstructed /= np.max(reconstructed)

        # show reconstructed image
        cv2.imshow("Rekonstruiert", reconstructed)
        cv2.waitKey()


def main():
    aufgabe_1()
    aufgabe_2()


if __name__ == "__main__":
    main()
