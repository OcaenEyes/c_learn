#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdwebview = new QWebEngineView(this);

    mdwebview->load(QUrl("qrc:/statics/index.html"));

    this->setCentralWidget(mdwebview);

}

MainWindow::~MainWindow()
{
    delete ui;
}

