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

    //功能按钮 - 数据库配置(示例：点击弹出对话框
    QPushButton *btnDbConfig = new QPushButton("数据库配置", this);
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
   // QPushButton *btnThreadTest = new QPushButton("多线程测试", this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
