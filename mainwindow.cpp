#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <string>
#include "actions_with_images.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // get a gray-level image as responce for click() signal
    connect(ui->btn_gray_image, SIGNAL(clicked()),
            this, SLOT(showGrayImage()));

    // read an image
    //readImageExample();

    // show canny edges when buttnon clicked
    connect(ui->btn_canny_edges, SIGNAL(clicked()),
            this, SLOT(showFrameWithCannyEdges()));

    // show colored video from cam at index 0 when buttnon clicked
    connect(ui->btn_show_cam, SIGNAL(clicked()),
            this, SLOT(showFrameWithColor()));


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::readImageExample() {
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

    } else {
        std::cout << "NO IMAGE";
    }
}

void MainWindow::showFlippedImage(cv::Mat image) {
    cv::Mat result;
    cv::flip(image,result,1);
    cv::namedWindow("Flipped Image");
    cv::imshow("Flipped Image", result);
    cv::imwrite("flipped image.bmp", result);

    //or
    //flipImage(image);
}

void MainWindow::showGrayImage() {
    cv::Mat gray = grayImage();
    cv::namedWindow("Gray Image");
    cv::imshow("Gray Image", gray);
}

void MainWindow::showFrameWithColor() {
    showColoredFrame();
}

void MainWindow::showFrameWithCannyEdges() {
    showCannyEdges();
}

int MainWindow::showCannyEdges() {
    //--- INITIALIZE VIDEOCAPTURE
    cv::VideoCapture cap;
    // open the default camera using default API
    cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if(!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    std::cout << "Start grabbing" << std::endl
              << "Press any key to terminate" << std::endl;
    cv::Mat edges;
    cv::namedWindow("edges",1);
    for(;;) {
        cv::Mat frame;
        cap >> frame; // // wait for a new frame from camera and store it into 'frame'
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}

int MainWindow::showColoredFrame() {
    cv::VideoCapture cap;
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    cap.open(deviceID + apiID);
    if(! cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    std::cout << "Start grabbing" << std::endl
              << "Press any key to terminate" << std::endl;
    cv::Mat edges;
    cv::namedWindow("frame",1);
    for(;;) {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        cv::imshow("frame", frame);
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;

}
