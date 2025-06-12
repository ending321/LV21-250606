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
        //m_lastError = db.lastError();  // 记录错误
        qDebug()<<"数据库打开失败:"<<db.lastError().text();
        return false;
    }
    //创建配置表（如果不在）
    //启用外键约束(SQLite默认不启用)
    QSqlQuery query;
    if(!query.exec("PRAGMA foreign_keys = ON")){
        //m_lastError = query.lastError();  // 记录错误
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
    ok = query.exec("CREATE TABLE IF NOT EXISTS orders (order_id INTEGER PRIMARY KEY AUTOINCREMENT,"
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
        m_lastError = query.lastError();  // 记录错误
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
        m_lastError = query.lastError();  // 记录错误
        qDebug()<<"添加订单失败:"<<query.lastError().text();
        return false;
    }
    return true;
}



QSqlError DatabaseHelper::lastError() const
{
    return m_lastError;
}

QSqlQuery DatabaseHelper::queryUsers(const QString &condition, const QVariant &value)
{
    QSqlQuery query;
    QString sql;
    bool querySuccess = false;

    //记录当前数据库连接状态
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()){
            m_lastError = QSqlError("数据库未打开", "请先初始化数据库连接",QSqlError::ConnectionError);
            return query;
        }

    if(condition == "id"){
        sql = "SELECT * FROM users WHERE id = :value";
        query.prepare(sql);
        query.bindValue(":value", value);
        querySuccess = query.exec();
    }else if(condition == "name"){
        sql = "SELECT * FROM users WHERE name LIKE :value";
        query.prepare(sql);
        query.bindValue(":value", value);
        querySuccess = query.exec();
    }else if(condition == "email"){
        sql = "SELECT * FROM users WHERE email LIKE :value";
        query.prepare(sql);
        query.bindValue(":value", value);
        querySuccess = query.exec();
    }else{
        m_lastError = QSqlError("无效的查询条件", "支持的查询条件：id, name, email",QSqlError::UnknownError);
        return query;
    }

    //处理查询执行结果
    if(!querySuccess){
        m_lastError = query.lastError();
        qDebug() << "查询用户失败: " << m_lastError.text();
        qDebug() << "SQL语句: " << sql;
    }else{
        m_lastError = QSqlError();//清空错误
    }
    return query;
}

QSqlQuery DatabaseHelper::queryOrders(const QString &condition, const QVariant &value)
{
    QSqlQuery query;
    QString sql;
    bool querySuccess = false;

    if (condition == "order_id") {
        sql = "SELECT * FROM orders WHERE order_id = :value";
        query.prepare(sql);
        query.bindValue(":value", value);
        querySuccess = query.exec();
    } else if (condition == "product") {
        sql = "SELECT * FROM orders WHERE product LIKE :value";
        query.prepare(sql);
        query.bindValue(":value", "%" + value.toString() + "%");
        querySuccess = query.exec();
    } else if (condition == "amount") {
        sql = "SELECT * FROM orders WHERE amount = :value";
        query.prepare(sql);
        query.bindValue(":value", value);
        querySuccess = query.exec();
    }else{
        m_lastError = QSqlError("无效的查询条件", "支持的查询条件：order_id, product, amount");
        return query;
    }

    //处理查询执行结果
    if(!querySuccess){
        m_lastError = query.lastError();
        qDebug() << "查询订单失败: " << m_lastError.text();
        qDebug() << "SQL语句: " << sql;
    }else{
        m_lastError = QSqlError();//清空错误
    }
    return query;
}
