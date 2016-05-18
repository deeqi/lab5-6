#ifndef ADMINRIGHTS_H
#define ADMINRIGHTS_H

#include <QWidget>
#include <QSqlQuery>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class adminRights;
}

class adminRights : public QWidget
{
    Q_OBJECT

public:
    explicit adminRights(QWidget *parent = 0);
    int currentItemRow;
    int currentItemCol;
    QStringList changedAdmins;
    QStringList adminRightsList;
    ~adminRights();

private slots:
    void on_pushButton_clicked();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    void fillTable();
    void getAdminRights();
    Ui::adminRights *ui;
};

#endif // ADMINRIGHTS_H
