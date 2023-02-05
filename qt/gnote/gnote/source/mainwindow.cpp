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
    connect(textEditIn,&EditorCore::textChanged,this,&MainWindow::textContent);

    textEditOut = new QTextEdit(_spliterMainView);

    // 分屏的切换展示模式
    _spliterMainView->setStretchFactor(0,50);
    _spliterMainView->setStretchFactor(1,50);



    // 菜单栏
    _menuBar = new QMenuBar(this);

    QMenu *_fileMenus = new QMenu("文件",_menuBar);
    QAction *_newWin = new QAction("新窗口",_fileMenus);
    _fileMenus->addAction(_newWin);

    _fileMenus->addSeparator();

    QAction *_newFile = new QAction("新建文件",_fileMenus);
    _fileMenus->addAction(_newFile);

    QAction *_openFile = new QAction("打开文件",_fileMenus);
    _fileMenus->addAction(_openFile);

    QAction *_saveFile = new QAction("保存文件",_fileMenus);
    _fileMenus->addAction(_saveFile);

    _fileMenus->addSeparator();

    QAction *_saveAsFile = new QAction("文件另存为",_fileMenus);
    _fileMenus->addAction(_saveAsFile);

    _menuBar->addMenu(_fileMenus);


    QMenu *_styleMenus = new QMenu("样式",_menuBar);
    _menuBar->addMenu(_styleMenus);


    QMenu *_aboutMenus = new QMenu("关于",_menuBar);

    QAction *_aboutMe = new QAction("关于作者",_aboutMenus);
    _aboutMenus->addAction(_aboutMe);

    _menuBar->addMenu(_aboutMenus);

    _menuBar->addMenu(_aboutMenus);



    this->setMenuBar(_menuBar);




    // 工具栏

    _toolBar = new QToolBar(this);

    QToolButton *_hToolBtn = new QToolButton;
    _hToolBtn->setText("标题");
    _hToolBtn->setToolTip("标题H");

    _hToolBtn->setPopupMode(QToolButton::InstantPopup);

    QMenu *_hMenu = new QMenu;
    QAction *h1 = new QAction("H1");
    QAction *h2 = new QAction("H2");
    QAction *h3 = new QAction("H3");
    QAction *h4 = new QAction("H4");
    QAction *h5 = new QAction("H5");
    QAction *h6 = new QAction("H6");

    _hMenu->addAction(h1);
    _hMenu->addAction(h2);
    _hMenu->addAction(h3);
    _hMenu->addAction(h4);
    _hMenu->addAction(h5);
    _hMenu->addAction(h6);

    _hToolBtn->setMenu(_hMenu);

    connect(_hToolBtn,&QToolButton::triggered,_hMenu,&QMenu::show);

    _toolBar->addWidget(_hToolBtn);



    QToolButton *_boldToolBtn = new QToolButton;
    _boldToolBtn->setText("粗体");
    _boldToolBtn->setToolTip("粗体B");
    _toolBar->addWidget(_boldToolBtn);


    QToolButton *_italicToolBtn = new QToolButton;
    _italicToolBtn->setText("斜体");
    _italicToolBtn->setToolTip("斜体I");
    _toolBar->addWidget(_italicToolBtn);


    QToolButton *_listToolBtn = new QToolButton;
    _listToolBtn->setText("有序列表");
    _listToolBtn->setToolTip("有序列表");
    _toolBar->addWidget(_listToolBtn);


    QToolButton *_unListToolBtn = new QToolButton;
    _unListToolBtn->setText("无序列表");
    _unListToolBtn->setToolTip("无序列表");
    _toolBar->addWidget(_unListToolBtn);

    QToolButton *_imgToolBtn = new QToolButton;
    _imgToolBtn->setText("图片");
    _imgToolBtn->setToolTip("图片Image");
    _toolBar->addWidget(_imgToolBtn);

    QToolButton *_codeToolBtn = new QToolButton;
    _codeToolBtn->setText("代码");
    _codeToolBtn->setToolTip("代码code");
    _toolBar->addWidget(_codeToolBtn);

    QToolButton *_mathToolBtn = new QToolButton;
    _mathToolBtn->setText("公式");
    _mathToolBtn->setToolTip("公式Math");
    _toolBar->addWidget(_mathToolBtn);

    QToolButton *_flowToolBtn = new QToolButton;
    _flowToolBtn->setText("流程图");
    _flowToolBtn->setToolTip("流程图Flow");
    _toolBar->addWidget(_flowToolBtn);

    this->addToolBar(_toolBar);



    this->setCentralWidget(_spliterMainView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: textContent(){
    qDebug() << textEditIn->toPlainText() << Qt::endl;
}

