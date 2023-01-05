#ifndef MARKDOWNCORE_H
#define MARKDOWNCORE_H

#include <QObject>
#include <QFile>

class MarkDownCore : public QObject
{
    Q_OBJECT
public:
    explicit MarkDownCore(QObject *parent = nullptr);

    //宏声明了一个可以从QML访问的属性
    Q_PROPERTY(QString mdRes READ markdown WRITE markdownIn NOTIFY textInChanged)

    Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)

    QString _textIn= "# 欢迎使用～ \n [【个人网站】http://oceaneyes.top](http://oceaneyes.top)";


signals:
    void textInChanged();
    void fileNameChanged();

private:
    QString _fName;

public slots:
    QString markdown();
    void markdownIn(const QString &_text);

    QString getFileName();
    void setFileName(const QString &_fileName);

    void readFileContent();
};

#endif // MARKDOWNCORE_H
