#include "addnew.h"
#include "ui_addnew.h"
#include "mainwindow.h"

addnew::addnew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addnew)
{
    ui->setupUi(this);
}

addnew::~addnew()
{
    delete ui;
}


void addnew::on_loadbtn_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Open a file","","Gif file(*.*)");
    ui->pathlabel->setText(path);

}

void addnew::on_okbtn_clicked()
{
    //wyciąganie danych z pól
    QString name = ui->nameedit->text();
    QString desc = ui->discedit->toPlainText();
    QString path = ui->pathlabel->text();

    //wkładanie ich do bazy danych
    QSqlQuery query2;
    query2.prepare("INSERT INTO Kroki ( Name, Path, Time, Speed, Desc, Klik) "
                          "VALUES ( :Name, :Path, :Time, :Speed, :Desc, :Klik)");

    query2.bindValue(":Name",name);
    query2.bindValue(":Path",path);
    query2.bindValue(":Time",0);
    query2.bindValue(":Speed",0);
    query2.bindValue(":Desc",desc);
    query2.bindValue(":Klik",0);
    query2.exec();

    this->close();
}

void addnew::on_cancelbtn_clicked()
{
    this->close();
}
