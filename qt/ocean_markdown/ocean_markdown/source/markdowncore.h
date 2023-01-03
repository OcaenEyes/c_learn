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

    QString _textIn= "# 欢迎使用～ \n [【个人网站】http://oceaneyes.top](http://oceaneyes.top)";

signals:
    void hasMarkdownIn();

public slots:
    QString markdown();
    void markdownIn(const QString &_text);
};

#endif // MARKDOWNCORE_H
