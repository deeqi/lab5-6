#include "adminrights.h"
#include "ui_adminrights.h"

adminRights::adminRights(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminRights)
{
    ui->setupUi(this);
    ui->lineEdit->setHidden(1);
    ui->pushButton_2->setHidden(1);
    ui->pushButton_3->setDisabled(1);

    for (int i = 0;i<5;i++){
        ui->tableWidget->setColumnWidth(i,100);
    }
    getAdminRights();
    fillTable();
}

adminRights::~adminRights()
{
    delete ui;
}

void adminRights::getAdminRights(){
    QSqlQuery query;
    QString oneAdminString;
    query.exec("select * from admins");
    while(query.next()){
        oneAdminString.clear();
        for (int i = 1;i<7;i++){
            if (i==2)i++;//пропуск второго параметра (пароль)
            oneAdminString+=query.value(i).toString()+",";
            if (i==6)oneAdminString+=query.value(i).toString();
        }
        adminRightsList.append(oneAdminString);
    }
}

void adminRights::fillTable(){
    ui->tableWidget->setRowCount(adminRightsList.length());
    for(int i = 0; i<adminRightsList.length();i++){
        QStringList oneItem = adminRightsList[i].split(",");
        for(int j=0; j<oneItem.length();j++){
            QTableWidgetItem *itm;
            itm = new QTableWidgetItem();
            itm->setText(oneItem[j]);
            itm->setFlags(itm->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,j,itm);
        }
    }
}

void adminRights::on_pushButton_clicked()
{
    this->close();
    this->destroy();
}

void adminRights::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    if(item->column()!=0 ){
        currentItemRow=item->row();
        currentItemCol=item->column();
        QString login = ui->tableWidget->item(currentItemRow,0)->text();
        QString right = ui->tableWidget->horizontalHeaderItem(currentItemCol)->text();
        ui->label->setText("Изменить право \""+right+"\" для "+login);
        ui->lineEdit->setText(item->text());
        QRegExp rightRestrict ("[+-]{1,1}");
        ui->lineEdit->setValidator (new QRegExpValidator (rightRestrict, this));
        ui->lineEdit->setHidden(0);
        ui->pushButton_2->setHidden(0);
    }
    else{
        ui->lineEdit->clear();
        ui->lineEdit->setHidden(1);
        ui->label->clear();
        ui->pushButton_2->setHidden(1);
    }
}

void adminRights::on_pushButton_2_clicked()
{
    ui->tableWidget->item(currentItemRow,currentItemCol)->setText(ui->lineEdit->text());
    ui->pushButton_3->setDisabled(0);

    QString oneChange = ui->tableWidget->item(currentItemRow,0)->text() + ",";
    for (int i=1;i<5;i++){
        oneChange+=ui->tableWidget->item(currentItemRow,i)->text()+",";
        if (i==4)oneChange+=ui->tableWidget->item(currentItemRow,i)->text();
    }
    changedAdmins.append(oneChange);
}

void adminRights::on_pushButton_3_clicked()
{
    QSqlQuery query;
    QString queryString;

    for (int i = 0; i<changedAdmins.length();i++){
        QString oneAdmin = changedAdmins[i];
        QStringList oneAdminString = oneAdmin.split(",");
        for (int j = 0; j<oneAdminString.length(); j++){
            queryString = "update admins set can_revoke_user = '"+oneAdminString[1]
                    +"', can_revoke_role ='"+oneAdminString[2]+"', can_assign_user = '"+
                    oneAdminString[3]+"', can_assign_role = '"+oneAdminString[4]
                    +"' where login = '"+oneAdminString[0]+"'";
            query.exec(queryString);
        }
    }
    ui->lineEdit->clear();
    ui->lineEdit->setHidden(1);
    ui->label->clear();
    ui->pushButton_2->setHidden(1);
    ui->pushButton_3->setDisabled(1);
}
