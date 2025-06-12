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

    //添加打开查询窗口的按钮
    QPushButton *btnOpenQueryWindow = new QPushButton("打开数据库查询", this);
    connect(btnOpenQueryWindow, &QPushButton::clicked, this, [=](){
        QueryWindow queryWindow(this);
        queryWindow.exec();
    });
    layout->addWidget(btnOpenQueryWindow);
/*
    //--------------------- 查询功能控件 ---------------------
    QLabel *lblQuery = new QLabel("数据库查询:", centralWidget);
    lblQuery->setStyleSheet("font-weight:bold;");

    //查询表选择
    cbQueryTable = new QComboBox(centralWidget);
    cbQueryTable->addItems({"用户表(users)", "订单表(orders)"});

    //查询条件选择
    cbQueryCondition = new QComboBox(centralWidget);
    cbQueryCondition->addItems({"ID", "名称", "邮箱", "商品", "金额"});

    //查询值输入
    leQueryValue = new QLineEdit(centralWidget);
    leQueryValue->setPlaceholderText("输入查询值");

    //查询按钮
    btnQuery = new QPushButton("执行查询", centralWidget);
    connect(btnQuery, &QPushButton::clicked, this, &MainWindow::handleQuery);

    //结果显示表格
    tvQueryResult = new QTableView(centralWidget);
    tvQueryResult->setEditTriggers(QAbstractItemView::NoEditTriggers);  //NoEditTriggers 表示禁用用户编辑
    tvQueryResult->setSelectionBehavior(QAbstractItemView::SelectRows);     //设置为行选择模式，用户点击任意单元格时，整行都会被选中。
    tvQueryResult->setStyleSheet("QTableView { border: 1px solid #ccc; }");
    tvQueryResult->setMinimumHeight(200);   //设置最小高度，确保表格可见

    //创建查询容器和布局
    QWidget *queryContainer = new QWidget(centralWidget);
    QVBoxLayout *queryContainerLayout = new QVBoxLayout(queryContainer);

    //将查询控件添加到布局
    QHBoxLayout *queryHeaderLayout = new QHBoxLayout();
    queryHeaderLayout->addWidget(lblQuery);
    queryHeaderLayout->addWidget(cbQueryTable);
    queryHeaderLayout->addWidget(cbQueryCondition);
    queryHeaderLayout->addWidget(leQueryValue);
    queryHeaderLayout->addWidget(btnQuery);
    //layout->addLayout(queryHeaderLayout);
    //layout->addWidget(tvQueryResult);

    //使用垂直分割器或设置拉伸因子，确保表格有足够空间
    queryContainerLayout->addLayout(queryHeaderLayout);
    queryContainerLayout->addWidget(tvQueryResult);
    queryContainerLayout->setContentsMargins(0, 0, 0, 0);
    // 设置拉伸因子，让查询容器占据更多空间
    layout->addWidget(queryContainer, 1); // 1表示拉伸因子，数值越大占据空间越多
*/
    //--------------------------------------------------------
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

    //订单信息输入控件
    QLabel *lblOrderProduct = new QLabel("商品名称:", centralWidget);
    leOrderProduct = new QLineEdit(centralWidget);
    leOrderProduct->setPlaceholderText("请输入商品名称");

    QLabel *lblOrderAmount = new QLabel("订单金额:", centralWidget);
    leOrderAmount = new QLineEdit(centralWidget);
    leOrderAmount->setPlaceholderText("请输入订单金额");

    QLabel *lblUserId = new QLabel("用户ID:", centralWidget);
    leUserId = new QLineEdit(centralWidget);
    leUserId->setPlaceholderText("请输入用户ID");

    //添加订单按钮
    btnAddOrder = new QPushButton("添加订单", centralWidget);
    connect(btnAddOrder, &QPushButton::clicked, this, [=](){
        bool ok;
        int userId = leUserId->text().toInt(&ok);   //用于将字符串转换为整数。&ok 是一个布尔变量的引用，用于存储转换结果的状态true false
        if(!ok || userId<=0){
            QMessageBox::warning(this,"输入错误", "请输入有效的用户ID");
            return;
        }
        QString product = leOrderProduct->text().trimmed(); //trimmed()仅去除首尾空格，中间空格保留与simplified()有区别
        if (product.isEmpty()) {
            QMessageBox::warning(this, "输入错误", "商品名称不能为空");
            return;
        }

        double amount = leOrderAmount->text().toDouble(&ok);
        if (!ok || amount <= 0) {
            QMessageBox::warning(this, "输入错误", "请输入有效的订单金额");
            return;
        }

        //调用DatabaseHelper添加订单
        if(DatabaseHelper::instance().addOrder(userId, product, amount)){
            QMessageBox::information(this,"成功","订单添加成功");
            //清空输入框
            leUserId->clear();
            leOrderProduct->clear();
            leOrderAmount->clear();
        }else{
            QSqlError error = DatabaseHelper::instance().lastError();
            QMessageBox::critical(this, "失败", "添加订单失败：" + error.text());
        }
    });

    //将数据库操作控件添加到布局(使用表单布局使界面更整齐)
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(lbUserName, leUserName);
    formLayout->addRow(lbUserAge, leUserAge);
    formLayout->addRow(lbUserEmail, leUserEmail);
    formLayout->addRow(btnAddUser);
    formLayout->addRow(lblUserId, leUserId);
    formLayout->addRow(lblOrderProduct, leOrderProduct);
    formLayout->addRow(lblOrderAmount, leOrderAmount);
    formLayout->addRow(btnAddOrder);

    layout->addLayout(formLayout);

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

/*
void MainWindow::handleQuery()
{
    //获取查询参数
    QString table = cbQueryTable->currentText().contains("用户")?"users":"orders";    //查询表
    QString condition = cbQueryCondition->currentText();    //查询条件(currentText()是获取当前文本)
    QString value = leQueryValue->text().trimmed();     //查询输入

    if(value.isEmpty()){
        QMessageBox::warning(this,"查询错误", "请输入查询值");
        return;
    }

    //根据表和条件构建查询
    QSqlQuery query;
    DatabaseHelper &dbHelper = DatabaseHelper::instance();

    if(table == "users"){
        if(condition == "ID"){
            query = dbHelper.queryUsers("id", value.toInt());
        }else if(condition == "名称"){
            query = dbHelper.queryUsers("name", value);
        }else if (condition == "邮箱"){
            query = dbHelper.queryUsers("email", value);
        }
    }else if (table == "orders"){
        if (condition == "ID") {
           query = dbHelper.queryOrders("order_id", value.toInt());
        }else if (condition == "商品") {
            query = dbHelper.queryOrders("product", value);
        }else if (condition == "金额") {
            query = dbHelper.queryOrders("amount", value.toDouble());
        }
    }

    // 显示查询结果
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(std::move(query));
    tvQueryResult->setModel(model);     //将模型关联到表格视图控件（QTableView）
    tvQueryResult->resizeColumnsToContents();   //自适应列宽

    //检查查询是否有错误（从 DatabaseHelper 的 lastError 判断，更准确）
    QSqlError error = dbHelper.lastError();
    if(error.isValid())    //用于判断是否存在有效的错误信息,用来检测 “有没有实际的数据库错误发生”。
    {
        QMessageBox::critical(this,"查询失败","查询执行失败:"+error.text());
    }
}
*/
