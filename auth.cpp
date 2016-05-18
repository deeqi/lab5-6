#include "auth.h"
#include "mainwindow.h"
#include "ui_auth.h"

auth::auth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth)
{
    ui->setupUi(this);
    ui->password->setMaxLength(20);
    ui->password->setEchoMode(QLineEdit::Password);

    QRegExp loginRestrict ("[A-Za-z 0-9 //_]{1,15}");
    ui->login->setValidator (new QRegExpValidator (loginRestrict, this));

    connect(this,SIGNAL(enterPressed()),this,SLOT(on_logButton_clicked()));
    //db
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("qweasdzxc123");
    db.setHostName("localhost");
    db.open();
}

auth::~auth()
{
    delete ui;
}

void auth::on_logButton_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    QSqlQuery query; QString loginQueryResult;
    QString queryStr = "select login from admins where login = '"+login+"'";
    query.exec(queryStr);

    while (query.next()) {
        if (!query.value(0).isNull()){
            loginQueryResult += query.value(0).toString();
        }
    }
    if (!loginQueryResult.isEmpty()){
        queryStr.clear();
        queryStr="select password from admins where login = '"+login+"'";
        query.exec(queryStr);
        QString dbPassword;

        while (query.next()) {
            if (!query.value(0).isNull()){
                dbPassword += query.value(0).toString();
            }
        }
        if (!(password == dbPassword)){
            ui->label_3->setText("Неправльно введен логин или пароль!");
        }
        else{
            setLoginParameters(login);
            MainWindow *mw; mw = new MainWindow();
            connect(this,SIGNAL(sendLoginParams(QStringList)),mw,SLOT(recieveLoginParams(QStringList)));
            connect(mw,SIGNAL(openAuthorization()),this,SLOT(openWindow()));
            emit sendLoginParams(loginParams);
            mw->show();
            this->close();
        }
    }
    else ui->label_3->setText("Неправльно введен логин или пароль!");
    ui->login->clear();
    ui->password->clear();
}

void auth::setLoginParameters(const QString &login){
    loginParams.clear();
    loginParams.append(login);
    QString queryStr = "select can_revoke_user, can_revoke_role, can_assign_user,can_assign_role "
                       "from admins where login = '" + login +"'";
    QSqlQuery query;
    query.exec(queryStr);

    while (query.next()) {
        for (int j = 0; j<4;j++){
            loginParams.append(query.value(j).toString());
        }
    }

}

void auth::on_login_returnPressed()
{
    emit enterPressed();
}

void auth::openWindow()
{
    this->show();
}

void auth::on_password_returnPressed()
{
    emit enterPressed();
}
