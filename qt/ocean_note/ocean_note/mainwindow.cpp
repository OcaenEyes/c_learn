
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "about.h"
#include <QToolBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://favicon.ico"));

    setWindowTitle("OCEAN NOTE");
    // 创建菜单栏
    menuBar = new QMenuBar(this);

    // 添加菜单栏到主窗口中
    this->setMenuBar(menuBar);

    QMenu *menu1 = new QMenu("文件",this);
    QMenu *menu2 = new QMenu("编辑",this);
    QMenu *menu3 = new QMenu("样式",this);
    QMenu *menu4 = new QMenu("关于",this);

    menuBar ->addMenu(menu1);
    menuBar ->addMenu(menu2);
    menuBar ->addMenu(menu3);
    menuBar ->addMenu(menu4);

    QAction *action1 = new QAction("新建",this);
    action1->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    connect(action1,SIGNAL(triggered(bool)),this,SLOT(on_actionnewfile_triggered()));

    QAction *action2 = new QAction("打开",this);
    action2->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    connect(action2,SIGNAL(triggered(bool)),this,SLOT(on_actionopenfile_triggered()));

    QAction *action12 = new QAction("保存",this);
    connect(action12,SIGNAL(triggered(bool)),this,SLOT(on_SaveFile_triggered()));

    QAction *action3 = new QAction("退出",this);
    connect(action3,SIGNAL(triggered(bool)),this,SLOT(on_actionexit_triggered()));

    QAction *action4 = new QAction("复制",this);
    action4->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    connect(action4,SIGNAL(triggered(bool)),this,SLOT(on_actioncopy_triggered()));

    QAction *action5 = new QAction("粘贴",this);
    action5->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_V));
    connect(action5,SIGNAL(triggered(bool)),this,SLOT(on_actionpatse_triggered()));

    QAction *action6 = new QAction("撤销",this);
    connect(action6,SIGNAL(triggered(bool)),this,SLOT(on_actionundo_triggered()));

    QAction *action7 = new QAction("恢复",this);
    connect(action7,SIGNAL(triggered(bool)),this,SLOT(on_actionredo_triggered()));

    QAction *action8 = new QAction("字体",this);
    connect(action8,SIGNAL(triggered(bool)),this,SLOT(on_actionfont_triggered()));

    QAction *action9 = new QAction("颜色",this);
    connect(action9,SIGNAL(triggered(bool)),this,SLOT(on_actioncolor_triggered()));

    QAction *action10 = new QAction("关于作者",this);
    connect(action10,SIGNAL(triggered(bool)),this,SLOT(on_about()));

    QAction *action11 = new QAction("帮助",this);
    connect(action11,SIGNAL(triggered(bool)),this,SLOT(on_help()));

    menu1->addAction(action1);
    menu1->addAction(action2);//菜单添加标签
    menu1->addAction(action12);//菜单添加标签
    menu1->addSeparator();//插入分割线
    QMenu *menu10 = new QMenu("最近访问的文件",this);
    menu1->addMenu(menu10);//添加二级菜单
    menu10->addAction(new QAction("暂无最近打开项目",this));//二级菜单添加菜单项
    menu1->addAction(action3);

    menu2->addAction(action4);
    menu2->addAction(action5);
    menu2->addAction(action6);
    menu2->addAction(action7);

    menu3->addAction(action8);
    menu3->addAction(action9);

    menu4->addAction(action10);
    menu4->addAction(action11);


    /* 工具栏 */
    toolBar = new QToolBar(this);

    this->addToolBar(Qt::TopToolBarArea,toolBar);

    toolBar ->setFloatable(false);
    toolBar -> setMovable(false);
    toolBar ->setToolButtonStyle(Qt::ToolButtonTextOnly);

    // 创建工具项
    QAction *action13 = new QAction("打开",this);
    // 槽函数与信号的连接
    connect(action13,SIGNAL(triggered(bool)),this,SLOT(on_actionopenfile_triggered()));

    QAction *action14 = new QAction("保存",this);
    connect(action14,SIGNAL(triggered(bool)),this,SLOT(on_SaveFile_triggered()));

    QAction *action15 = new QAction("撤回",this);
    connect(action15,SIGNAL(triggered(bool)),this,SLOT(on_actionundo_triggered()));

    QAction *action16 = new QAction("剪切",this);
    connect(action16,SIGNAL(triggered(bool)),this,SLOT(on_actioncut_triggered()));

    QAction *action17 = new QAction("粗体",this);
    connect(action17,SIGNAL(triggered(bool)),this,SLOT(on_actionTextBold_triggered()));

    QAction *action18 = new QAction("下划线",this);
    connect(action18,SIGNAL(triggered(bool)),this,SLOT(on_actionTextUnderLine_triggered()));

    QAction *action19 = new QAction("斜体",this);
    connect(action19,SIGNAL(triggered(bool)),this,SLOT(on_actionTextItalic_triggered()));

    QAction *action20 = new QAction("左对齐",this);
    connect(action20,SIGNAL(triggered(bool)),this,SLOT(on_actionLift_triggered()));

    QAction *action21 = new QAction("中对齐",this);
    connect(action21,SIGNAL(triggered(bool)),this,SLOT(on_actionCenter_triggered()));

    QAction *action22 = new QAction("右对齐",this);
    connect(action22,SIGNAL(triggered(bool)),this,SLOT(on_actionRight_triggered()));


    toolBar ->addAction(action13);
    toolBar ->addSeparator();
    toolBar ->addAction(action14);
    toolBar ->addSeparator();
    toolBar ->addAction(action15);
    toolBar ->addSeparator();
    toolBar ->addAction(action16);
    toolBar ->addSeparator();
    toolBar ->addAction(action17);
    toolBar ->addSeparator();
    toolBar ->addAction(action18);
    toolBar ->addSeparator();
    toolBar ->addAction(action19);
    toolBar ->addSeparator();
    toolBar ->addAction(action20);
    toolBar ->addSeparator();
    toolBar ->addAction(action21);
    toolBar ->addSeparator();
    toolBar ->addAction(action22);
    toolBar ->addSeparator();


    /* 状态栏 */
    QStatusBar * status = new QStatusBar();
    status ->setObjectName("状态栏");
    status ->setStyleSheet("QStatusBar::item{border:0px}");
    // 主窗口添加状态栏
    this->setStatusBar(status);
    //创建标签
    QLabel *statusLabel = new QLabel("ocean note", this);
    //状态栏添加信息
    status->showMessage("欢迎使用文本编辑器", 3000);//显示在左侧，并且3秒后自动消失
    status->addPermanentWidget(statusLabel);//添加右侧标签(永久性)

    /* 铆接部分*/
    QDockWidget *dockWidget = new QDockWidget();
    dockWidget -> setFeatures(QDockWidget::NoDockWidgetFeatures); // 设置铆接不可移动、不可关闭、不可浮动
    dockWidget ->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); // 设置允许左右停靠

    QLabel * titleLabel = new QLabel("lines");
    titleLabel->setAlignment(Qt::AlignCenter);
    dockWidget -> setTitleBarWidget(titleLabel);

    // 主窗口添加铆接部分
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidget);

    QListWidget *textList = new QListWidget(this);
    for(int i=1; i<=50; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString("%1").arg(i+1));
        textList->addItem(item);
        item->setTextAlignment(Qt::AlignRight);
    }
    textList->setFixedWidth(30);
    textList->setObjectName("文本列表");
    //设置没有水平以及垂直滑动条
    textList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //铆接部件添加内容主体
    dockWidget->setWidget(textList);

    /* 文本编辑框 */
    textEdit = new QTextEdit(this);
    textEdit -> setText("ocean note 文本编辑");
    textEdit -> setObjectName("文本输入");
    connect(textEdit,SIGNAL(textChanged()),this,SLOT(createFile()));
    QFont font = QFont("黑体",18,QFont::Normal,true);

    this->setCentralWidget(textEdit);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::saveCurrentData(QString filePath){
    QString ret= filePath;
    if(ret =="")
        ret = showFileDialog(QFileDialog::AcceptSave);
    if(ret !=""){
        QFile file(ret);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << textEdit ->toPlainText();
            file.close();
            setWindowTitle("OceanNote - ["+ret +"]");
        }else{
            ret ="";
        }
    }

    return ret;
}
void MainWindow::setCurrentFileName(const QString &filename){
    m_fileName = filename;
    textEdit->document() ->setModified(false);

    QString shownName;
    if(filename.isEmpty()){
        shownName = "untitled.txt";
    }else{
        shownName = QFileInfo(filename).fileName();
    }

    setWindowModified(false);
}
QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode){
    // 实现对文件对打开及保存
    QString ret = "";
    QFileDialog fd(this);
    QStringList filters;

    filters.append("Text Files (*.txt)");
    filters.append("All Files (*)");

    fd.setWindowTitle("文件");
    fd.setAcceptMode(mode);

    if(mode == QFileDialog::AcceptOpen){ //判断是打开文件还是保存文件
        fd.setFileMode(QFileDialog::ExistingFile); // 设置可选单个已存在的文件
    }

    if(fd.exec() == QFileDialog::Accepted){
        ret = fd.selectedFiles()[0]; // 函数返回装有选中的文件的 绝对路径链表
    }

    return ret;
}


void MainWindow::on_actionexit_triggered(){
    close();

} // 退出操作

void  MainWindow::on_actionopenfile_triggered(){
    QString path = showFileDialog(QFileDialog::AcceptOpen);
    setCurrentFileName(path);
    if(path ==""){
        QFile file(path);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            textEdit -> setPlainText(QString(file.readAll()));
            file.close();
            setWindowTitle("OceanNote - ["+ path+ "]");
        }else{

        }

    }

} // 打开文件操作

void  MainWindow::on_SaveFile_triggered(){
    QString path = saveCurrentData(m_fileName);
    if(path != ""){
        m_fileName =path;
    }
} // 保存文件操作

void  MainWindow::on_actionnewfile_triggered(){
    QMessageBox::StandardButton ok = QMessageBox::warning(this,tr("Waring"),
                                                          tr("创建新文件？"),
                                                          QMessageBox::Yes | QMessageBox::Default,
                                                          QMessageBox::No);
    m_fileName.clear();
    textEdit -> setText(QString());
    if(m_fileName == "" && ok == QMessageBox::StandardButton::Yes){
        m_fileName =  showFileDialog(QFileDialog::AcceptSave);
    }
} //创建新文件操作

void  MainWindow::on_actionundo_triggered(){
    textEdit->undo();
}//撤回操作

void  MainWindow::on_actionredo_triggered(){
    textEdit->redo();
}//恢复文件

void  MainWindow::on_actioncut_triggered(){
    textEdit ->cut();
}//剪切文件

void  MainWindow::on_actioncopy_triggered(){
    textEdit->copy();
}//复制文件

void  MainWindow::on_actionpatse_triggered(){
    textEdit->paste();
}//粘贴文件

// 设置光标的选区，使格式作用域选取内的字符
void MainWindow::mergeFormat(QTextCharFormat fmt){
    QTextCursor cursor = textEdit->textCursor();
    if(!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
}

void  MainWindow::on_actionTextUnderLine_triggered(){
    bool underlinecheck = true;
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlinecheck ? true:false);
    mergeFormat(fmt);
    underlinecheck = !underlinecheck;
}

void  MainWindow::on_actionTextItalic_triggered(){
    bool italiccheck = true;
    QTextCharFormat fmt;
    fmt.setFontItalic(italiccheck ? true:false);
    mergeFormat(fmt);
    italiccheck = !italiccheck;
}

void  MainWindow::on_actionTextBold_triggered(){
    bool boldcheck = true;
    QTextCharFormat fmt;
    fmt.setFontWeight(boldcheck ? QFont::Bold : QFont::Normal);
    mergeFormat(fmt);
    boldcheck = !boldcheck;
}

//对齐
void  MainWindow::on_actionLift_triggered(){
    textEdit->setAlignment(Qt::AlignLeft);
}

void  MainWindow::on_actionCenter_triggered(){
     textEdit->setAlignment(Qt::AlignCenter);
}

void  MainWindow::on_actionRight_triggered(){
     textEdit->setAlignment(Qt::AlignRight);
}

void  MainWindow::on_actioncolor_triggered(){
    QColor c = QColorDialog::getColor(color,this,"颜色选择");
    if(c.isValid()){
        color =c;
        // 设置文本框的文本颜色
        // 1.从光标开始新输入的文本颜色被设置
        // 2.鼠标选中的文本颜色设置
        textEdit->setTextColor(c);
    }
}//颜色操作

void  MainWindow::on_actionfont_triggered(){
    bool ok; // 用户字体对话框保存是否选择了字体

    QFont f = QFontDialog::getFont(&ok,font,this,"选择文本框要设置的字体");

    if(ok){
        font =f;

        // 1.从当前光标开始
        // 鼠标选中文本的字体
        textEdit->setCurrentFont(f);
    }
}

void  MainWindow::on_help(){
    QDesktopServices::openUrl(QUrl(QLatin1String("http://oceaneyes.top")));
}

void  MainWindow::on_about(){
    static About about;
    about.show();
}

void MainWindow::createFile(){}

//https://blog.csdn.net/ironjam/article/details/125582161
//https://blog.csdn.net/btufdycxyffd/article/details/126716115
//https://blog.csdn.net/qq_45775342/article/details/107368621
//https://blog.csdn.net/AAAA202012/article/details/120616329
//https://juejin.cn/post/7056678495040045093
