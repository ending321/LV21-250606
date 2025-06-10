#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H
#include <QMainWindow>
#include <QWidget>
#include<QString>
#include<QThread>
#include<QDebug>
class WorkerThread:public QThread
{
private:
    Q_OBJECT
public:
    WorkerThread(QObject *parent = nullptr);  //可以加explicit禁止构造函数隐式转换
    void run()override; //重写覆盖父类QThread的run函数
signals:
    void resultReady(const QString &result);
    void progressUpdated(int value, const QString &message); //进度更新信号
};

#endif // WORKER_THREAD_H
