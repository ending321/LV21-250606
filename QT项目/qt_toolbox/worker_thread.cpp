#include "worker_thread.h"

WorkerThread::WorkerThread(QObject *parent):QThread(parent) {}

void WorkerThread::run(){
    //模拟耗时操作（比如批量读取10个文件）
    for (int i = 0; i < 10; ++i) {
        //qDebug() << "线程中：模拟处理第" << i << "个任务";
        QString message = QString("处理第%1个任务").arg(i);
        emit progressUpdated(i*10, message);
        QThread::sleep(1); // 休眠1秒，模拟耗时
    }
    emit resultReady("多线程任务完成！");
}
