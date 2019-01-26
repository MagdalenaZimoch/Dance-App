#include "step.h"
#include "ui_step.h"
#include "mainwindow.h"
#include "name.h"
QString namee;
QString nazwa2;
QTime time1;
qint32 a;
Step::Step(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Step)
{
    ui->setupUi(this);

    auto movie = new QMovie(this);
    QSqlQuery query("SELECT * FROM Kroki WHERE Klik=1");
    while(query.next())
    {
            QString name = query.value(1).toString();
            namee = name;
            QString path = query.value(2).toString();
            QString disc = query.value(5).toString();

            movie->setFileName(path);
            ui->naanimacje->setMovie(movie);
            movie->setScaledSize(QSize(120,120));
            movie->start();


            ui->nazwa->setText(name);
            ui->naopis->setText(disc);

    }
    connect(movie, &QMovie::frameChanged, this,
        [movie]()
        {
            if(movie->currentFrameNumber() == 1)
            {
                time1.start();
            }

            if(movie->currentFrameNumber() == (movie->frameCount() - 1))
            {
                movie->stop();
                if(movie->state() == QMovie::NotRunning)
                {
                    a = time1.elapsed();
                    QSqlQuery query2;
                    query2.prepare("UPDATE  Kroki SET Time=:time WHERE Name=:name");
                    query2.bindValue(":time", a);
                    query2.bindValue(":name", namee);
                    query2.exec();
                }

            }
        }
    );
    ui->spinBox->setValue(a);

}


Step::~Step()
{
    delete ui;
}

void Step::on_okbtn_clicked()
{
    qint32 time;
    if(radio == 1)
    {
        time = ui->spinBox->value();
    }
    else if(radio == 0)
    {
        time = a;
    }
    QSqlQuery query("SELECT * FROM Kroki WHERE Klik=1");
    while(query.next())
    {

        qint32 id = query.value(0).toInt();
        QSqlQuery query2;
        query2.prepare("INSERT INTO Uklady ( Name, Steps, Time) "
                              "VALUES ( :Name, :Steps, :Time)");

        query2.bindValue(":Name",nazwa2);
        query2.bindValue(":Steps",id);
        query2.bindValue(":Time",time);
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

void Step::on_radioustaw_clicked()
{
    radio = 1;
}

void Step::on_radiozostaw_clicked()
{
    radio = 0;
    ui->spinBox->setValue(a);
}

void Step::on_sprawdzbtn_clicked()
{

}
