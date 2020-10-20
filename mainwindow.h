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
#include <QMouseEvent>
#include <QEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init(char type);
    chess *game;//游戏指针
    QTimer *time;
    char game_type;
    char game_style;
    bool selectPos=false;


    void paintEvent(QPaintEvent *);//绘图函数
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);//鼠标点击
    int clickx,clicky;//鼠标点击坐标
    void startgame();//初始化游戏
    void ifend();
    void actionpeo();
 private slots:


    void actionai();
    void slot_button();
    void slot_button2();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
