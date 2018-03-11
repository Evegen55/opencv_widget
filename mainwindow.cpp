#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <string>
#include "actions_with_images.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // get a gray-level image as responce for click() signal
    connect(ui->btn_gray_image, SIGNAL(clicked()),
            this, SLOT(showGrayImage()));
    // read an image
    connect(ui->btn_open_image, SIGNAL(clicked()),
            this, SLOT(openImage()));
    // show canny edges when buttnon clicked
    connect(ui->btn_canny_edges, SIGNAL(clicked()),
            this, SLOT(showFrameWithCannyEdges()));
    // show colored video from cam at index 0 when buttnon clicked
    connect(ui->btn_show_cam, SIGNAL(clicked()),
            this, SLOT(showFrameWithColor()));
    // show colored video from cam at index 0 when buttnon clicked
    connect(ui->btn_image_to_tab, SIGNAL(clicked()),
            this, SLOT(openImageAndShowInTab()));
    // show colored video from cam at index 0 when buttnon clicked
    connect(ui->btn_show_cam_in_tab, SIGNAL(clicked()),
            this, SLOT(getVideoFromCamShowInTab()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImage() {
//    cv::Mat image = cv::imread("../opencv_widget/images/sadeness.jpg", 1);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    cv::Mat image= cv::imread(fileName.toStdString());
    //if image has been read
    if (image.data) {
        cv::namedWindow("Original Image");
        cv::imshow("Original Image", image);

        int imageHeight = image.size().height;
        int imageWidth = image.size().width;

        //build QString object
        QString text = QString("size:\n  height: ")
                .append(QString::number(imageHeight))
                .append("\n").append("  width: ")
                .append(QString::number(imageWidth));
        //get the label from mainwindow.ui source
        ui->label->setText(text);

        //flip image
        //TODO why showFlippedImage(image) doesn't work but showGrayImage() works fine with button?
        //No such slot MainWindow::showFlippedImage(image)
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

void MainWindow::openImageAndShowInTab() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    cv::Mat image= cv::imread(fileName.toStdString());
    //if image has been read
    if (image.data) {
        QImage img= QImage((const unsigned char*)(image.data), image.cols,image.rows,QImage::Format_RGB888);
        // display on label
        ui->label_for_image->setPixmap(QPixmap::fromImage(img));
        // resize the label to fit the image
        ui->label_for_image->resize(ui->label_for_image->pixmap()->size());
    } else {
        std::cout << "NO IMAGE";
    }
}

void MainWindow::getVideoFromCamShowInTab() {
    showColoredCamInTab();
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
        ui->label->setText("ERROR! Unable to open camera");
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    std::cout << "Start grabbing" << std::endl;
    ui->label->setText("Press any key to terminate");
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
    std::cout << "Start grabbing" << std::endl;
    ui->label->setText("Start grabbing colored video\nPress any key to terminate");
    cv::Mat edges;
    cv::namedWindow("frame",1);
    for(;;) {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            ui->label->setText("ERROR! blank frame grabbed");
            break;
        }
        cv::imshow("frame", frame);
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;

}

//TODO it doesn't work
int MainWindow::showColoredCamInTab() {
    cv::VideoCapture cap;
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    cap.open(deviceID + apiID);
    if(! cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    std::cout << "Start grabbing" << std::endl;
    ui->label->setText("Start grabbing colored video\nPress any key to terminate");
    for(;;) {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            ui->label->setText("ERROR! blank frame grabbed");
            break;
        }
        QImage imgFrame= QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_RGB888);
        // display on label
        ui->label_for_image->setPixmap(QPixmap::fromImage(imgFrame));
        // resize the label to fit the image
        ui->label_for_image->resize(ui->label_for_image->pixmap()->size());
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;
}


