#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <string>
#include "actions_with_images.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // read an image
    cv::Mat image = cv::imread("../opencv_widget/images/sadeness.jpg", 1);
    //if image has been read
    if (image.data) {
        // create image window named "My Image"
        cv::namedWindow("My Image");
        // show the image on window
        cv::imshow("My Image", image);

        int imageHeight = image.size().height;
        int imageWidth = image.size().width;

        std::cout << "size:\n"
                  << "  height: " << imageHeight << "\n"
                  << "  width: " << imageWidth
                  << std::endl;

        //build QString object
        QString text = QString("size:\n  height: ")
                .append(QString::number(imageHeight))
                .append("\n").append("  width: ")
                .append(QString::number(imageWidth));
        //get the label from mainwindow.ui source
        ui->label->setText(text);

        //flip image
        //TODO why showFlippedImage(image) doesn't work but showGrayImage() works fine with button?
        connect(ui->btn_flip_image, SIGNAL(clicked()),
                    this, SLOT(showFlippedImage(image)));

        // get a gray-level image as responce for click() signal
        connect(ui->btn_gray_image, SIGNAL(clicked()),
                    this, SLOT(showGrayImage()));

    } else {
        std::cout << "NO IMAGE";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFlippedImage(cv::Mat image)
{
    cv::Mat result;
    cv::flip(image,result,1);
    cv::namedWindow("Flipped Image");
    cv::imshow("Flipped Image", result);
    cv::imwrite("flipped image.bmp", result);

    //or
    //flipImage(image);
}

void MainWindow::showGrayImage()
{
    cv::Mat gray= grayImage();
    cv::namedWindow("Gray Image");
    cv::imshow("Gray Image", gray);
}
