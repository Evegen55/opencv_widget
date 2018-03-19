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

    int showCannyEdges();
    int showColoredFrame();
    int showColoredCamInTab();
    
public slots:
    void openImageAsOpeCVFrame();
    void openImageAndShowInTab();
    void showGrayImage();
    void showFrameWithColor();
    void showFrameWithCannyEdges();    
    void getVideoFromCamShowInTab();
    //void showFlippedImage(cv::Mat image);


private slots:
    void on_btn_image_to_tab_clicked();

private:
    void flipImageInTab(cv::Mat image);
    Ui::MainWindow *ui;
    cv::Mat imageForActionsInTab;
};

#endif // MAINWINDOW_H
