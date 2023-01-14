#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _spliterMainView = new QSplitter(Qt::Horizontal, 0); //新建主分割窗口，水平分割

    _fileTree = new QTreeView(_spliterMainView);
    _fileModel = new QFileSystemModel;
    _fileModel->setRootPath(QDir::currentPath());
    _fileTree->setModel(_fileModel);

    QSplitter *_splitterRight = new QSplitter(Qt::Vertical, _spliterMainView);   //右分割窗口，并以主分割窗口作为父窗口
    _mdwebview = new QWebEngineView(_splitterRight);
    _mdwebview->load(QUrl("qrc:/statics/index.html"));

    _spliterMainView->setStretchFactor(1,1);
    this->setCentralWidget(_spliterMainView);

}

MainWindow::~MainWindow()
{
    delete ui;
}

