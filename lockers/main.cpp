#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "udpclient.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    UdpClient udpClient;              // 创建 UdpClient 实例，用于处理 UDP 通信
    QQmlApplicationEngine engine;
    // 将 udpClient 实例注册到 QML 上下文，使其在 QML 中可用
    engine.rootContext()->setContextProperty("udpClient", &udpClient);

    const QUrl url(QStringLiteral("qrc:/lockers/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
