#ifndef CHESS_H
#define CHESS_H



class chess{
public:
    int board[21][21];//棋盘
    int black,white;
    int state;//游戏状态
    char type;//游戏类型
    int score[21][21];

    chess();
    bool player;//当前下棋对象
    bool ifwin(int x,int y);//判断输赢
    bool ifheqi();//判断和棋
    bool jinshou(int x,int y);//是否禁手
    void updatemap(int x,int y);//更新棋盘
    void start(char a);//开始游戏
    void clear();//清理界面

    void act_peo(int x,int y);//玩家落子
    void act_ai(int &clickX,int &clickY);
    void getScore();
    void clear2();
    void playEVE(int &clickx,int &clicky) ;


};
#endif // CHESS_H

