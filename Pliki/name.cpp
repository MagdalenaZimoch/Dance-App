#include "name.h"
#include "step.h"
#include "ui_name.h"
#include <QDebug>


Name::Name(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Name)
{
    ui->setupUi(this);
}

Name::~Name()
{
    delete ui;
}

void Name::on_gobtn_clicked()
{
    QString nazwa;
    //nazwa nowego ukladu
    nazwa = ui->nownazwa->text();
    Step* step = new Step();
    connect(this, SIGNAL(wyslijnazwe(QString)),step ,SLOT(odbierznazwa(QString)));
    emit wyslijnazwe(nazwa);
    this->close();
}



