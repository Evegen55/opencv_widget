#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readImageExample();    
    int showCannyEdges();
    int showColoredFrame();
    
public slots:
    void openImage();
    void showFlippedImage(cv::Mat image);
    void showGrayImage();
    void showFrameWithColor();
    void showFrameWithCannyEdges();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
