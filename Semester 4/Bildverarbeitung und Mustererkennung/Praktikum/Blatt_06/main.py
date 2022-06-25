from math import floor

import cv2
import numpy as np

HIGH = 255
LOW = 0

MORPH_KERNEL_SIZE = 3
OPENING_ITERATIONS = 1
BACKGROUND_ITERATIONS = 10
DISTANCE_MASK_SIZE = 3
DISTANCE_THRESHOLD_FACTOR = 0.15
OUTLINE_MARKER = -1
OUTLINE = [255, 0, 0]


def dilate(img, structure):
    """Dilation of supplied image using supplied structure"""
    (height, width) = img.shape
    (sheight, swidth) = structure.shape

    # initialize output
    dilated = np.zeros(img.shape, np.uint8)

    # get start and and of structure
    sx_end = floor(swidth / 2)
    sx_start = -sx_end
    sy_end = floor(sheight / 2)
    sy_start = -sy_end

    # go through each pixel in image
    for y in range(height):
        for x in range(width):
            value = 0

            # multiply section of image with structure and calculate sum
            for sy in range(sy_start, sy_end + 1):
                for sx in range(sx_start, sx_end + 1):
                    if 0 <= y + sy < height and 0 <= x + sx < width:
                        value += img[y + sy, x + sx] * structure[sy - sy_start, sx - sx_start]

            if value > 0:
                # dilate pixel
                dilated[y, x] = HIGH

    return dilated


def erode(img, structure):
    """Erosion of supplied image using supplied structure"""
    (height, width) = img.shape
    (sheight, swidth) = structure.shape

    # initialize output
    eroded = np.zeros(img.shape, np.uint8)
    # claculate threshold
    high = np.sum(structure) * HIGH

    # get structure start and end
    sx_end = floor(swidth / 2)
    sx_start = -sx_end
    sy_end = floor(sheight / 2)
    sy_start = -sy_end

    # go through each pixel
    for y in range(height):
        for x in range(width):
            value = 0

            # multiply section of image with structure and calculate sum
            for sy in range(sy_start, sy_end + 1):
                for sx in range(sx_start, sx_end + 1):
                    if 0 <= y + sy < height and 0 <= x + sx < width:
                        value += img[y + sy, x + sx] * structure[sy - sy_start, sx - sx_start]

            # if value is threshold
            if value == high:
                # erode image
                eroded[y, x] = HIGH

    return eroded


def aufgabe_1():
    # load image
    img = cv2.imread("p06_zahnrad.png", cv2.IMREAD_GRAYSCALE)

    # initialize structure and iteration count
    structure = np.array([
        [0, 0, 1, 0, 0],
        [0, 0, 1, 0, 0],
        [1, 1, 1, 1, 1],
        [0, 0, 1, 0, 0],
        [0, 0, 1, 0, 0]
    ])
    iterations = 2

#    cv2.imshow("Original", img)
#    cv2.waitKey()

    # dilate image for number of iterations using structure
    dilated = img
    for _ in range(iterations):
        dilated = dilate(dilated, structure)
    cv2.imshow("Dilatation", dilated)
    cv2.waitKey()

    # erode image for number of iterations using structure
    eroded = dilated
    for _ in range(iterations):
        eroded = erode(eroded, structure)
    cv2.imshow("Erosion", eroded)
    cv2.waitKey()


def aufgabe_2():
    # load image
    img = cv2.imread("p06_gummitiere.png")
    # extract blue channel
    blue_channel = img[:, :, 0]
#    cv2.imshow("Threshold", blue_channel)
#    cv2.waitKey()

    # apply thresholding using otsu's method and invert
    ret, thresh = cv2.threshold(blue_channel, 0, HIGH, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

#    cv2.imshow("Threshold", thresh)
#    cv2.waitKey()

    # apply opening morphological transformation
    kernel = np.ones((MORPH_KERNEL_SIZE, MORPH_KERNEL_SIZE), np.uint8)
    opening = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel, iterations=OPENING_ITERATIONS)

#    cv2.imshow("Morphed", opening)
#    cv2.waitKey()

    # dilate image once again to get background spots
    sure_bg = cv2.dilate(opening, kernel, iterations=BACKGROUND_ITERATIONS)

#    cv2.imshow("bg", sure_bg)
#    cv2.waitKey()

    # calculate distances
    dist_transform = cv2.distanceTransform(thresh, cv2.DIST_C, DISTANCE_MASK_SIZE)

#    cv2.imshow("distance transformation", dist_transform)
#    cv2.waitKey()

    # apply thresholding to distance image to get foreground spots
    ret, sure_fg = cv2.threshold(dist_transform, dist_transform.max() * DISTANCE_THRESHOLD_FACTOR, HIGH, LOW)
    sure_fg = np.uint8(sure_fg)

#    cv2.imshow("sure_fg", sure_fg)
#    cv2.waitKey()

    # calculate unknown area by subtracting foreground from background
    unknown = cv2.subtract(sure_bg, sure_fg)

#    cv2.imshow("unknown", unknown)
#    cv2.waitKey()

    # create markers
    ret, markers = cv2.connectedComponents(sure_fg)
    markers += 1
    markers[unknown == HIGH] = 0

    # apply watershed algorithm using markers
    markers = cv2.watershed(img, markers)
    segments = np.uint8((markers + 1) / (np.max(markers) + 1) * HIGH)
    marker_img = cv2.applyColorMap(segments, cv2.COLORMAP_JET)

    # outline markers in image
    img[markers == OUTLINE_MARKER] = OUTLINE

    cv2.imshow("marker", marker_img)
    cv2.waitKey()

    num_labels, _, _, centroids = cv2.connectedComponentsWithStats(segments, connectivity=4)
    for i in range(1, num_labels):
        [x, y] = centroids[i]
        cv2.putText(img, str(i), (int(x), int(y)), cv2.FONT_HERSHEY_SIMPLEX, 1, OUTLINE, 1)

    cv2.imshow("watershed", img)
    cv2.waitKey()


def main():
    aufgabe_1()
    aufgabe_2()


if __name__ == "__main__":
    main()
