#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include "chess.h"
#include "mainwindow.h"
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QApplication>
#include <utility>
#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    chess *game;//游戏指针
    QTimer *time;
    QPushButton b1;//开始游戏
    QPushButton b2;//人人
    QPushButton b3;//人机

    void paintEvent(QPaintEvent *);//绘图函数
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent();//鼠标点击
    int clickx,clicky;//鼠标点击坐标
    void startgame();//初始化游戏



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
