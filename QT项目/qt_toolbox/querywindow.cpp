#include "querywindow.h"


QueryWindow::QueryWindow(QWidget *parent):QDialog(parent) {
    //窗口基础设置
    setWindowTitle("数据库查询工具");
    resize(800,600);
    setMinimumSize(800,600);

    //创建查询控件
    QLabel *lblQuery = new QLabel("数据库查询:", this);
    lblQuery->setStyleSheet("font-weight: bold; font-size: 14px;");

    cbQueryTable = new QComboBox(this);
    cbQueryTable->addItems({"用户表(users)", "订单表(orders)"});
    cbQueryTable->setMinimumWidth(120);

    cbQueryCondition = new QComboBox(this);
    cbQueryCondition->addItems({"ID", "名称", "邮箱", "商品", "金额"});
    cbQueryCondition->setMinimumWidth(100);

    leQueryValue = new QLineEdit(this);
    leQueryValue->setPlaceholderText("输入查询值");
    leQueryValue->setMinimumWidth(200);

    btnQuery = new QPushButton("执行查询", this);
    btnQuery->setMinimumWidth(100);
    connect(btnQuery, &QPushButton::clicked, this, &QueryWindow::handleQuery);

    // 结果显示表格
    tvQueryResult = new QTableView(this);
    tvQueryResult->setEditTriggers(QAbstractItemView::NoEditTriggers);  //NoEditTriggers 表示禁用用户编辑
    tvQueryResult->setSelectionBehavior(QAbstractItemView::SelectRows); //设置为行选择模式，用户点击任意单元格时，整行都会被选中。
    tvQueryResult->setStyleSheet("QTableView { border: 1px solid #ccc; }");
    tvQueryResult->setMinimumHeight(300);

    // 创建布局
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(lblQuery);
    headerLayout->addWidget(cbQueryTable);
    headerLayout->addWidget(cbQueryCondition);
    headerLayout->addWidget(leQueryValue);
    headerLayout->addWidget(btnQuery);
    headerLayout->setSpacing(10);
    headerLayout->setContentsMargins(20, 20, 20, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(tvQueryResult);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 初始化模型
    model = new QSqlQueryModel(this);
    tvQueryResult->setModel(model);
}
QueryWindow::~QueryWindow()
{
    delete model;
}

void QueryWindow::handleQuery()
{
    // 获取查询参数
    QString table = cbQueryTable->currentText().contains("用户") ? "users" : "orders";
    QString condition = cbQueryCondition->currentText();
    QString value = leQueryValue->text().trimmed();

    // 调试输出 - 确认查询参数
    //qDebug() << "查询表:" << table << ", 条件:" << condition << ", 值:" << value;

    // 输入验证
    if (value.isEmpty()) {
        QMessageBox::warning(this, "查询错误", "请输入查询值");
        return;
    }

    // 检查数据库连接
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, "连接错误", "请先配置数据库连接");
        return;
    }

    // 执行查询
    QSqlQuery query;
    DatabaseHelper &dbHelper = DatabaseHelper::instance();

    if (table == "users") {
        if (condition == "ID") {
            query = dbHelper.queryUsers("id", value.toInt());
        } else if (condition == "名称") {
            query = dbHelper.queryUsers("name", "%" + value + "%"); // 添加模糊查询
        } else if (condition == "邮箱") {
            query = dbHelper.queryUsers("email", "%" + value + "%"); // 添加模糊查询
        }
    } else if (table == "orders") {
        if (condition == "ID") {
            query = dbHelper.queryOrders("order_id", value.toInt());
        } else if (condition == "商品") {
            query = dbHelper.queryOrders("product", "%" + value + "%"); // 添加模糊查询
        } else if (condition == "金额") {
            query = dbHelper.queryOrders("amount", value.toDouble());
        }
    }

    // 显示查询结果
    model->setQuery(std::move(query));
    tvQueryResult->setModel(model);
    tvQueryResult->resizeColumnsToContents();

    // 错误处理
    QSqlError error = dbHelper.lastError();
    if (error.isValid()) {
        QMessageBox::critical(this, "查询失败", "执行失败: " + error.text());
    } else if (model->rowCount() == 0) {
        QMessageBox::information(this, "查询结果", "未找到匹配记录");
    }
}
