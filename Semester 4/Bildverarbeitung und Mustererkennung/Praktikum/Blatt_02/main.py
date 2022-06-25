from random import random

import cv2
import numpy as np
import matplotlib.pyplot as plt

def get_tile(img, n):
    """Copies a random section of size n*n out of the supplied image"""
    (width, height, _) = img.shape
    # Pick random origin coordinates for our tile image.
    # Coordinates are calculated as follows:
    # random() * (len(dim) - n)
    # First we subtract n from the length of the specified dimension,
    # so the coordinate origin + n - 1 is inside the image.
    # Next we call the random function, which returns a random floating point number between 0 and 1,
    # and multiply its result with the last result.
    x = int(random() * (width - n))
    y = int(random() * (height - n))

    # Copy section of image starting at x and y with size n*n
    return np.array([[img[x + j, y + i] for j in range(n)] for i in range(n)])


def create_tile_img(img, pattern, n):
    """Copies the supplied image and adds interleaved tiles of the supplied pattern image of size n*n"""
    (width, height, _) = img.shape
    # Copy image
    tile_img = np.copy(img)

    # The image is sliced in blocks of size (2*n)^2,
    # the origin of the block (top left corner) will be replaced with a random tile

    # Go through each line of blocks
    for i in range(int(height / (2 * n))):
        # Go through each block in line
        for j in range(int(width / (2 * n))):
            # Calculate origin coordinates
            x = j * 2 * n
            y = i * 2 * n

            # Generate a random tile from the supplied pattern image
            tile = get_tile(pattern, n)
            # Go through each row in the tile image
            for k in range(n):
                # Go through each pixel in the tile image
                for l in range(n):
                    # Copy value from tile image to the result image
                    tile_img[x + l, y + k] = tile[l, k]

    # Return the result image
    return tile_img


def aufgabe_1(n):
    # Load images
    img = cv2.imread("p02_teil1_minden.jpg")
    pattern = cv2.imread("p02_teil1_sonne.jpg")

    # Create tile image
    tile_img = create_tile_img(img, pattern, n)
    cv2.imshow("Tile", tile_img)
    cv2.waitKey()


def calculate_hist(img):
    """Calculate histogram of supplied grayscale image"""
    # Create array with 256 elements of value 0
    hist = np.zeros(256)

    # Go through each row in image
    for row in img:
        # Go through each pixel in image
        for pixel in row:
            # Increment histogram value at pixel value position
            hist[pixel] += 1

    # Return resulting histogram
    return hist


def cumulate_hist(hist):
    """Calculate cumulative histogram of supplied histogram"""
    # Create array with the same number of elements as the histogram with value 0
    cumulative_hist = np.zeros(len(hist), np.uint32)

    accumulator = 0
    for i in range(len(hist)):
        # add each histogram value to accumulator
        accumulator += hist[i]
        # assign current accumulator value to cumulative histogram
        cumulative_hist[i] = accumulator

    return cumulative_hist


def get_mapping(cumulative_hist, mn):
    """Returns an anonymous function of type f -> Number -> Number that maps the passed value to linearize the image"""
    k = len(cumulative_hist)
    return lambda i: cumulative_hist[i] * ((k - 1) / mn)


def show_hist(hist):
    """Helper function to display histogram using pyplt"""
    fig, ax = plt.subplots()
    ax.bar(np.arange(len(hist)), hist)
    ax.set_xlabel('value')
    ax.set_ylabel('count')
    plt.show()


def show_mapping(mapping):
    """Helper function to display mapping using pyplt"""
    x = range(256)
    y = [mapping(i) for i in x]

    fig, ax = plt.subplots()
    ax.plot(x, y)
    ax.set_xlabel('old value')
    ax.set_ylabel('new value')
    plt.show()


def aufgabe_2():
    # Load image
    img = cv2.imread("p02_teil2_steine.jpg")
    (width, height, _) = img.shape

    # Calculate histogram of input image
    hist = calculate_hist(img)
    show_hist(hist)

    # Cumulate histogram of input image
    cumulative_hist = cumulate_hist(hist)
    show_hist(cumulative_hist)

    # Create mapping from cumulative histogram
    mapping = get_mapping(cumulative_hist, width * height)
    show_mapping(mapping)

    # Apply mapping to image, creating the result image
    new_img = np.array([[mapping(pixel) for pixel in row] for row in img], np.uint8)

    # Calulate histogram of result image (for visualisation)
    hist = calculate_hist(new_img)
    show_hist(hist)

    # Cumulate histogram of result image (for visualisation)
    cumulative_hist = cumulate_hist(hist)
    show_hist(cumulative_hist)

    # Display input and result image
    cv2.imshow("Ausgangsbild", img)
    cv2.waitKey()
    cv2.imshow("Ergebnisbild", new_img)
    cv2.waitKey()


def main():
    aufgabe_1(25)
    aufgabe_1(100)
    aufgabe_2()


if __name__ == "__main__":
    main()