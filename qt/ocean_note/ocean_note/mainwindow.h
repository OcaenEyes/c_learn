#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDockWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>//这些对话框可以实现较为基础的选择选项
#include <QFile>
#include <QStringConverter>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString m_fileName;
    QTextEdit *textEdit;
    QListWidget *textList;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QFont font;
    QColor color;

public:
    QString saveCurrentData(QString filePath);
    void setCurrentFileName(const QString &filename);
    QString showFileDialog(QFileDialog::AcceptMode mode);
    // 设置光标的选区，使格式作用域选取内的字符
    void mergeFormat(QTextCharFormat fmt);

public slots:
    void on_actionexit_triggered(); // 退出操作

    void on_actionopenfile_triggered(); // 打开文件操作

    void on_SaveFile_triggered(); // 保存文件操作

    void on_actionnewfile_triggered(); //创建新文件操作

    void on_actionundo_triggered();//撤回操作

    void on_actionredo_triggered();//恢复文件

    void on_actioncut_triggered();//剪切文件

    void on_actioncopy_triggered();//复制文件

    void on_actionpatse_triggered();//粘贴文件

    void on_actionTextUnderLine_triggered();

    void on_actionTextItalic_triggered();

    void on_actionTextBold_triggered();

    //对齐
    void on_actionLift_triggered();

    void on_actionCenter_triggered();

    void on_actionRight_triggered();

    void on_actioncolor_triggered();//颜色操作

    void on_actionfont_triggered();

    void on_help();

    void on_about();

    void createFile();
};
#endif // MAINWINDOW_H

