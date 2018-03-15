#include "actions_with_images.h"

cv::Mat grayImage() {
    // create image
    cv::Mat ima(240,320,CV_8U,cv::Scalar(100));
    // return it
    return ima;
}
