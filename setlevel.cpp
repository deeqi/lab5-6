#include "setlevel.h"
#include "ui_setlevel.h"

setlevel::setlevel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setlevel)
{
    ui->setupUi(this);
    ui->pushButton->setDisabled(1);
}

setlevel::~setlevel()
{
    delete ui;
}

void setlevel::on_lineEdit_returnPressed()
{
    ui->pushButton->setDisabled(0);
    directory = ui->lineEdit->text();
    folders.clear();
    ui->comboBox->clear();
    ui->listWidget->clear();

    dir.setPath(directory);
    if (dir.exists()){
        emit setDirectory(directory);
        folders = dir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
        ui->comboBox->addItems(folders);
        ui->label_4->setText("Директория установлена");

        for(int i = 0; i <folders.length();i++){
            QString preSet = folders[i] + " - Not secret";
            ui->listWidget->addItem(preSet);
        }

    }
    else ui->label_4->setText("Директория указана неверно");

}

void setlevel::on_pushButton_2_clicked()
{
    this->close();
}

void setlevel::on_pushButton_clicked()
{
    QString uFolder = ui->comboBox->itemText(ui->comboBox->currentIndex());
    QString slvl = ui->comboBox_2->currentText();
    QString lvlName = slvl;
    QStringList listNames;

        emit newFolderLvl(uFolder,slvl);
        ui->label_5->setText("Уровень присвоен");

        for (int i = 0; i< ui->listWidget->count(); i++){
            listNames.append((ui->listWidget->item(i)->text()).split(" ").at(0));
        }

        if ((ui->listWidget->count())==0)ui->listWidget->addItem(uFolder + " - " + lvlName);

        else{

            if (listNames.contains(uFolder)){
                int index = listNames.indexOf(uFolder);
                ui->listWidget->takeItem(index);
                ui->listWidget->addItem(uFolder + " - " + lvlName);
            }
            else ui->listWidget->addItem(uFolder + " - " + lvlName);

        }
    slvl.clear();
    lvlName.clear();
    listNames.clear();
}
