#include "database_helper.h"
#include <QSqlDatabase>
#include <QSqlQuery>


DatabaseHelper::DatabaseHelper() {}

DatabaseHelper::~DatabaseHelper()
{
}

DatabaseHelper &DatabaseHelper::instance()
{
    static DatabaseHelper helper;
    return helper;
}

bool DatabaseHelper::initDatabase(const QString &dbPath)
{
    //创建SQLite数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    //打开数据库
    if(!db.open()){
        qDebug()<<"数据库打开失败:"<<db.lastError().text();
        return false;
    }
    //创建配置表（如果不在）
    //启用外键约束(SQLite默认不启用)
    QSqlQuery query;
    if(!query.exec("PRAGMA foreign_keys = ON")){
        qDebug()<<"启用外键约束失败："<<query.lastError().text();
        //外键约束失败不影响后续操作，继续执行
    }
    // 创建 users 表
    bool ok = query.exec(    "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                         " name TEXT NOT NULL,"
                         " age INTEGER,"
                         " email TEXT UNIQUE)");
    if(!ok){
        qDebug()<<"创建users表失败："<<query.lastError().text();
    }
    // 创建 orders 表，关联 users 表
    ok = query.exec("CREATE TABLE IF NOT EXISTS orders (order_id INTEGER PRIMARY KEY,"
                    " user_id INTEGER,"
                    " product TEXT,"
                    " amount REAL,"
                    " order_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                    " FOREIGN KEY (user_id) REFERENCES users(id))");
    if(!ok){
        qDebug()<<"创建orders表失败："<<query.lastError().text();
    }
    return true;
}

bool DatabaseHelper::addUser(const QString &name, int age, const QString &email)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO users (name, age, email) "
                  "VALUES(:name, :age, :email)");
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":email", email);

    if(!query.exec()){
        qDebug()<<"添加用户失败:"<<query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseHelper::addOrder(int userId, const QString &product, double amount)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO orders (user_id, product, amount) "
                  "VALUES(:user_id, :product, :amount)");
    query.bindValue(":user_id", userId);
    query.bindValue(":product", product);
    query.bindValue(":amount", amount);

    if(!query.exec()){
        qDebug()<<"添加订单失败:"<<query.lastError().text();
        return false;
    }
    return true;
}



QSqlError DatabaseHelper::lastError() const
{
    return m_lastError;
}


