import cv2
import numpy as np


def get_min_index(a):
    """Get indices of minima in array"""
    return np.unravel_index(np.argmin(a), a.shape)


def get_max_index(a):
    """Get indices of maxima in array"""
    return np.unravel_index(np.argmax(a), a.shape)


def ssd(reference, template):
    """Calculates sum of squared differences"""
    return np.sum((template - reference) ** 2)


def cor(reference, template):
    """Calculates correlation coefficient"""
    # redistribute elements around 0
    tdistrib = template - np.average(template)
    rdistrib = reference - np.average(reference)

    # calculate sum of squares
    tsqr = np.sum(tdistrib ** 2)
    rsqr = np.sum(rdistrib ** 2)
    # calculate sum of crosses
    cross = np.sum(tdistrib * rdistrib)

    # return normalized value
    return cross / (tsqr ** (1/2) * rsqr ** (1/2))


def aufgabe_1():
    # load reference image and convert to grayscale
    img = cv2.imread("p07_reference.png")
    reference = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # load template image
    template = cv2.imread("p07_template.png", cv2.IMREAD_GRAYSCALE)

    (rheight, rwidth) = reference.shape
    (theight, twidth) = template.shape

    oheight = rheight - theight
    owidth = rwidth - twidth

    # create arrays for error output
    out_ssd = np.zeros((oheight, owidth))
    out_cor = np.zeros((oheight, owidth))
    for y in range(oheight):
        for x in range(owidth):
            # calculate ssd and cor coefficient of image slice
            out_ssd[y, x] = ssd(reference[y:y+theight, x:x+twidth], template)
            out_cor[y, x] = cor(reference[y:y+theight, x:x+twidth], template)

    # normalize ssd
    out_ssd = out_ssd / np.max(out_ssd)

    # get index of minimum error
    (sy, sx) = get_min_index(out_ssd)
    # mark area using blue rectangle
    ssd_img = np.copy(img)
    cv2.rectangle(ssd_img, (sx, sy), (sx + twidth, sy + theight), (255, 0, 0))
    # display values
    cv2.imshow("ssd values", out_ssd)
    cv2.waitKey()
    # display image
    cv2.imshow("ssd", ssd_img)
    cv2.waitKey()

    # get index of maximum coefficient
    (cy, cx) = get_max_index(out_cor)
    # mark area using green rectangle
    cor_img = np.copy(img)
    cv2.rectangle(cor_img, (cx, cy), (cx + twidth, cy + theight), (0, 255, 0))
    # display values
    cv2.imshow("cor values", out_cor)
    cv2.waitKey()
    # display image
    cv2.imshow("cor", cor_img)
    cv2.waitKey()


KERNELSIZE = (3, 3)
SIGMA = 1.4
ALPHA = 0.06
THRESHOLD = 20000
DISTANCE = 10


def calculate_structure_tensor(g):
    """Calculates structure tensor of supplied grayscale image"""
    # calculate gradient
    gx, gy = np.gradient(g)

    # calculate parts of tensor
    gxgx = cv2.GaussianBlur(gx ** 2, KERNELSIZE, SIGMA)
    gxgy = cv2.GaussianBlur(gx * gy, KERNELSIZE, SIGMA)
    gygy = cv2.GaussianBlur(gy ** 2, KERNELSIZE, SIGMA)

    # return tensor as tuple
    return \
        (gxgx, gxgy), \
        (gxgy, gygy)


def calculate_corner_response_function(tensor):
    """Calculates corner response function of supplied structure tensor"""
    # extract tensor parts
    (gxgx, gygx), \
    (gxgy, gygy) = tensor

    # calculate determinate and trace
    det = gxgx * gygy - gxgy * gygx
    trace = gxgx + gygy

    # return corner response function
    return det - ALPHA * (trace ** 2)


def harris_corner_detector(img):
    """Detects and marks corners in image"""
    # convert image to grayscale
    grayscale = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    (height, width, _) = img.shape

    # calculate tensor
    tensor = calculate_structure_tensor(grayscale)
    # calculate corner response function
    crf = calculate_corner_response_function(tensor)

    # apply thresholding
    ret, thresh = cv2.threshold(crf, THRESHOLD, 0, cv2.THRESH_TOZERO)

    # non maxima supression
    y, x = get_max_index(thresh)
    # while there are maxima in the threshold image
    while thresh[y, x] > 0:
        # draw marker at maxima in output image
        cv2.drawMarker(img, (x, y), (0, 0, 255))
        # remove maxima from threshold image
        thresh[y, x] = 0

        # go through all neighboring pixels
        for sy in range(max(0, y - DISTANCE), min(y + DISTANCE, height)):
            for sx in range(max(0, x - DISTANCE), min(x + DISTANCE, width)):
                # calculate euclidean distance
                distance = ((sx - x) ** 2 + (sy - y) ** 2) ** (1 / 2)
                # if pixel is at most 10 pixels away
                if distance <= DISTANCE:
                    # remove pixel from threshold
                    thresh[sy, sx] = 0

        # get next maxima
        y, x = get_max_index(thresh)


def aufgabe_2():
    # load image
    img = cv2.imread("p07_harris.png")

    # apply harris corner detection
    harris_corner_detector(img)

    # display image with markers
    cv2.imshow("img", img)
    cv2.waitKey()


def main():
    aufgabe_1()
    aufgabe_2()


if __name__ == "__main__":
    main()
