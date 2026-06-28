#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");
    ui->editPwd->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    QString username = ui->editUser->text().trimmed();
    QString password = ui->editPwd->text();

    if (username.isEmpty())
    {
        QMessageBox::warning(this, "提示", "请输入账号");
        ui->editUser->setFocus();
        return;
    }
    if (password.isEmpty())
    {
        QMessageBox::warning(this, "提示", "请输入密码");
        ui->editPwd->setFocus();
        return;
    }

    if (checkAccount(username, password))
    {
        QMessageBox::information(this, "成功", "登录验证通过！");
        accept();
    }
    else
    {
        QMessageBox::critical(this, "失败", "账号或密码错误");
        ui->editPwd->clear();
        ui->editPwd->setFocus();
    }
}

void LoginDialog::on_btnCancel_clicked()
{
    reject();
}

bool LoginDialog::checkAccount(const QString &user, const QString &pwd)
{
    // 测试账号 admin / 123456，业务替换SQLite查询
    return user == "admin" && pwd == "123456";
}