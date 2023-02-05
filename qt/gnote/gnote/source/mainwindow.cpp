#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 分屏 左右布局
    _spliterMainView = new QSplitter(Qt::Horizontal, 0); //新建主分割窗口，水平分割

    textEditIn = new EditorCore(_spliterMainView);

    textEditOut = new QTextEdit(_spliterMainView);

    // 分屏的切换展示模式
    _spliterMainView->setStretchFactor(0,50);
    _spliterMainView->setStretchFactor(1,50);



    // 菜单栏
    _menuBar = new QMenuBar(this);

    QMenu *_fileMenus = new QMenu("文件",_menuBar);
//    QAction *_newWin = new QAction("新窗口",_fileMenus);

    _menuBar->addMenu(_fileMenus);


    QMenu *_styleMenus = new QMenu("样式",_menuBar);
    _menuBar->addMenu(_styleMenus);


    QMenu *_aboutMenus = new QMenu("关于",_menuBar);
    _menuBar->addMenu(_aboutMenus);

    this->setMenuBar(_menuBar);

    // 工具栏



    this->setCentralWidget(_spliterMainView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

