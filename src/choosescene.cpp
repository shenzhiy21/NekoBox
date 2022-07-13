#include "choosescene.h"
#include "mypushbutton.h"
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>

ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1280, 1024);
    this->setWindowTitle("Level");
    this->setWindowIcon(QIcon(":/res/Player_left.png"));

    //背景图片加载
    background.load(":/res/Background2.png");

    for(int i = 0; i < LEVEL_SIZE; i++)
    {
        MyPushButton* levelBtn = new MyPushButton(":/res/levelBtn.png");
        levelBtn->setParent(this);
        levelBtn->move(230 + i%4 * 200 , 130 + i/4 * 175);

        //创建标签（按钮的文字）
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(levelBtn->width(), levelBtn->height());
        label->setText(QString::number(i + 1));
        label->move(230 + i%4 * 200 , 130 + i/4 * 175);
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        //设置 label上的文字对齐方式 水平居中和 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(levelBtn, &MyPushButton::clicked, [=](){
            level = i + 1;
            emit this->startGame();
        });
    }
}

void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //绘制背景
    painter.drawPixmap(0, 0, 1280, 1024, background);
}

void ChooseScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        emit this->returnToMenu();
        return;
    }
}
