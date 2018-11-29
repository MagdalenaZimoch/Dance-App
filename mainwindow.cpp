#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qdesktopservices.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/Magda/Documents/mojodtwarzacz/test.db");

    if(mydb.open())
    {
        qDebug()<<"udalo sie";

        mydb.close();
    }



    player = new QMediaPlayer(this);
    //Za pomocą tego będzie wyświetlany końcowy układ:
    film  = new QMovie(this);
    film->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/renifer.gif");
    ui->filmlabel->setMovie(film);


    //wygląd :
    auto central = new QWidget(this);
    auto grid = new QGridLayout(this);
    central->setLayout(grid);
    ui->scrollArea->setWidget(central);
    grid->setColumnMinimumWidth(3,120);
    grid->setVerticalSpacing(6);
    grid->setHorizontalSpacing(6);

    //dynamiczne dodawanie przycisków

    for(int i=0;i<18;i++)
    {
        auto anim = new QPushButton(this);
        a.append(anim);

        auto movi = new QMovie(this);
        movie.append(movi);

        grid->addWidget(a[i]);

        a[i]->setMinimumHeight(120);
        a[i]->setMinimumWidth(120);
        if (i%2==0){
        movie[i]->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/Akrobacje.gif");
        }
        else{
        movie[i]->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/Akrobacje2.gif");
        }
        connect(movie[i], &QMovie::frameChanged, [=]{a[i]->setIcon(movie[i]->currentPixmap());});
        a[i]->setIconSize(QSize(120,120));
        movie[i]->start();
    }

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
    //qDebug()<<"tutaj jest path: "+filename;

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

}
