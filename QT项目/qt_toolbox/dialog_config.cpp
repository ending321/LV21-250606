#include "dialog_config.h"


dialog_config::dialog_config(QWidget *parent)
    :QDialog(parent) {
    setWindowTitle("数据库配置");
    setFixedSize(400, 200);// 固定窗口大小，禁止用户拉伸
    QFormLayout *layout = new QFormLayout(this);// 创建表单布局（标签-输入对）
    editDbPath = new QLineEdit("toolbox.db", this);// 路径输入框，默认值"toolbox.db"
    layout->addRow("数据库路径", editDbPath);// 将标签和输入框添加到表单
    // 创建按钮组，包含"确认"和"取消"按钮，水平排列
    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,Qt::Horizontal, this);

    connect(btnBox, &QDialogButtonBox::accepted, this, &dialog_config::saveDbPath);
    // 连接"确认"按钮到对话框的accept()槽函数（关闭对话框并返回Accepted状态）
    connect(btnBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    // 连接"取消"按钮到对话框的reject()槽函数（关闭对话框并返回Rejected状态）
    connect(btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(btnBox);
    //保存路径，供外部获取
    m_dbPath = editDbPath->text();
}

void dialog_config::saveDbPath(){
    m_dbPath = editDbPath->text(); //在用户点击确认时保存路径
}

//实现获取路径的函数
QString dialog_config::getDbPath()const{
    return m_dbPath;//返回保存的路径
}
