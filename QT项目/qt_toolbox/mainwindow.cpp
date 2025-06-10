#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //基础界面设置
    setWindowTitle("QT 多功能工具集");
    setFixedSize(800, 600);

    //中心部件与布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget); //设置为中心部件

    //功能按钮 - 数据库配置(示例：点击弹出对话框
    QPushButton *btnDbConfig = new QPushButton("数据库配置", centralWidget);
    connect(btnDbConfig, &QPushButton::clicked, this, [=](){
        dialog_config dialog(this);
        if(dialog.exec()==QDialog::Accepted){
            //若对话框确认，可获取配置参数(如数据库路径)
            QString dbPath = dialog.getDbPath();    //假设dialog_config提供了getDbPath()方法
            QMessageBox::information(this, "配置成功","数据库路径已设为："+dbPath);
        }
    });
    layout->addWidget(btnDbConfig);

    // 功能按钮 - 多线程测试（模拟耗时操作）
    QPushButton *btnThreadTest = new QPushButton("多线程测试", this);
    connect(btnThreadTest, &QPushButton::clicked, this, [=](){
        WorkerThread *thread = new WorkerThread(this);

        //连接进度更新信号
        connect(thread, &WorkerThread::progressUpdated, this, [=](int value, const QString &message){
            progressBar->setValue(value);
            logTextEdit->append(message);
        });

        //连接结果完成信号
        connect(thread, &WorkerThread::resultReady, this, [=](const QString &result){
            progressBar->setValue(100);
            logTextEdit->append(result);
            QMessageBox::information(this, "线程完成", result);
            thread->deleteLater();
        });
        //重置UI状态
        progressBar->setValue(0);
        logTextEdit->clear();

        thread->start();
    });
    layout->addWidget(btnThreadTest);

    //添加进度条
    progressBar = new QProgressBar(centralWidget);
    progressBar->setRange(0,100);
    progressBar->setValue(0);
    layout->addWidget(progressBar);

    //添加日志显示区域
    logTextEdit = new QTextEdit(centralWidget);
    logTextEdit->setReadOnly(true);
    layout->addWidget(logTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
