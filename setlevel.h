#ifndef SETLEVEL_H
#define SETLEVEL_H

#include <QWidget>
#include <QDir>
#include <QFile>
#include <settings.h>
#include <userwindow.h>

namespace Ui {
class setlevel;
}

class setlevel : public QWidget
{
    Q_OBJECT

public:
    explicit setlevel(QWidget *parent = 0);
    QString directory;
    QStringList folders;
    QDir dir;
    ~setlevel();
signals:

    void setDirectory (QString);
    void newFolderLvl(QString,QString);

private slots:
    void on_lineEdit_returnPressed();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::setlevel *ui;
};

#endif // SETLEVEL_H
