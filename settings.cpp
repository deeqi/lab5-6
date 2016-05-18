#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnWidth(0,100);
    ui->pushButton->setDisabled(1);

    setRolesList();
    setLvlsRolesList();
    setUsersList();
    setUsersRolesList();
    levelsList<<"Top secret"<<"Secret"<<"Not secret"<<"Special use";

    //Начальное задание списка ролей
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("Roles");

    for (int i = 0; i<rolesList.length();i++){
        QTreeWidgetItem *itm = new QTreeWidgetItem(1);
        itm->setText(0,rolesList[i]);
        ui->treeWidget->addTopLevelItem(itm); 
        QString lvlForRole = lvlsRoles[i];
        QStringList lol = lvlForRole.split(",");
            for (int j=0; j<lol.length();j++){
                QTreeWidgetItem *child = new QTreeWidgetItem(1);
                child->setFlags(Qt::ItemIsEnabled);
                child->setText(0,lol[j]);
                itm->addChild(child);
            }
    }

    //Начальное задание списка пользователей
    for  (int j = 0; j<usersList.length(); j++){
        QString roleForUser = usersRoles[j];
        QString userInList = usersList[j]+" - "+roleForUser;
        ui->listWidget->addItem(userInList);
    }
    //неактивные кнопки "изменить"
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_5->setDisabled(true);

    ui->lineEdit->setMaxLength(20);
    ui->lineEdit_2->setMaxLength(20);

    ui->listWidget_2->addItems(levelsList);
    ui->listWidget_3->addItems(rolesList);
    //неактивные менюшки добавления/изменения
    hideRolesBar();
    hideUserBar();

}

settings::~settings()
{
    delete ui;
}

void settings::setRolesList()
{
    QSqlQuery query;
    query.exec("select name from roles");
    while (query.next()) {
        if (!query.value(0).isNull()){
            rolesList.append(query.value(0).toString());
        }
    }
}

void settings::setLvlsRolesList()
{
    QSqlQuery query;
    query.exec("select secret_lvls from roles");
    while (query.next()) {
        if (!query.value(0).isNull()){
            lvlsRoles.append(query.value(0).toString());
        }
    }
}

void settings::setUsersList()
{
    QSqlQuery query;
    query.exec("select name from users");
    while (query.next()) {
        if (!query.value(0).isNull()){
            usersList.append(query.value(0).toString());
        }
    }
}

void settings::setUsersRolesList()
{
    QSqlQuery query;
    query.exec("select roles from users");
    while (query.next()) {
        if (!query.value(0).isNull()){
            usersRoles.append(query.value(0).toString());
        }
    }
}

void settings::refreshUsersSlot()
{
emit rolesListChanged(rolesList,lvlsRoles);
emit usersListChanged(usersList,usersRoles);
}

void settings::on_pushButton_2_clicked()  //кнопка добавить (пользователя)
{
    ui->listWidget_3->setDisabled(0);
    ui->listWidget_5->setDisabled(0);
    ui->lineEdit->setDisabled(0);
    ui->pushButton_9->setDisabled(0);
    ui->listWidget_5->clear();
}


void settings::on_pushButton_clicked()              //кнопка удалить
{

    QString removeItem = currentItem;
    rolesList.removeAt(rolesList.indexOf(removeItem));
    lvlsRoles.removeAt(lvlsRoles.indexOf(removeItem));

    ui->listWidget_3->clear();
    ui->listWidget_3->addItems(rolesList);

    ui->listWidget->clear();

    QSqlQuery query;
    for  (int j = 0; j<usersList.length(); j++){
        QString roleForUser = usersRoles[j];
        roleForUser.remove(removeItem);
        QStringList newroles = roleForUser.split(",");
        for (int k = 0; k<newroles.length();k++){
            if (newroles[k].isEmpty())newroles.removeAt(k);
        }
        roleForUser.clear();
        roleForUser = newroles.join(",");
        usersRoles[j] = roleForUser;
        QString userInList = usersList[j]+" - "+roleForUser;
        QString queryString = "update users set roles ='"
                +roleForUser +"' where name = '" + usersList[j] +"'";
        query.exec(queryString);
        ui->listWidget->addItem(userInList);
    }

    emit rolesListChanged(rolesList,lvlsRoles);

    QString queryStr = "delete from roles where name = '"+removeItem+"'";
    query.exec(queryStr);

    ui->pushButton->setDisabled(1);
    delete ui->treeWidget->currentItem();

}

void settings::on_pushButton_7_clicked()    //кнопка закрыть
{
    this->close();
}

void settings::on_pushButton_3_clicked()    //кнопка добавить (роль)
{
    ui->listWidget_2->setDisabled(0);
    ui->listWidget_4->setDisabled(0);
    ui->lineEdit_2->setDisabled(0);
    ui->pushButton_8->setDisabled(0);
}

void settings::on_listWidget_2_itemClicked(QListWidgetItem *item) //список уровней
{
        selectedLevels.append(item->text());
        ui->listWidget_4->addItem(item->text());
        ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
}

void settings::hideRolesBar()               //деактивация кнопок изменения ролей
{
    ui->listWidget_2->setDisabled(true);
    ui->listWidget_4->setDisabled(true);
    ui->lineEdit_2->setDisabled(true);
    ui->commandLinkButton->setDisabled(1);
    ui->pushButton_8->setDisabled(true);
    ui->pushButton_10->setDisabled(true);
}

void settings::hideUserBar()                //деактивация кнопок изменения пользователей
{
    ui->listWidget_3->setDisabled(true);
    ui->listWidget_5->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->commandLinkButton_2->setDisabled(1);
    ui->lineEdit->setDisabled(true);
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_11->setDisabled(true);
}

void settings::on_listWidget_4_itemClicked(QListWidgetItem *item) //список ролей 2
{
    selectedLevels.removeAt(selectedLevels.indexOf(item->text()));
    ui->listWidget_2->addItem(item->text());
    ui->listWidget_4->takeItem(ui->listWidget_4->currentRow());
}

void settings::on_pushButton_8_clicked()    //кнопка добавить роль( с параметрами)
{
    QString rolename = ui->lineEdit_2->text(); //имя роли
    QTreeWidgetItem *itm = new QTreeWidgetItem(1);
    itm->setText(0,rolename);
    ui->treeWidget->addTopLevelItem(itm);
    //добавление детей (уровней секретности)
    for (int i = 0; i<selectedLevels.length();i++){
        QTreeWidgetItem *child = new QTreeWidgetItem(1);
        child->setText(0,selectedLevels[i]);
        itm->addChild(child);
    }
    //добавление ук для роли в список
    QString newlvls;
    for (int j = 0;j<selectedLevels.length();j++){
        if(j!=(selectedLevels.length()-1))newlvls+= (selectedLevels[j]+",");
        else newlvls+=selectedLevels[j];
    }

    rolesList.append(rolename);
    lvlsRoles.append(newlvls);

    //вставляем в бд
    QSqlQuery query;
    QString id;
    int newId;
    query.exec("SELECT max(roleid) FROM roles;");
    while (query.next()) {id = query.value(0).toString();}
    newId = id.toInt() + 1;
    id = QString::number(newId);
    QString queryString = "insert into roles values('"+id+"','"+rolename+"','"
            +newlvls+"')";
    query.exec(queryString);

    emit rolesListChanged(rolesList,lvlsRoles);

    ui->listWidget_3->clear();
    ui->listWidget_3->addItems(rolesList);

    selectedLevels.clear();
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(levelsList);
    ui->listWidget_4->clear();
    ui->lineEdit_2->clear();
    hideRolesBar();
}

void settings::on_treeWidget_itemExpanded(QTreeWidgetItem *item)    //раскрытие корня дерева
{
    currentItem.clear();
    ui->pushButton->setDisabled(0);
    ui->pushButton_5->setDisabled(0);
    currentItem = item->text(0);
    currentTree = item;
    ui->label_3->setText(currentItem);
}

void settings::on_pushButton_5_clicked()    //кнопка изменить
{
    if (rights[4]=="+")ui->listWidget_2->setDisabled(0);
    if (rights[2]=="+")ui->listWidget_4->setDisabled(0);
    ui->lineEdit_2->setDisabled(0);
    ui->pushButton_10->setDisabled(0);
    ui->lineEdit_2->setText(currentItem);

    ui->listWidget_2->clear();
    ui->listWidget_4->clear();
    selectedLevels.clear();

    QStringList lList;
    lList<<"Top secret"<<"Secret"<<"Not secret"<<"Special use";
    QString lvls = lvlsRoles[rolesList.indexOf(currentItem)];
    QStringList lul = lvls.split(",");
    for (int i = 0; i<lul.length(); i++){
        lList.removeAt(lList.indexOf(lul[i]));
        ui->listWidget_4->addItem(lul[i]);
        selectedLevels.append(lul[i]);
    }
    ui->listWidget_2->addItems(lList);

}

void settings::on_treeWidget_itemCollapsed(QTreeWidgetItem *item)       //сворачивание корня дерева
{
    ui->pushButton_5->setDisabled(1);
    ui->pushButton->setDisabled(1);
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(levelsList);
    ui->listWidget_4->clear();
    ui->lineEdit_2->clear();
    item->isHidden();
    hideRolesBar();
}

void settings::on_pushButton_10_clicked()           //кнопка изменить с параметрами (роль)
{
    int index = rolesList.indexOf(currentItem);
    rolesList.removeAt(index);  
    lvlsRoles.removeAt(index);

    QString newlvls;
    for (int j = 0;j<selectedLevels.length();j++){
        if(j!=(selectedLevels.length()-1))newlvls+= (selectedLevels[j]+",");
        else newlvls+= selectedLevels[j];
    }
    QString newName = ui->lineEdit_2->text();
    rolesList.append(newName);
    lvlsRoles.append(newlvls);

    QSqlQuery query;
    QString queryString = "update roles set name = '"+newName+"', secret_lvls ='"
            +newlvls +"' where name = '" + currentItem +"'";
    query.exec(queryString);
    emit rolesListChanged(rolesList,lvlsRoles);

    currentTree->setText(0,(ui->lineEdit_2->text()));
    currentTree->takeChildren();

    for (int i = 0; i<selectedLevels.length();i++){
        QTreeWidgetItem *child = new QTreeWidgetItem(1);
        child->setText(0,selectedLevels[i]);
        currentTree->addChild(child);
    }

    ui->listWidget_3->clear();
    ui->listWidget_3->addItems(rolesList);
    selectedLevels.clear();
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(levelsList);
    ui->listWidget_4->clear();
    ui->lineEdit_2->clear();
    hideRolesBar();
}

void settings::on_pushButton_9_clicked() //добавить пользователя с параметрами
{
    QString newuser = ui->lineEdit->text();
    QString newroles;
    for (int i = 0; i<selectedRoles.length();i++){
        if(i!=(selectedRoles.length()-1))newroles+=(selectedRoles[i]+",");
        else newroles+=selectedRoles[i];
    }

    usersList.append(newuser);
    usersRoles.append(newroles);

    //вставляем в бд
    QSqlQuery query;
    QString id;
    int newId;
    query.exec("SELECT max(userid) FROM users;");
    while (query.next()) {id = query.value(0).toString();}
    newId = id.toInt() + 1;
    id = QString::number(newId);
    QString queryString = "insert into users values('"+id+"','"+newuser+"','"
            +newroles+"')";
    query.exec(queryString);

    emit usersListChanged(usersList,usersRoles);

    QString newUserString = newuser + " - "+newroles;
    ui->listWidget->addItem(newUserString);


    ui->listWidget_3->clear();
    ui->listWidget_5->clear();
    ui->lineEdit->clear();
    ui->listWidget_3->addItems(rolesList);

    selectedRoles.clear();
    hideUserBar();

}

void settings::on_listWidget_3_itemClicked(QListWidgetItem *item) //список ролей3
{
    selectedRoles.append(item->text());
    ui->listWidget_5->addItem(item->text());
    ui->listWidget_3->takeItem(ui->listWidget_3->currentRow());
}

void settings::on_listWidget_5_itemClicked(QListWidgetItem *item)
{
    selectedRoles.removeAt(selectedRoles.indexOf(item->text()));
    ui->listWidget_3->addItem(item->text());
    ui->listWidget_5->takeItem(ui->listWidget_5->currentRow());
}

void settings::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_4->setDisabled(0);
    ui->pushButton_6->setDisabled(0);
    ui->listWidget_5->clear();
    ui->listWidget_3->clear();
    ui->listWidget_3->addItems(rolesList);
    ui->label_12->setText((item->text()).split(" - ").at(0));
}

void settings::on_pushButton_4_clicked()        //кнопка изменить пользователя (без параметров)
{
    if (rights[3]=="+")ui->listWidget_3->setDisabled(0);
    if (rights[1]=="+")ui->listWidget_5->setDisabled(0);
    ui->lineEdit->setDisabled(0);
    ui->pushButton_11->setDisabled(0);

    currentUser = (ui->listWidget->currentItem()->text()).split(" - ").at(0);
    currentUserIndex = ui->listWidget->currentRow();
    ui->lineEdit->setText(currentUser);

    ui->listWidget_3->clear();
    ui->listWidget_5->clear();
    QStringList lList;
    lList = rolesList;
    QString lvls = usersRoles[usersList.indexOf(currentUser)];
    QStringList roleForRolelist = lvls.split(",");

    for (int i = 0; i<roleForRolelist.length(); i++){
        lList.removeAt(lList.indexOf(roleForRolelist[i]));
        ui->listWidget_5->addItem(roleForRolelist[i]);
        selectedRoles.append(roleForRolelist[i]);
    }
    ui->listWidget_3->addItems(lList);

}

void settings::on_pushButton_11_clicked()           //кнопка изменить пользвателя с параметрами
{
    int index = usersList.indexOf(currentUser);
    usersRoles.removeAt(index);
    usersList.removeAt(index);
    QString newName = ui->lineEdit->text();
    usersList.append(newName);

    QString newRoles;
    for (int i = 0; i<selectedRoles.length();i++){
        if (i!=(selectedRoles.length()-1))newRoles+= (selectedRoles[i] + ",");
        else newRoles+= selectedRoles[i];
    }
    usersRoles.append(newRoles);

    QSqlQuery query;
    QString queryString = "update users set name = '"+newName+"', roles ='"
            +newRoles +"' where name = '" + currentUser +"'";
    query.exec(queryString);

    emit usersListChanged(usersList,usersRoles);
    ui->listWidget->takeItem(currentUserIndex);
    QString newUserString = ui->lineEdit->text() + " - " + newRoles;
    ui->listWidget->addItem(newUserString);

    selectedRoles.clear();
    ui->listWidget_3->clear();
    ui->listWidget_3->addItems(rolesList);
    ui->listWidget_5->clear();
    ui->lineEdit->clear();
    hideUserBar();
}

void settings::on_pushButton_6_clicked()
{
    QString removedItem = ui->listWidget->currentItem()->text().split(" - ").at(0);
    ui->listWidget->takeItem(ui->listWidget->currentRow());
    usersList.removeAt(usersList.indexOf(removedItem));
    usersRoles.removeAt(usersList.indexOf(removedItem));

    emit usersListChanged(usersList,usersRoles);
    QSqlQuery query;
    QString queryStr = "delete from users where name = '"+removedItem+"'";
    query.exec(queryStr);
}

void settings::recieveAdminRights(QStringList adminRights)
{
    rights.clear();
    rights = adminRights;
    QString labelInfo;
    if (rights[1]=="+")labelInfo+=" \"revoke user\" ";
        else ui->pushButton_6->setHidden(1);
    if (rights[2]=="+")labelInfo+=" \"revoke role\" ";
        else ui->pushButton->setHidden(1);
    if (rights[3]=="+")labelInfo+=" \"assign user\" ";
        else ui->pushButton_2->setHidden(1);
    if (rights[4]=="+")labelInfo+=" \"assign role\" ";
        else ui->pushButton_3->setHidden(1);
    ui->label_13->setText("Доступные права:"+labelInfo);
}

void settings::on_treeWidget_itemClicked(QTreeWidgetItem *item)
{
    if(item->childCount()==0)ui->pushButton->setDisabled(1);
}
