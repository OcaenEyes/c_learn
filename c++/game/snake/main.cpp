/*
 * @Author: OCEAN.GZY
 * @Date: 2023-05-11 12:19:07
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2023-05-11 12:27:38
 * @FilePath: /c++/game/snake/main.cpp
 * @Description: 注释信息
 */
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// 定义方向键码
#define KEY_LEFT 68
#define KEY_RIGHT 67
#define KEY_UP 65
#define KEY_DOWN 66

// 定义游戏界面大小
const int width = 40;
const int height = 20;

// 定义贪吃蛇头和身体的坐标
int x, y;
int tailX[100], tailY[100];
int nTail = 0;

// 定义食物的坐标和得分
int fruitX, fruitY;
int score = 0;

// 定义游戏状态
bool gameOver = false;

// 定义方向
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

// 初始化游戏
void Setup()
{
    // 初始化随机数种子
    srand(time(NULL));

    // 初始化贪吃蛇头和食物的坐标
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;

    // 初始化方向和得分
    dir = STOP;
    score = 0;

    // 初始化窗口
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
}

// 绘制游戏界面
void Draw()
{
    clear();

    // 绘制上边界
    for (int i = 0; i < width + 2; i++)
        mvprintw(0, i, "-");

    // 绘制下边界
    for (int i = 0; i < width + 2; i++)
        mvprintw(height + 1, i, "-");

    // 绘制左边界
    for (int i = 1; i < height + 1; i++)
        mvprintw(i, 0, "|");

    // 绘制右边界
    for (int i = 1; i < height + 1; i++)
        mvprintw(i, width + 1, "|");

    // 绘制贪吃蛇头和身体
    mvprintw(y, x, "O");
    for (int i = 0; i < nTail; i++)
        mvprintw(tailY[i], tailX[i], "o");

    // 绘制食物
    mvprintw(fruitY, fruitX, "*");

    // 绘制得分
    mvprintw(height + 2, 0, "Score: %d", score);

    refresh();
}

// 处理键盘输入
void Input()
{
    int c = getch();
    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 'q': // 按下 q 键退出游戏
        gameOver = true;
        break;
    }
}

// 更新游戏状态
void Logic()
{
    // 更新贪吃蛇身体的位置
    int prevX = tailX[0];
    int prevY = tailY[0];
    int tempX, tempY;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        tempX = tailX[i];
        tempY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    // 根据方向更新贪吃蛇头的位置
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // 检查贪吃蛇头是否撞到墙或自己的身体
    if (x < 1 || x > width || y < 1 || y > height)
        gameOver = true;
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // 如果贪吃蛇头吃到了食物，则增加得分和贪吃蛇的长度
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void GameSpeed(int level)
{
    // 根据关卡等级计算延迟时间
    int delay = (11 - level) * 100;

    // 延迟一段时间，控制游戏速度
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}
// 游戏主循环
void GameLoop()
{
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        GameSpeed(1); // 控制游戏速度
    }

    // 游戏结束后输出最终得分并关闭窗口
    clear();
    mvprintw(height / 2, (width - 9) / 2, "Game Over!");
    mvprintw(height / 2 + 1, (width - 10) / 2, "Your score: %d", score);
    refresh();
    getch();
    endwin();
}

// 主函数
int main()
{
    Setup();
    GameLoop();
    return 0;
}
