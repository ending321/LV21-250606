#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QSqlQuery>
#include"database_helper.h"

class QueryWindow:public QDialog
{
    Q_OBJECT
public:
    QueryWindow(QWidget *parent=nullptr);
    ~QueryWindow();

private slots:
    void handleQuery();

private:
    //查询功能相关控件
    QComboBox *cbQueryTable;       // 选择查询表
    QComboBox *cbQueryCondition;   // 选择查询条件
    QLineEdit *leQueryValue;       // 查询值输入
    QPushButton *btnQuery;         // 查询按钮
    QTableView *tvQueryResult;     // 显示查询结果
    QSqlQueryModel *model;
};

#endif // QUERYWINDOW_H
