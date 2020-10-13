#include "subwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
subwidget::subwidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("六子棋");
    //this->setWindowIcon(QIcon(""));
    this->setFixedSize(1280,880);
    b=new QPushButton(this);
    b->move(550,600);
    b->setFixedSize(300,70);
    b->setText("进入游戏");
    connect(b,&QPushButton::clicked,this,&subwidget::sendslot);



}
void subwidget::sendslot()
{
    emit mysignal();
}
