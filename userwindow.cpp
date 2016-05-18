#include "userwindow.h"
#include "ui_userwindow.h"

userwindow::userwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userwindow)
{
    ui->setupUi(this);
}

userwindow::~userwindow()
{
    delete ui;
}

void userwindow::on_pushButton_2_clicked()
{
    this->close();
}

void userwindow::getUsers(QStringList ul,QStringList ur)
{
    usersList.clear();
    usersRoles.clear();
    usersList = ul;
    usersRoles = ur;
    ui->comboBox->clear();
    ui->comboBox->addItems(usersList);
}

void userwindow::getRoles(QStringList rl,QStringList lvlr)
{
    rolesList.clear();
    lvlsRoles.clear();
    rolesList = rl;
    lvlsRoles = lvlr;
}

void userwindow::on_pushButton_clicked() //кнопка выбрать
{
    ui->label_2->clear();
    ui->listWidget->clear();
    currentUser = ui->comboBox->currentText();

    ui->label_2->setText("Выбран пользователь "+currentUser);
    ui->listWidget->addItem("Текущие роли пользователя: ");

    QString allUserRoles = usersRoles[usersList.indexOf(currentUser)];
    QStringList uroles = allUserRoles.split(",");
    for (int g = 0; g<uroles.length();g++){
        if (uroles[g].isEmpty()) uroles.removeAt(g);
    }
    QStringList ulvls;
    QStringList userDirs;

    for (int i = 0; i<uroles.length(); i++){
        ui->listWidget->addItem("      " + uroles[i]);
        QString lvls = lvlsRoles[rolesList.indexOf(uroles[i])];
        QStringList kek = lvls.split(",");
        for (int j = 0; j<kek.length(); j++){
            ulvls.append(kek[j]);
        }
    }
    //;
    QStringList folders = foldersMap.keys();
    QStringList values = foldersMap.values();

    for (int j = 0; j<folders.length();j++){
          if (ulvls.contains(values[j])){
                userDirs.append(folders[j]);
          }
    }


    if (!foldersMap.empty()){
        ui->listWidget->addItem("Доступные папки:");
        for (int u =0; u<userDirs.length();u++){
            ui->listWidget->addItem("      "+userDirs[u]+" - " + foldersMap.value(userDirs[u]));
        }
    }
    else ui->listWidget->addItem("Уровни секретности директорий не заданы");

    folders.clear();
    values.clear();
    userDirs.clear();
    allUserRoles.clear();
    uroles.clear();
    ulvls.clear();


}

void userwindow::getDirectory(QString directory)
{
    foldersMap.clear();
    basicDir.setPath(directory);

    QStringList folders = basicDir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);

    for(int i = 0; i <folders.length();i++){
        foldersMap.insert(folders[i],"Not secret");
    }
}

void userwindow::addFolder(QString folder, QString lvl)
{
    foldersMap.insert(folder,lvl);
}
