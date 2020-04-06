import numpy as np
import cv2
import sys
from os import path
import csv


if __name__ == "__main__":
    args = sys.argv
    file_path = args[1]
    out_path = args[2]
    
    if not path.exists(file_path):
        exit("指定された画像は存在しません")
    
    # グレイスケールで取得する
    img = cv2.imread(file_path, 0)
    vec_hex = np.vectorize(hex)
    hex_img = vec_hex(img)

    with open(out_path, 'w') as f:
        writer = csv.writer(f)
        writer.writerows(hex_img.tolist())
