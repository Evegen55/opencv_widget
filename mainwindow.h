#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QtNetwork/QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int showCannyEdges();
    int showColoredFrame();
    int showColoredCamInTab();
    
public slots:
    void openImageAsOpeCVFrame();
    void openImageAndShowInTab();
    void showGrayImageAsOpeCVFrame();
    void showFrameWithColor();
    void showFrameWithCannyEdges();
    void getVideoFromCamShowInTab();
    //void showFlippedImage(cv::Mat image);
    //Открываем JSON по клику кнопки
    void openJsonFromWeb();

private slots:
    void on_btn_image_to_tab_clicked();
    // Обработчик данных полученных от объекта QNetworkAccessManager
    void onJsonResult(QNetworkReply *reply);

private:
    cv::Mat flipImageInTab(cv::Mat image);
    Ui::MainWindow *ui;
    cv::Mat imageForActionsInTab;

    QNetworkAccessManager *networkManager;
};

#endif // MAINWINDOW_H
