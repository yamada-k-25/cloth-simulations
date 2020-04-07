#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    Mat image;
    image = imread("Assets/Lenna.bmp", 0);
    if(!image.data) {
        printf("No image data\n");
        return -1;
    }

    // namedWindow("Display Image", WINDOW_AUTOSIZE);
    // imshow("Display Image", image);
    // waitKey(0);

    imwrite("Assets/LenaGray.bmp", image);

    return 0;
}