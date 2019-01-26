#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "name.h"
#include "addnew.h"
#include "step.h"
#include <qdebug.h>
#include <qdesktopservices.h>
#include <QSqlQuery>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //wygląd :
    auto central = new QWidget(this);
    auto grid = new QGridLayout(this);
    central->setLayout(grid);
    ui->scrollArea->setWidget(central);
    grid->setColumnMinimumWidth(3,120);
    grid->setVerticalSpacing(6);
    grid->setHorizontalSpacing(6);



    //Połączennie z bazą danych
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Magda/Documents/mojodtwarzacz/test.db");


    if(mydb.open())
    {

        QSqlQuery query("SELECT * FROM Kroki");
        int i = 0;
        while(query.next())
        {
            auto anim = new QPushButton(this);
            a.append(anim);

            auto movi = new QMovie(this);
            movie.append(movi);

            grid->addWidget(a[i]);

            a[i]->setMinimumHeight(120);
            a[i]->setMinimumWidth(120);


            QString path = query.value(2).toString();

            movie[i]->setFileName(path);

            connect(movie[i], &QMovie::frameChanged, [=]{a[i]->setIcon(movie[i]->currentPixmap());});
            a[i]->setIconSize(QSize(120,120));
            movie[i]->start();
            connect(a[i],SIGNAL(clicked()), this, SLOT(klickbtn( )));
            i++;
        }


    }

    player = new QMediaPlayer(this);
    //Za pomocą tego będzie wyświetlany końcowy układ:
    film  = new QMovie(this);
    film->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/renifer.gif");
    ui->filmlabel->setMovie(film);

    //Ikony przycisków
    ui->playbtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->stopbtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pausebtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->openbtn->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->newstepbtn->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));


    connect(player, &QMediaPlayer::positionChanged,this,&MainWindow::on_positionnchanged);
    connect(player, &QMediaPlayer::durationChanged,this,&MainWindow::on_durationnchanged);


}

MainWindow::~MainWindow()
{
    delete ui;




}

void MainWindow::on_openbtn_clicked()
{
    //załadowanie pliku
    QString filename = QFileDialog::getOpenFileName(this,"Open a file","","Music File(*.*)");

    QString name = QFileInfo(filename).fileName();
    on_stopbtn_clicked();
    player->setMedia(QUrl::fromLocalFile(filename));
    ui->nameoffile->setText(name);
}

void MainWindow::on_progresslider_sliderMoved(int position)
{
    player->setPosition(position);

}

void MainWindow::on_positionnchanged(qint64 position)
{
    ui->progresslider->setValue(position);

}

void MainWindow::on_durationnchanged(qint64 position)
{
    ui->progresslider->setMaximum(position);
}

void MainWindow::on_playbtn_clicked()
{
    player->setVolume(100);
    player->play();
    film->start();
}

void MainWindow::on_stopbtn_clicked()
{
    player->stop();
    film->stop();

}

void MainWindow::on_pausebtn_clicked()
{
     player->pause();
     film->setSpeed(200);
}

void MainWindow::on_newstepbtn_clicked()
{
    addnew newstep;
    newstep.setModal(true);
    newstep.exec();
}

void MainWindow::klickbtn()
{
    player->pause();
    QObject* btn = QObject::sender();
    QSqlQuery query;
    QSqlQuery query2("SELECT *FROM Kroki");
    qint32 ktory;
    for(int i=0;i<=a.length()-1;i++)
    {

        if(btn == a[i])
        {
            ktory = i;
            qDebug()<<i;
        }
        movie[i]->stop();
    }
    qint32 count = 0;
    while(query2.next())
    {
        qDebug()<<count <<" : " << ktory;
        if(count == ktory)
        {

            QString id = query2.value(0).toString();
            qDebug()<<id;
            query.exec("UPDATE Kroki SET Klik = 1 WHERE id = "+id);
            qDebug()<<"wpisany";
        }
        else
        {
            QString id = query2.value(0).toString();
            query.exec("UPDATE Kroki SET Klik = 0 WHERE id = "+id);
        }
        count++;

    }


    Step step;
    step.setModal(true);
    step.exec();
    player->play();
    for(int i=0;i<=a.length()-1;i++)
    {
        movie[i]->start();
    }

}

void MainWindow::nameof()
{

}



