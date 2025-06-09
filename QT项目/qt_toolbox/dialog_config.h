#ifndef DIALOG_CONFIG_H
#define DIALOG_CONFIG_H

#include <QMainWindow>
#include <QWidget>
#include<QFormLayout>
#include<QLineEdit>
#include<QDialogButtonBox>
#include<QDialog>

class dialog_config:public QDialog
{
    Q_OBJECT    // 加在这：private区域（默认class类成员是private）、类定义开头、继承QObject后
    QString m_dbPath;  // 存储用户设置的数据库路径
    QLineEdit *editDbPath;

public:
    dialog_config(QWidget *parent = nullptr);
    QString getDbPath() const;  //获取数据库路径的公共接口

private slots:
    void saveDbPath();//保存路径的槽函数
};

#endif // DIALOG_CONFIG_H
