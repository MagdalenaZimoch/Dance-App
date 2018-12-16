#include "step.h"
#include "ui_step.h"
#include "mainwindow.h"
#include "name.h"

QString nazwa2;

Step::Step(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Step)
{
    ui->setupUi(this);

    QSqlQuery query("SELECT * FROM Kroki WHERE Klik=1");
    while(query.next())
    {
            QString name = query.value(1).toString();
            QString path = query.value(2).toString();
            QString disc = query.value(5).toString();

            auto movie = new QMovie(this);

            movie->setFileName(path);
            ui->naanimacje->setMovie(movie);
            movie->setScaledSize(QSize(120,120));
            movie->start();
            ui->nazwa->setText(name);
            ui->naopis->setText(disc);
    }
}


Step::~Step()
{
    delete ui;
}

void Step::on_okbtn_clicked()
{
    QSqlQuery query("SELECT * FROM Kroki WHERE Klik=1");
    while(query.next())
    {
        qint32 id = query.value(0).toInt();
        QSqlQuery query2;
        query2.prepare("INSERT INTO Uklady ( Name, Steps, Time) "
                              "VALUES ( :Name, :Steps, :Time)");

        query2.bindValue(":Name",nazwa2);
        query2.bindValue(":Steps",id);
        query2.bindValue(":Time","9");
        query2.exec();
    }
    this->close();

}

void Step::odbierznazwa(QString nazwa)
{
    nazwa2 = nazwa;
}

void Step::on_cancelbtn_clicked()
{
    this->close();

}
