#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QWebEngineView>
#include <QTreeView>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QFileSystemModel>
#include "filelistmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWebEngineView *_mdwebview;
    QSplitter *_spliterMainView;
    QTreeView *_fileTree;
    QFileSystemModel *_fileModel;
    QMenuBar *_menuBar;
    QToolBar *_toolBar;
    FileListModel *_fileListModel;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
