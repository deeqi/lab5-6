#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userWindow = new userwindow();
    settingsWindow = new settings();
    setlevelWindow = new setlevel();
    adminrightsWindow = new adminRights();
    ui->setupUi(this);
    ui->adminsRights->setDisabled(1);

    connect(this,SIGNAL(sendAdminRights(QStringList)),settingsWindow,SLOT(recieveAdminRights(QStringList)));
    connect(setlevelWindow,SIGNAL(newFolderLvl(QString,QString)),userWindow,SLOT(addFolder(QString,QString)));
    connect(setlevelWindow,SIGNAL(setDirectory(QString)),userWindow,SLOT(getDirectory(QString)));
    connect(settingsWindow,SIGNAL(usersListChanged(QStringList,QStringList)),userWindow, SLOT(getUsers(QStringList,QStringList)));
    connect(settingsWindow,SIGNAL(rolesListChanged(QStringList,QStringList)),userWindow,SLOT(getRoles(QStringList,QStringList)));
    connect(this,SIGNAL(refreshUsers()),settingsWindow,SLOT(refreshUsersSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recieveLoginParams(QStringList loginParams){
    ui->label->setText("Вы вошли как: " + loginParams[0]);
    if (loginParams[0] == "godmode")ui->adminsRights->setDisabled(0);
    emit sendAdminRights(loginParams);
}

void MainWindow::on_pushButton_2_clicked()
{
    emit refreshUsers();
    userWindow->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    this->destroy();
    userWindow->deleteLater();
    settingsWindow->deleteLater();
    setlevelWindow->deleteLater();
    adminrightsWindow->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    settingsWindow->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    setlevelWindow->show();
}

void MainWindow::on_adminsRights_clicked()
{
    adminrightsWindow->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    emit openAuthorization();
    this->close();
    this->destroy();
    userWindow->deleteLater();
    settingsWindow->deleteLater();
    setlevelWindow->deleteLater();
    adminrightsWindow->deleteLater();
}
