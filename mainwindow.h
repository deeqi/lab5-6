#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <settings.h>
#include <userwindow.h>
#include <setlevel.h>
#include <auth.h>
#include <adminrights.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void recieveLoginParams(QStringList);
public:
    explicit MainWindow(QWidget *parent = 0);
    setlevel *setlevelWindow;
    settings *settingsWindow;
    userwindow *userWindow;
    adminRights *adminrightsWindow;
    ~MainWindow();
signals:
    void sendAdminRights(QStringList);
    void refreshUsers();
    void openAuthorization();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_adminsRights_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
