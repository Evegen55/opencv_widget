#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <string>
#include "actions_with_images.h"

#include <QFileDialog>

#include <QtGlobal>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // get a gray-level image as responce for click() signal
    connect(ui->btn_gray_image, SIGNAL(clicked()),
            this, SLOT(showGrayImageAsOpeCVFrame()));
    // read an image
    connect(ui->btn_open_image_as_opencv_frame, SIGNAL(clicked()),
            this, SLOT(openImageAsOpeCVFrame()));
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
    //flip image by clicking button
    connect(ui->btn_flip_image, SIGNAL(clicked()),
            this, SLOT(on_btn_image_to_tab_clicked()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openImageAsOpeCVFrame() {
    //    cv::Mat image = cv::imread("../opencv_widget/images/sadeness.jpg", 1);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    cv::Mat image = cv::imread(fileName.toStdString());
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
        ui->labelForMessages->setText(text);
    } else {
        qDebug() << QString("NO IMAGE %1").arg(fileName);
    }

}

//void MainWindow::showFlippedImage(cv::Mat image) {
//    cv::Mat result;
//    cv::flip(image,result,1);
//    cv::namedWindow("Flipped Image");
//    cv::imshow("Flipped Image", result);
//    cv::imwrite("flipped image.bmp", result);
//}



void MainWindow::showGrayImageAsOpeCVFrame() {
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
    imageForActionsInTab = cv::imread(fileName.toStdString());
    //if image has been read
    if (imageForActionsInTab.data) {
        cv::cvtColor(imageForActionsInTab, imageForActionsInTab, CV_BGR2RGB);
        //It creates an object with automatic storage duration.
        //It is created, used, and then goes out of scope when the current block ({ ... }) ends.
        //It's the simplest way to create an object, and is just the same as when you write int x = 0;
        QImage qimg ((const unsigned char*)(imageForActionsInTab.data),
                     imageForActionsInTab.cols,imageForActionsInTab.rows,
                     QImage::Format_RGB888);
        // display on label
        ui->labelForWebCamImages->setPixmap(QPixmap::fromImage(qimg));
        // resize the label to fit the image
        ui->labelForWebCamImages->resize(ui->labelForWebCamImages->pixmap()->size());        
    } else {
        qDebug() << QString("Image %1 has no data or can't being read").arg(fileName);
    }
}

void MainWindow::on_btn_image_to_tab_clicked()
{
    imageForActionsInTab = flipImageInTab(imageForActionsInTab);
}

cv::Mat MainWindow::flipImageInTab(cv::Mat image)
{
    cv::Mat result;
    cv::flip(image,result,1);
    //cv::cvtColor(result, result, CV_BGR2RGB);
    QImage img= QImage((const unsigned char*)(result.data), result.cols,result.rows,QImage::Format_RGB888);
    // display on label
    ui->labelForWebCamImages->setPixmap(QPixmap::fromImage(img));
    // resize the label to fit the image
    ui->labelForWebCamImages->resize(ui->labelForWebCamImages->pixmap()->size());
    return result;
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
        ui->labelForMessages->setText("ERROR! Unable to open camera");
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    qDebug() << QString("Start grabbing from cam with deviceId %1 ").arg(deviceID + apiID);
    ui->labelForMessages->setText("Press any key to terminate");
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
    qDebug() << QString("Start grabbing from cam with deviceId %1 ").arg(deviceID + apiID);
    ui->labelForMessages->setText("Start grabbing colored video\nPress any key to terminate");
    cv::Mat edges;
    cv::namedWindow("frame",1);
    for(;;) {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            ui->labelForMessages->setText("ERROR! blank frame grabbed");
            break;
        }
        cv::imshow("frame", frame);
        if(cv::waitKey(30) >= 0) break;
    }

    return 0;

}

int MainWindow::showColoredCamInTab() {
    cv::VideoCapture cap;
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    cap.open(deviceID + apiID);
    if(!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    qDebug() << QString("Start grabbing from cam with deviceId %1 ").arg(deviceID + apiID);
    ui->labelForMessages->setText("Start grabbing colored video\nPress any key to terminate");

    // resize the label to fit the image
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    ui->labelForWebCamImages->resize(ui->labelForWebCamImages->pixmap()->size());
    for(;;) {
        cap >> frame; // get a new frame from camera
        // check if we succeeded
        if (frame.empty()) {
            std::cerr << "ERROR! blank frame grabbed\n";
            ui->labelForMessages->setText("ERROR! blank frame grabbed\n");
            break;
        }
        //we really need to convert frame in order to adopt frame data to QImage
        cv::cvtColor(frame, frame, CV_BGR2RGB);
        QImage imgFrame = QImage((const unsigned char*)(frame.data), frame.cols,frame.rows,QImage::Format_RGB888);
        // display on label with pre-defined size
        ui->labelForWebCamImages->setPixmap(QPixmap::fromImage(imgFrame));
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}
