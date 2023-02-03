#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 分屏 左右布局
    _spliterMainView = new QSplitter(Qt::Horizontal, 0); //新建主分割窗口，水平分割

    textEditIn = new QTextEdit(_spliterMainView);

    textEditOut = new QTextEdit(_spliterMainView);

    // 分屏的切换展示模式
    _spliterMainView->setStretchFactor(0,50);
    _spliterMainView->setStretchFactor(1,50);


    this->setCentralWidget(_spliterMainView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

