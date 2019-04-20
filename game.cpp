#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 15
#define LINES 15

char board[ROWS][LINES] = {" "};
char pieces[ROWS][LINES] = {"0"};
char ch = '0';
int point = 0;

class Board {
public:
     Board(int row = 15 , int line = 15)
        :_row(row)
        ,_line(line)
    {}

    Board(const Board& b) 
        :_row(b._row)
        ,_line(b._line)
    {}
    
    ~Board() 
    {}

    // 初始化棋盘
    void InitBoard() {
        memset(board , ' ' , ROWS*LINES*sizeof(char));
    }

    // 打印棋盘
    void DisplayBoard()const {
        int i = _row;
        int k = 1;
        cout << " 0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 |" << endl;
        cout << "---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|" << endl;
        while(i) {
            if (k < 10) {
                cout << " " << k << " |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
            }
            else {
                cout << k << " |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
            }
            ++k;
            --i;
            cout << "---|----|----|----|----|----|----|----|----|----|----|----|----|----|----|----|" << endl;
        }
        return;
    }
private:
    int _row;
    int _line;
};

// 棋子颜色
enum _color {
    black = 1,    // 黑色
    white = 2     // 白色
}_color;

// 棋子状态
enum _state {
    legal = 0,     // 合法
    illegal = 1    // 非法
}_state;

class Rule {
public:
    Rule(int x = 7 , int y = 7 , int color = 1 , int state = 0)
        :_x(x)
        ,_y(y)
        ,_color(color)
        ,_state(state)
    {}

    Rule(const Rule& r)
        :_x(r._x)
        ,_y(r._y)
        ,_color(r._color)
        ,_state(r._state)
    {}

    ~Rule() 
    {}

    // 初始化棋子
    void InitPieces() {
        memset(pieces , '0' , ROWS*LINES*sizeof(char));
    }

    // 移动棋子
    void MovePieces() {
        if (_color == 1 && _state == 0) {
            ch = 'b';
            pieces[_x - 1][_y - 1] = ch;
        }
        else if (_color == 0 && _state == 0) {
            ch = 'w';
            pieces[_x - 1][_y - 1] = ch;
        }
    }

private:
    int _x;
    int _y;
    int _color;
    int _state;
};

// 是否合法
int IsLegal(int x , int y) {
    if (x > 15 || x < 1 || y > 15 || y < 1) {
        _state = illegal;
        cout << "越界了，请重新输入~~~" << endl;
        return 1;
    }
    else if (pieces[x][y] != '0') {
        _state = legal;
        cout << "该位置已经下过棋子，请重新输入~~~" << endl;
        return 1;
    }
    return 0;
}

int GameOver(int x ,int y) {
    if (point != 225) {
        int xMin = x - 4;
        int xMax = x + 4;
        int yMin = y - 4;
        int yMax = y + 4;

        int i , j , p , q;
        // 在水平方向遍历，看是否有连续5颗相同颜色的棋子 
        for(i = xMin ; i <= xMax - 4 ; i++) {
            int sum = 0;
            for(j = i ; j < i + 5 ; j++) {
                if(pieces[j][y] == pieces[x][y])
                    sum++;
                else
                    break;
            }       
            if(sum == 5)
                return 0;
        }

        // 在竖直方向遍历，看是否有连续5颗相同颜色的棋子 
        for(i = yMin ; i <= yMax - 4 ; i++) {
            int sum = 0;
            for(j = i ; j < i + 5 ; j++) {
                if(pieces[j][y] == pieces[x][y])
                    sum++;
                else
                    break;
            }       
            if(sum == 5)
                return 0;
        }

        // 左上角位置，从(x,y)开始沿左上方寻找，找到一个满足条件的最大正方形
        // 则从正方形的左上顶点开始沿对角线遍历    
        for(i = x , j = y ; i > xMin && j > yMin ; i-- , j--); 
        // 从左上角向右下角遍历，看是否有连续5颗相同颜色的棋子   
        for(; i <= xMax - 4 && j <= yMax - 4 ; i++ , j++) {
            int sum = 0;
            for(p = i , q = j ; p < i + 5 ; p++ , q++) {
                if (pieces[p][q] == pieces[x][y])
                    sum++;
                else
                    break;
            }
            if(sum == 5)
                return 0;
        }

        // 左下角位置，从(x,y)开始沿左上方寻找，找到一个满足条件的最大正方形
        // 则从正方形的左上顶点开始沿对角线遍历    
        for(i = x , j = y ; i > xMin && j < yMax ; i--,j++); 
        // 从左
        // 左下角向右上角遍历，看是否有连续5颗相同颜色的棋子   
        for(; i <= xMax - 4 && j >= yMin + 4 ; i++ , j--) {
            int sum = 0;
            for(p = i , q = j ; p < i + 5 ; p++ , q--) {
                if (pieces[p][q] == pieces[x][y])
                    sum++;
                else
                    break;
            }
            if(sum == 5)
                return 0;
        }
    }
    else if (point > 225) {
        cout << "棋盘已满" << endl;
        return 1;
    }
    return 1;
}

void WhitePieces(int x , int y) {
    if (IsLegal(x , y) == 1) {
        return;
    }
    else if (IsLegal(x , y) == 0) {
        point++;
        Rule r(x , y , 2 , 0);
        return;
    }
}

void BlackPieces(int x , int y) {
    if (IsLegal(x , y) == 1) {
        return;
    }
    else if (IsLegal(x , y) == 0) {
        point++;
        Rule r(x , y , 1 , 0);
        return;
    }
}

void InPieces(int& x , int& y) {
    cout << "黑子坐标：" << endl;
    cout << "x = "; 
    cin >> x ;
    cout << "y = ";
    cin >> y ;
    cout << endl;
    BlackPieces(x , y);

    cout << "白子坐标：" << endl;
    cout << "x = "; 
    cin >> x ;
    cout << "y = "; 
    cin >> y ;
    cout << endl;
    WhitePieces(x , y);
}

int Show() {
    cout << "------------------------------------" << endl;
    cout << "---------------五子棋---------------" << endl;
    cout << "------------------------------------" << endl;
    cout << "Please input your choose:" << endl;
    cout << "1.退出游戏           2.开始游戏     " << endl;
    int chooce = 0;
    cout << "-- chooce: ";
    cin >> chooce;
    cout << endl;
    Board b;
    if (chooce == 1) {
        return 0;
    }
    else if (chooce == 2) {
        cout << "1.black             2.white      " << endl; 
        cout << "Please the color of your pieces: ";
        cin >> chooce;
        if (chooce == 1) {
            _color = black;
            b.DisplayBoard();
        }
        else if (chooce == 2) {
            _color = white;
            b.DisplayBoard();
        }
    }
    int x = 0;
    int y = 0;
    do {
        InPieces(x , y);
        b.DisplayBoard();
    }
    while (GameOver(x , y));
    return 0;
}

int main() {
    Show();

    return 0;
}








