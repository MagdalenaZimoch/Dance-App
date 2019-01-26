#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "name.h"
#include "addnew.h"
#include "step.h"
#include <qdebug.h>
#include <qdesktopservices.h>
#include <QSqlQuery>
#include <QRegion>

QString namename;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nameofsystem = new QString();
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
            a[i]->setStyleSheet("* { background-color:  rgb(255,255,255) }");


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
        }
        movie[i]->stop();
    }
    qint32 count = 0;
    while(query2.next())
    {
        if(count == ktory)
        {
            QString id = query2.value(0).toString();
            query.exec("UPDATE Kroki SET Klik = 1 WHERE id = "+id);
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
void MainWindow::namesystem(QString name)
{
    *nameofsystem = name;
    namename = name;
}

void MainWindow::on_pushButton_clicked()
{
    ui->progresslider->setValue(0);
    player->setPosition(0);
    qDebug()<< namename;
    //połączenie z bazą danych

    QSqlQuery query4("SELECT * FROM Uklady WHERE Name = '"+namename+"'");


    while(query4.next())
    {
            //odczytywanie id kroku
            qint32 steps = query4.value(2).toInt();
            //odczytywanie czasu
            qint32 time = query4.value(3).toInt();
            //odczytywanie ścieżki do pliku o takim samym id
            QSqlQuery query5("SELECT * FROM Kroki");
            while(query5.next())
            {
                qint32 id = query5.value(0).toInt();
                if (id == steps)
                {
                    QString path = query5.value(2).toString();
                    QString disp = query5.value(5).toString();
                    film->setFileName(path);
                    ui->opiskrokupodczasodtwarzania->setText(disp);
                    film->start();
                    //odtworzenie układu jak będzie wiadome ile czasu ma zajmować dany krok
                }
            }


    }

}
