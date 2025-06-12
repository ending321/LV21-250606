#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSqlQueryModel>

class QueryWindow:public QDialog
{
    Q_OBJECT
public:
    QueryWindow(QWidget *parent=nullptr);
    ~QueryWindow();
};

#endif // QUERYWINDOW_H
