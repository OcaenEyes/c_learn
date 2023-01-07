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

    Q_PROPERTY(QString newFileName READ getNewFileName WRITE setNewFileName NOTIFY newFileNameChanged)

    QString _textIn= "\n## 欢迎使用~\n\n\n**# 桌面应用：📙OceanMarkdown**\n\n++*👋本版本为测试版，功能还在优化中~🤔*++\n\n\n    "
                     "1.文档新建、打开文档、保存\n    "
                     "2.编辑、预览、一键清空\n    "
                     "3.标题、引用、粗体、斜体、\n    "
                     "5.标记、上标、下标、下划线、删除线\n    "
                     "6.表格\n    "
                     "7.图片\n   "
                     " 8.链接\n    "
                     "9.有序编号、无序编号\n    "
                     "10.代码\n    "
                     "12.数学公式\n\n"
                     "**# 关于作者**\n"
                     "##### 👋 读书城南，🤔 在未来面前，我们都是孩子～\n\n"
                     "- 📙 一个热衷于探索学习新方向、新事物的智能产品经理，闲暇时间喜欢coding💻、画图🎨、音乐🎵、学习ing~\n  \n"
                     "##### 👋 Social Media\n\n"
                     "- 🛠️ Blog: [http://oceaneyes.top](http://oceaneyes.top)\n\n"
                     "- ⚡ PM导航: [https://pmhub.oceangzy.top](https://pmhub.oceangzy.top)\n\n"
                     "- ☘️ CNBLOG: [https://www.cnblogs.com/oceaneyes-gzy/](https://www.cnblogs.com/oceaneyes-gzy/)\n\n"
                     "- 🌱 AI PRJ自己部署的一些算法demo: [http://ai.oceangzy.top/](http://ai.oceangzy.top/)\n\n"
                     "- 📫 Email: 1450136519@qq.com\n\n"
                     "- 💬 WeChat: [OCEANGZY](https://oceaneyes.top/img/wechatqrcode.jpg )\n\n"
                     "- 💬 公众号: [UncleJoker-GZY](https://oceaneyes.top/img/wechatgzh.jpeg)\n  \n"
                     "##### 👋 感谢打赏~\n  \n  "
                     "<img src=\"https://oceaneyes.top/img/alipay.jpg\" title=\"支付宝打赏\" alt=\"\" style=\"width:140px;display:inline-block\" >\n \n  "
                     "<img src=\"https://oceaneyes.top/img/wechatpay.jpg\" title=\"微信打赏\" alt=\"\" style=\"width:140px;display:inline-block\" >\n \n";

    Q_INVOKABLE void saveFile(const QString &_text);


signals:
    void textInChanged();
    void fileNameChanged();
    void newFileNameChanged();

private:
    QString _fName;

public slots:
    QString markdown();
    void markdownIn(const QString &_text);

    QString getFileName();
    void setFileName(const QString &_fileName);
    void saveFile();

    QString getNewFileName();
    void setNewFileName(const QString &_fileName);

    void readFileContent();
};

#endif // MARKDOWNCORE_H
