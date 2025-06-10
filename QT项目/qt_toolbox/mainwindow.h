#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"dialog_config.h"
#include"worker_thread.h"
#include"database_helper.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QMessageBox>
#include<QDialog>
#include <QProgressBar>
#include <QTextEdit>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProgressBar *progressBar;  // 进度条
    QTextEdit *logTextEdit; // 日志显示区域

    //database_helper使用到的输控件指针，用于输入用户信息的编辑框
    QLineEdit *leUserName;
    QLineEdit *leUserAge;
    QLineEdit *leUserEmail;
    QLineEdit *leOrderProduct;
    QLineEdit *leOrderAmount;
    QPushButton *btnAddUser;
    QPushButton *btnAddOrder;

};
#endif // MAINWINDOW_H
