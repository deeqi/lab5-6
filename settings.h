#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <userwindow.h>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QSqlQuery>

namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    QString basicdir;
    QStringList rights;
    QStringList selectedLevels;
    QStringList selectedRoles;
    QStringList rolesList;
    QStringList lvlsRoles;
    QStringList usersRoles;
    QStringList usersList;
    QStringList levelsList;
    QMap<QString,int> foldersMap;
    QString currentUser;
    int currentUserIndex;
    QString currentItem;
    QTreeWidgetItem *currentTree;
    void hideRolesBar();
    void hideUserBar();
    ~settings();
signals:
    void rolesListChanged(QStringList, QStringList);
    void usersListChanged(QStringList,QStringList);
public slots:
    void refreshUsersSlot();
    void recieveAdminRights(QStringList);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();
    void on_listWidget_2_itemClicked(QListWidgetItem *item);
    void on_listWidget_4_itemClicked(QListWidgetItem *item);
    void on_pushButton_8_clicked();
    void on_treeWidget_itemExpanded(QTreeWidgetItem *item);
    void on_pushButton_5_clicked();
    void on_treeWidget_itemCollapsed(QTreeWidgetItem *item);
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_listWidget_3_itemClicked(QListWidgetItem *item);
    void on_listWidget_5_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_pushButton_4_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_6_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item);

private:
    void setRolesList();
    void setLvlsRolesList();
    void setUsersList();
    void setUsersRolesList();
    Ui::settings *ui;
};

#endif // SETTINGS_H
