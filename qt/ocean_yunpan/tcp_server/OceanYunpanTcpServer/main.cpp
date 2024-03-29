#include "tcpserver.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "operatedb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "OceanYunpanTcpServer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    OperateDB::getInstance().initDB();
    TcpServer w;
    w.show();
    return a.exec();
}
