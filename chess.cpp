#include <iostream>
#include "chess.h"
#include "mainwindow.h"
#include <stdlib.h>
#include <time.h>
#include <QTimer>
#include <QApplication>
#include <utility>
#include <QDebug>
#include <vector>
using namespace std;
const int chesssize =21;




chess::chess()
{
    black =1;
    white =-1;
    state =0;
}

void chess::clear()
{
    int i,j;
    for(i=0;i<chesssize;i++)
    {
        for(j=0;j<chesssize;j++)
        {
            board[i][j]=0;
        }
    }
}

void chess::start(char a)
{
    clear();
    player =true;//黑方

}

void chess::updatemap(int x, int y)
{
    if(player)
    {
        board[x][y]=1;
    }
    else
    {
        board[x][y]=-1;
    }
    player=!player;
}

void chess::act_peo(int x, int y)
{
    updatemap(x,y);
}

bool chess::ifwin(int x, int y)
{
    for(int i=0;i<6;i++)
    {
        if(x-i>=0&&x-i+5<chesssize&&board[x-i][y]==board[x-i+1][y]&&
                board[x-i][y]==board[x-i+2][y]&&
                board[x-i][y]==board[x-i+3][y]&&
                board[x-i][y]==board[x-i+4][y]&&
                board[x-i][y]==board[x-i+5][y])//水平方向六子
        {
            return true;
        }
        else if(y-i<=0&&y-i+5<chesssize&&board[x][y-i]==board[x][y-i+1]&&
                board[x][y-i]==board[x][y-i+2]&&
                board[x][y-i]==board[x][y-i+3]&&
                board[x][y-i]==board[x][y-i+4]&&
                board[x][y-i]==board[x][y-i+5])
        {
            return true;
        }
        else if(x+i<chesssize&&x+i-5>=0&&y-i>=0&&y-i+5<chesssize&&
                board[x+i][clickY-i]==board[x+i-1][y-i+1]&&
                board[x+i][clickY-i]==board[x+i-2][y-i+2]&&
                board[x+i][clickY-i]==board[x+i-3][y-i+3]&&
                board[x+i][clickY-i]==board[x+i-4][y-i+4]&&
                board[x+i][clickY-i]==board[x+i-5][y-i+5])
        {
            return true;
        }
        else if(x- i >= 0 &&
                x - i + 5 < chesssize &&
                y - i >= 0 &&
                y - i + 5 < chesssize &&
                board[x-i][y-i] == board[x-i+1][y-i+1] &&
                board[x-i][y-i] == board[x-i+2][y-i+2] &&
                board[x-i][y-i] == board[x-i+3][y-i+3] &&
                board[x-i][y-i] == board[x-i+4][y-i+4]&&
                board[x-i][y-i] == board[x-i+5][y-i+5])
        {
            return true;
        }
    }
    return false;
}

bool chess::ifheqi()
{
    for(int i=0;i<chesssize;i++)
    {
        for(int j=0;j<chesssize;j++)
        {
            if(board[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}
bool chess::jinshou(int x, int y)
{
    int num=0,k=0;
        k=0;
        //向上
        for(int i=0;i<6;i++)
        {
            if(y+i<chessboard_size)
            {
                if(board[x][y+i]==1)
                {
                    k++;
                }
                else if(board[x][y+i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        //qDebug()<<num;
        if(k>=4)
        {
            num++;
        }
        k=0;
        if(num>=2)
        {
            return true;
        }
        //向下
        for(int i=0;i<6;i++)
        {
            if(y-i>=0)
            {
                if(board[x][y-i]==1)
                {
                    k++;
                }
                else if(board[x][y-i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向左
        for(int i=0;i<6;i++)
        {
            if(x-i>=0)
            {
                if(board[x-i][y]==1)
                {
                    k++;
                }
                else if(board[x-i][y]==white)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向右

        for(int i=0;i<6;i++)
        {
            if(x+i<chessboard_size)
            {
                if(board[x+i][y]==1)
                {
                    k++;
                }
                else if(board[x+i][y]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向左上
        for(int i=0;i<6;i++)
        {
            if(x-i>=0&&y-i>=0)
            {
                if(board[x-i][y-i]==1)
                {
                    k++;
                }
                else if(board[x-i][y-i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向左下
        for(int i=0;i<6;i++)
        {
            if(x-i>=0&&y+i<chessboard_size)
            {
                if(board[x-i][y+i]==1)
                {
                    k++;
                }
                else if(board[x-i][y+i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向右上
        for(int i=0;i<6;i++)
        {
            if(x+i<chessboard_size&&y-i>=0)
            {
                if(board[x+i][y-i]==1)
                {
                    k++;
                }
                else if(board[x+i][y-i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        k=0;
        //向右下
        for(int i=0;i<6;i++)
        {
            if(x+i<chessboard_size&&y+i<chessboard_size)
            {
                if(board[x+i][y+i]==1)
                {
                    k++;
                }
                else if(board[x+i][y+i]==-1)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        if(k>=4)
        {
            num++;
        }
        if(num>=2)
        {
            return true;
        }
        return false;


}
