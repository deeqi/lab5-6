#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <QStringList>
#include <QDir>
#include <QMap>

namespace Ui {
class userwindow;
}

class userwindow : public QWidget
{
    Q_OBJECT

public:
    explicit userwindow(QWidget *parent = 0);
    QStringList usersList;
    QStringList usersRoles;
    QStringList rolesList;
    QStringList lvlsRoles;
    QString currentUser;
    QDir basicDir;
    QMap<QString,QString> foldersMap;
    ~userwindow();
public slots:
    void getUsers(QStringList,QStringList);
    void getRoles(QStringList,QStringList);
    void getDirectory(QString);
    void addFolder(QString,QString);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userwindow *ui;
};

#endif // USERWINDOW_H
