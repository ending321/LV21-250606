#ifndef DATABASE_HELPER_H
#define DATABASE_HELPER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QString>
#include<QSqlError>
#include<QMessageBox>
#include <QSqlQuery>

class DatabaseHelper
{
public:
    static DatabaseHelper& instance();

    bool initDatabase(const QString &dbPath);
    //bool isInitialized() const;

    bool addUser(const QString &name, int age, const QString &email);
    bool addOrder(int userId, const QString &product, double amount);
    //QString getConfig(const QString &key, const QString &defaultValue="");

    QSqlError lastError() const;

    //查询users orders表
    QSqlQuery queryUsers(const QString &condition, const QVariant &value);
    QSqlQuery queryOrders(const QString &condition, const QVariant &value);

private:
    DatabaseHelper();
    ~DatabaseHelper();
    //DatabaseHelper(const DatabaseHelper&)=delete;
    //DatabaseHelper& operator=(const DatabaseHelper&)=delete;

    bool m_initialized;
    QSqlError m_lastError;
};

#endif // DATABASE_HELPER_H
