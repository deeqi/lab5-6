#ifndef AUTH_H
#define AUTH_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <mainwindow.h>

namespace Ui {
class auth;
}

class auth : public QWidget
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = 0);
    ~auth();
signals:
    void enterPressed();
    void sendLoginParams(QStringList);
public slots:
    void openWindow();
private slots:
    void on_logButton_clicked();
    void on_login_returnPressed();
    void on_password_returnPressed();
private:
    void setLoginParameters(const QString &login);
    QStringList loginParams;
    Ui::auth *ui;
};

#endif // AUTH_H
