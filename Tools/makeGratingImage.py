import numpy as np
import cv2
import sys
from os import path


def makeGratingImage(width, height, linePitchRate):
    image = np.zeros((width, height), np.int)

    for h in range(image.shape[0]):
        for w in range(image.shape[1]):
            if int(w / (width * linePitchRate)) % 2 == 0:
                image[h][w] = 255
            else:
                image[h][w] = 0
    
    return image

if __name__ == "__main__":
    args = sys.argv
    width = int(args[1])
    height = int(args[2])
    linePitchRate = float(args[3])
    file_name = args[4]

    out_path="Assets/"
    
    if not path.exists(out_path):
        exit("指定された保存先は存在しません")
    
    # width, height, linePitchRate = 256, 256, 1/10
    image = makeGratingImage(width, height, linePitchRate)

    cv2.imwrite(out_path + file_name, image)