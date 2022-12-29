#ifndef MARKDOWNCORE_H
#define MARKDOWNCORE_H

#include <QObject>

class MarkDownCore : public QObject
{
    Q_OBJECT
public:
    explicit MarkDownCore(QObject *parent = nullptr);

//    Q_INVOKABLE void fontDesign ();
    //宏声明了一个可以从QML访问的属性
    Q_PROPERTY(QString mdRes READ markdown WRITE markdownIn NOTIFY hasMarkdownIn)

    QString _textIn= "欢迎使用～";

signals:
    void hasMarkdownIn();
    void fontBold();
    void fontUnderLine();
    void fontItalic();
    void fontLeftAlign();
    void fontCenterAlign();
    void fontRightAlign();

public slots:
    void fontDesign();
    QString markdown();
    void markdownIn(const QString &_text);
    void setFontBold();
    void setFontUnderLine();
    void setFontItalic();
    void setFontLeftAlign();
    void setFontCenterAlign();
    void setFontRightAlign();

};

#endif // MARKDOWNCORE_H
