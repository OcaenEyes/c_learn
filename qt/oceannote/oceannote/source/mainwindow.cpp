#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _fileListModel = new FileListModel;

    // 分屏 左右布局
    _spliterMainView = new QSplitter(Qt::Horizontal, 0); //新建主分割窗口，水平分割
    // 文件列表
    _fileTree = new QTreeView(_spliterMainView);
    // 文件模型
    _fileModel = new QFileSystemModel;
    _fileModel->setRootPath(QDir::currentPath());
    _fileTree->setModel(_fileModel);

    // 右侧布局
    QSplitter *_splitterRight = new QSplitter(Qt::Vertical, _spliterMainView);   //右分割窗口，并以主分割窗口作为父窗口

    // markdown web容器
    _mdwebview = new QWebEngineView(_splitterRight);
    _mdwebview->load(QUrl("qrc:/statics/index.html"));

    // 分屏的切换展示模式
    _spliterMainView->setStretchFactor(1,1);

    // 菜单栏
    _menuBar = new QMenuBar(this);


    QMenu *_fileMenu = new QMenu("文件");
    QMenu *_styleMenu = new QMenu("样式");
    QMenu *_aboutMenu = new QMenu("关于");

    _menuBar->addMenu(_fileMenu);
    _menuBar->addMenu(_styleMenu);
    _menuBar->addMenu(_aboutMenu);

    QAction *_actionNewWin = new QAction("新窗口",_fileMenu);
    connect(_actionNewWin, &QAction::triggered, _fileListModel, &FileListModel::openNewWindow);

    QAction *_actionNewFile = new QAction("新建文档",_fileMenu);
    connect(_actionNewFile, &QAction::triggered, _fileListModel, &FileListModel::ceateFile);

    QAction *_actionOpenFile = new QAction("打开文档",_fileMenu);
    connect(_actionOpenFile, &QAction::triggered, _fileListModel, &FileListModel::openFile);

    QAction *_actionOpenFolder = new QAction("打开文件夹",_fileMenu);
    connect(_actionOpenFolder, &QAction::triggered, _fileListModel, &FileListModel::openFolder);

    QAction *_actionSaveFile = new QAction("保存",_fileMenu);
    connect(_actionSaveFile, &QAction::triggered, _fileListModel, &FileListModel::saveFile);

    QAction *_actionSaveAsFile = new QAction("另存为",_fileMenu);
    connect(_actionSaveAsFile, &QAction::triggered, _fileListModel, &FileListModel::saveAsFile);


    _fileMenu->addAction(_actionNewWin);
    _fileMenu->addSeparator();
    _fileMenu->addAction(_actionNewFile);
    _fileMenu->addAction(_actionOpenFile);
    _fileMenu->addAction(_actionOpenFolder);
    _fileMenu->addSeparator();
    _fileMenu->addAction(_actionSaveFile);
    _fileMenu->addAction(_actionSaveAsFile);

    this->setMenuBar(_menuBar);



    // 工具栏
//    _toolBar = new QToolBar(this);
//    QMenu *fileMenu = new QMenu();
//    QMenu *styleMenu = new QMenu();
//    QMenu *aboutMenu = new QMenu();



//    QAction *_fileAction = fileMenu->addAction("文件");
//    QAction *_styleAction = styleMenu->addAction("样式");
//    QAction *_aboutAction = aboutMenu->addAction("关于");

//    _fileAction->setMenu(_fileMenu);
//    _toolBar->addAction(_fileAction);

//    _styleAction->setMenu(_styleMenu);
//    _toolBar->addAction(_styleAction);

//    _aboutAction->setMenu(_aboutMenu);
//    _toolBar->addAction(_aboutAction);

//    this->addToolBar(_toolBar);


    this->setCentralWidget(_spliterMainView);

}

MainWindow::~MainWindow()
{
    delete ui;
}

