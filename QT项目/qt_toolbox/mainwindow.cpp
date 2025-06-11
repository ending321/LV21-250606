#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

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
/*
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
*/
    //----------------------数据库操作控件----------------------
    //数据库配置按钮
    QPushButton *btnDbConfig = new QPushButton("数据库配置", this);
    connect(btnDbConfig, &QPushButton::clicked, this, [=](){
        dialog_config dialog(this);
        if(dialog.exec()==QDialog::Accepted){
            QString dbPath = dialog.getDbPath();
            //初始化数据库
            if(DatabaseHelper::instance().initDatabase(dbPath)){
                QMessageBox::information(this, "配置成功", "数据库路径已设为:"+dbPath);
            }else{
                QSqlError error=DatabaseHelper::instance().lastError();
                QMessageBox::critical(this, "配置失败","数据库初始化失败"+error.text());
            }
        }
    });
    layout->addWidget(btnDbConfig);

    //用户信息输入控件
    QLabel *lbUserName = new QLabel("用户名:", centralWidget);
    leUserName = new QLineEdit(centralWidget);
    leUserName->setPlaceholderText("请输入用户名");

    QLabel *lbUserAge = new QLabel("年龄", centralWidget);
    leUserAge = new QLineEdit(centralWidget);
    leUserAge->setPlaceholderText("请输入年龄");

    QLabel *lbUserEmail = new QLabel("邮箱", centralWidget);
    leUserEmail = new QLineEdit(centralWidget);
    leUserEmail->setPlaceholderText("请输入邮箱");

    //添加用户按钮
    btnAddUser = new QPushButton("添加用户", this);
    connect(btnAddUser, &QPushButton::clicked, this, [=](){
        QString name = leUserName->text().trimmed();
        if(name.isEmpty()){
            QMessageBox::warning(this,"输入错误","用户名不能为空");
            return;
        }

        bool ok;
        int age = leUserAge->text().toInt(&ok);
        if(!ok||age<0){
            QMessageBox::warning(this,"输入错误","请输入有效的年龄");
            return;
        }

        QString email = leUserEmail->text().trimmed();
        if(email.isEmpty()){
            QMessageBox::warning(this,"输入错误","邮箱不能为空");
            return;
        }

        //调用DatabaseHelper添加用户
        if(DatabaseHelper::instance().addUser(name,age,email)){
            QMessageBox::information(this,"成功","用户添加成功");
            //清空输入框
            leUserName->clear();
            leUserAge->clear();
            leUserEmail->clear();
        }else{
            QSqlError error=DatabaseHelper::instance().lastError();
            QMessageBox::critical(this,"失败","添加用户失败:"+error.text());
        }
    });

    //-------------------------------------------------------
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
