#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick>

#include <QLocale>
#include <QTranslator>
#include "markdowncore.h"
#include "filelistmodel.h"

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)  
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QtWebEngineQuick::initialize();
    QGuiApplication app(argc, argv);

    //qmlRegisterType注册C++类型至QML
    //arg1:import时模块名
    //arg2:主版本号
    //arg3:次版本号
    //arg4:QML类型名
    qmlRegisterType<MarkDownCore>("MarkDownCore",1,0,"MarkDownCore");
    qmlRegisterType<FileListModel>("FileListModel",1,0,"FileListModel");

//    qmlRegisterUncreatableType<FileListModel>("FileListModel",1,0,"FileListModel","Cannot create a TreeView instance");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ocean_markdown_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
//    QAbstractItemModel* _fileListModel = new FileListModel();
//    engine.rootContext()->setContextProperty("_fileListModel",_fileListModel);
    const QUrl url(QStringLiteral("qrc:/layouts/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
