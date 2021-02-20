#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "StreamTarget.h"
#include "StreamSource.h"
#include "FpsCounter.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<StreamSource>("com.dln.streaming", 1, 0, "CppStreamSource");
    qmlRegisterType<StreamTarget>("com.dln.streaming", 1, 0, "StreamTarget");
    qmlRegisterType<FpsCounter>("com.dln.common", 1, 0, "FpsCounter");

    engine.load(QUrl("qrc:/SourceWindow.qml"));
    engine.load(QUrl("qrc:/TargetWindow.qml"));

    return app.exec();
}
