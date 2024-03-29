#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick>


#include <QLocale>
#include <QTranslator>
#include "markdowncore.h"
#include "filelistmodel.h"
#include "filefolderpathindir.h"

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
    qmlRegisterType<FileFolderPathInDir>("FileFolderPathInDir",1,0,"FileFolderPathInDir");


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
//    qDebug() << "启动参数argc:"<< argc<<Qt::endl;
//    qDebug() << "启动参数argv:"<<qApp->arguments()<<Qt::endl;
//    qDebug() << "启动参数argv:"<<qApp->arguments().count()<<Qt::endl;
//    qDebug() << "启动参数argv:"<<qApp->arguments().at(0)<<Qt::endl;

    if(argc ==2){
        auto root = engine.rootObjects();
        qDebug() << "启动root:"<<root <<Qt::endl;
        auto mainWindowQml = root.first()->findChild<QObject*>("mainWindow");
        mainWindowQml->setProperty("curFileUrl",qApp->arguments().at(1));
        qDebug() <<qApp->arguments().at(1) << Qt::endl;
        QMetaObject::invokeMethod(mainWindowQml, "readLoaclFileByPath", Q_ARG(QString,qApp->arguments().at(1) ));
    }


    return app.exec();
}
