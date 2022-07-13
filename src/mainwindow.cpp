#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSound>
#include <QLabel>
#include "define.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1280, 1024);   //固定窗口大小
    setWindowTitle("NekoBox");
    this->setWindowIcon(QIcon(":/res/Player_left.png"));

    //添加场景
    customScene = new CustomScene(this);
    chooseScene = new ChooseScene(this);

    //添加主界面背景
    background.load(":/res/Background.png");

    //添加胜利图片
    congrat.load(":/res/congrat.png");

    //添加移动步数显示
    label = new QLabel;
    label->setParent(this);
    label->setText(QString::number(player.step));
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(pe);
    QFont font;
    font.setPointSize(18);
    label->setFont(font);
    label->move(150, -202);
    label->hide();

    //添加音乐
    QSound *music = new QSound(":/res/BGM.wav");
    music->setLoops(QSound::Infinite);
    music->play();

    //添加按钮
    startBtn = new MyPushButton(":/res/startBtn.png");
    startBtn->setParent(this);
    startBtn->move((this->width() - startBtn->width()) / 2, 500);
    connect(startBtn, &QPushButton::clicked, [&](){
        isChoosing = true;
        this->chooseLevel();
    });

    customBtn = new MyPushButton(":/res/customBtn.png");
    customBtn->setParent(this);
    customBtn->move((this->width() - customBtn->width()) / 2, 650);
    connect(customBtn, &QPushButton::clicked, [&](){
        isCustom = true;
        customScene->reset();
        customScene->show();
        this->hide();
    });

    exitBtn = new MyPushButton(":/res/exitBtn.png");
    exitBtn->setParent(this);
    exitBtn->move((this->width() - exitBtn->width()) / 2, 800);
    connect(exitBtn, &QPushButton::clicked,[&](){
        this->close();
    });

    //监听
    connect(customScene, &CustomScene::customCheck, [&](){
        isCustom = false;
        customScene->hide();

        this->show();
        this->startGame();
    });

    connect(customScene, &CustomScene::returnToMenu, [&](){
        isCustom = false;
        customScene->hide();
        this->show();
    });

    connect(chooseScene, &ChooseScene::startGame, [&](){
        isChoosing = false;
        chooseScene->hide();
        this->show();
        this->initGame();
        this->startGame();
    });

    connect(chooseScene, &ChooseScene::returnToMenu, [&](){
        isChoosing = false;
        chooseScene->hide();
        this->show();
    });

    //初始化资源文件
    help.load(":/res/help.png");

}

MainWindow::~MainWindow()
{
    delete ui;
}


