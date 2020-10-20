#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chess.h"
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QPaintEvent>
#include<QLabel>
#include<QBitmap>
#include<QPushButton>
#include<qmath.h>
#include<QBrush>
#include<QDebug>
#include<QMouseEvent>
#include<QMessageBox>
//#include <QSound>
//#include<QMediaPlayer>
#include<QMenuBar>
#include<QMenu>
#include<QIcon>
#include<qtimer.h>

const int chess_size=21;
const int distance=40;
const int block=40;
const int moused=25;
const int lenth=11;
const int r=17;
const int ai=700;
    MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

setMouseTracking(true);
    ui->setupUi(this);
    this->setFixedSize(distance*2+(chess_size-1)*block+400,2*distance+(chess_size-1)*block);
    ui->pushButton->setGeometry(1000,200,200,60);
    ui->pushButton_2->setText("人机对战");
    ui->pushButton_2->setGeometry(1000,400,200,60);
    startgame();
connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::slot_button);
connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::slot_button2);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(game)
    {
        delete  game;
        game=nullptr;
    }
    if(time)
    {
        delete time;
        time=nullptr;
    }
}
void MainWindow::paintEvent(QPaintEvent *)
{
    if(ui->pushButton->underMouse())
        {
            ui->pushButton->setFlat(false);
        }
        else
        {
            ui->pushButton->setFlat(true);
        }
        if(ui->pushButton_2->underMouse())
        {
            ui->pushButton_2->setFlat(false);
        }
        else
        {
            ui->pushButton_2->setFlat(true);
        }



    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap("../123/2161747_211210803000_2.jpg"));
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    p.setPen(pen);
    for(int i=0;i<chess_size;i++)
    {
        p.drawLine(distance,distance+i*block,distance+(chess_size-1)*block,distance+i*block);//画横线
        p.drawLine(distance+i*block,distance,distance+i*block,distance+(chess_size-1)*block);
    }
    QBrush brush;
    //画圆形棋子
    brush.setStyle(Qt::SolidPattern);
    //绘制鼠标落子点
    if(clickx>=0&&clickx<chess_size&&clicky>=0&&clicky<chess_size&&game->state==1&&game->board[clickx][clicky]==0)
    {
        if(game->player)
        {
            brush.setColor(Qt::black);
            p.setBrush(brush);
            p.drawRect(distance+block*clickx-lenth/2,distance+block*clicky-lenth/2,lenth,lenth);

        }
        else if(game->player==false&&game_type!='r')
        {
            brush.setColor(Qt::white);
            p.setBrush(brush);
            p.drawRect(distance+block*clickx-lenth/2,distance+block*clicky-2,lenth,lenth);
        }
    }
    //画棋子
    for(int i=0;i<chess_size;i++)
    {
        for(int j=0;j<chess_size;j++)
        {
            if(game->board[i][j]==1)
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint(distance+block* i ,distance +block* j),r,r);
            }
            else if(game->board[i][j]==-1)
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint(distance+block* i ,distance +block* j),r,r);

            }
        }
    }
    update();
}

void MainWindow::startgame()//初始化
{
    game=new chess;
    time=nullptr;

}

void MainWindow::init(char type)
{
    if(game)
    {
        delete game;
    }
    game=new chess;
    game->state=1;
    game->type=type;
    if(time)
    {
        delete time;
        time=nullptr;

    }
    clickx=-1;
    clicky=-1;
    game->start(type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    int mx=ev->x();
    int my=ev->y();
    //保证鼠标在范围内
    if(mx>=distance-moused&&mx<=distance+(chess_size-1)*block+moused&&my>=distance-moused&&my<=distance+(chess_size-1)*block&&game->state==1)
    {
        //获取距离最近的左上角坐标
        int row=(mx-distance)/block;
        int col=(my-distance)/block;
        int leftrow=distance+block*row;
        int leftcol=distance+block*col;
        clickx=-1;
        clicky=-1;
        //确定一个在误差范围内的点
        int l=0;
        selectPos = false;
        l=sqrt((mx-leftrow)*(mx-leftrow)+(my-leftcol)*(my-leftcol));
        if(l<moused)
        {
            clickx=row;
            clicky=col;
            if (game->board[clickx][clicky]==0)
            {
                selectPos = true;
            }
        }
        l=sqrt((mx-leftrow-block)*(mx-leftrow-block)+(my-leftcol)*(my-leftcol));
        if(l<moused)
        {
           clickx=row+1;
           clicky=col;
           if (game->board[clickx][clicky]==0)
           {
               selectPos = true;
           }
        }
        l=sqrt((mx-leftrow)*(mx-leftrow)+(my-leftcol-block)*(my-leftcol-block));
        if(l<moused)
        {
                clickx=row;
                clicky=col+1;
                if (game->board[clickx][clicky]==0)
                {
                    selectPos = true;
                }
        }
        l=sqrt((mx-leftrow-block)*(mx-leftrow-block)+(my-leftcol-block)*(my-leftcol-block));
        if(l<moused)
        {
            clickx=row+1;
            clicky=col+1;
        }
        if (game->board[clickx][clicky]==0)
        {
            selectPos = true;
        }
    }
update();



}



void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (selectPos=false)
    {
        return;
    }
    else
        selectPos=false;


        if(game_type=='s'||game->player==true)
        {
            actionpeo();
        }
        if(game_type=='r'&&game->player==false)
        {
            QTimer::singleShot(ai,this,SLOT(actionai()));
        }

    update();
}

void MainWindow::actionpeo()
{
    if(clickx!=-1&&clicky!=-1&&game->board[clickx][clicky]==0)
    {
        game->act_peo(clickx,clicky);
        ifend();
        update();
    }
}
void MainWindow::actionai()
{
    game->act_ai(clickx,clicky);  //落子

        ifend();  //判断输赢
        update();
}

void MainWindow::ifend()
{
    //if(clickx>=0&&clicky>=0&&clickx<chess_size&&clicky<chess_size&&game->board[clickx][clicky]!=0)
    {
        //黑子是否禁手
   //     if(game->board[clickx][clicky]==1&&game->jinshou(clickx,clicky)&&game->state==1)
        {
    //        time->stop();
   //         time=nullptr;
        }
   //     QMessageBox::StandardButton standar=QMessageBox::information(this,"游戏结束","黑方禁手，白方获胜。",QMessageBox::Ok);
    //    if(standar==QMessageBox::Ok)
        {
   //         game->state=0;
   //         game->clear();
   //         ui->pushButton->setText("双人对决");
  //          ui->pushButton_2->setText("人机对决");
            //ui->pushButton_3->setText("智能对决");
        }

    }
   // else
    if(game->ifheqi()&&game->state==1)
            {
                if(time)
                {
                    time->stop();
                    time=nullptr;   //关闭定时器
                }
                game->state=0;
                QMessageBox::StandardButton standarbutton=QMessageBox::information(this,"游戏结束","该局和棋",QMessageBox::Ok);
                if(standarbutton==QMessageBox::Ok)
                {
                    game->state=0;
                    game->clear();
                    ui->pushButton->setText("双人对战");
                    ui->pushButton_2->setText("人机对战");
                   // ui->pushButton_3->setText("智能对决");
                }
            }
    else if(game->ifwin(clickx,clicky)&&game->state==1)
    {
        if(time)
        {
            time->stop();
            time=nullptr;}
        if(game->board[clickx][clicky]==1)
        {
           QMessageBox::StandardButton standarbutton1=QMessageBox::information(this," 游戏结束！","黑棋胜",QMessageBox::Ok);//黑棋胜
           if(standarbutton1==QMessageBox::Ok)
           {
             game->state=0;
             game->clear();
             ui->pushButton->setText("双人对战");
             ui->pushButton_2->setText("人机对战");
             //ui->pushButton_3->setText("智能对决");
            }
       }

        else
        {
            QMessageBox::StandardButton standarbutton1=QMessageBox::information(this," 游戏结束！","白棋胜",QMessageBox::Ok); //白棋胜
            if(standarbutton1==QMessageBox::Ok)
            {
              game->state=0;
              game->clear();
              ui->pushButton->setText("双人对战");
              ui->pushButton_2->setText("人机对战");
              //ui->pushButton_3->setText("智能对决");
             }
        }
    }


}
void MainWindow::slot_button()
{
    if(time)
    {
        time->stop();
        delete time;
        time=nullptr;
    }
    ui->centralWidget->setMouseTracking(true); //激活鼠标追踪
    setMouseTracking(true);  //激活整个窗体的鼠标追踪
    ui->pushButton->setMouseTracking(true); //激活该按钮的鼠标追踪功能
    game_type='s';  //双人模式类型
    init(game_type);  //初始化
    ui->pushButton->setText("重新开始:双人对决");
    ui->pushButton_2->setText("人机对决");
    //ui->pushButton_3->setText("智能对决");
    update();
    }
void MainWindow::slot_button2()
{
    if(time)
    {
        time->stop();
        delete time;
        time=nullptr;
    }
    ui->centralWidget->setMouseTracking(true); //激活鼠标追踪
    setMouseTracking(true);  //激活整个窗体的鼠标追踪
    ui->pushButton_2->setMouseTracking(true); //激活该按钮的鼠标追踪功能
    game_type='r';  //双人模式类型
    init(game_type);  //初始化
    ui->pushButton->setText("双人对决");
    ui->pushButton_2->setText("人机对决");
    update();
}
