#include "actions_with_images.h"

cv::Mat grayImage() {
    // create image
    cv::Mat ima(240,320,CV_8U,cv::Scalar(100));
    // return it
    return ima;
}


void flipImage(cv::Mat image)
{
    cv::Mat result;
    cv::flip(image,result,1);
    cv::namedWindow("Flipped Image");
    cv::imshow("Flipped Image", result);
    cv::imwrite("flipped image.bmp", result);
}
