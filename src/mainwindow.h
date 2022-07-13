#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QPushButton>
#include <QLabel>
#include "player.h"
#include "map.h"
#include "state.h"
#include "mypushbutton.h"
#include "customscene.h"
#include "choosescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private:
    Ui::MainWindow *ui;
    Player player;
    Map map;

    //拷贝人物和地图，用于重开'R'操作
    Player origin_player;
    Map origin_map;

    //维护每一时刻状态的栈，用于回退'Z'操作
    QStack<State> state;

    //资源文件载入
    QPixmap help;   //帮助界面的图片
    QPixmap background; //背景图片
    QPixmap congrat;    //胜利图片

    //按钮
    MyPushButton* startBtn = nullptr;
    MyPushButton* customBtn = nullptr;
    MyPushButton* exitBtn = nullptr;

    //布尔值
    bool tabPressedDown = false;    //是否按下H键
    bool isGaming = false;          //是否正在游戏中
    bool isCustom = false;          //是否正在自定义设计关卡
    bool isChoosing = false;        //是否正在选择关卡
    bool success = false;           //是否胜利

    //场景
    CustomScene* customScene = nullptr;
    ChooseScene* chooseScene = nullptr;

    //游戏逻辑
    void collision(int _dRow, int _dCol);
    void set();             //重置当前关卡
    void callback();        //回退到上一次的状态
    void chooseLevel();     //按下“开始”按钮后的界面操作
    void startGame();       //开始进入游戏界面
    void copy();            //拷贝人物和地图
    void initGame();        //游戏界面初始化
    void returnToMenu();    //回到菜单界面

    //绘图函数
    void gamePaintEvent(QPainter* painter);

    //用于显示当前步数的label
    QLabel* label;


};
#endif // MAINWINDOW_H
