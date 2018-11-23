#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qdesktopservices.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    //Być może za pomocą tego będzie wyświetlany końcowy układ:
    film  = new QMovie(this);
    a[4] = new QMovie(this);
    //player->setVideoOutput(film);
    //ui->Layout1->(film);
    film->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/renifer.gif");
    ui->filmlabel->setMovie(film);
    //a[1]->setFileName("C:/Users/Magda/Documents/build-mojodtwarzacz-Desktop_Qt_5_6_0_MinGW_32bit-Debug/animacje.gif");

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
    delete player;
    delete wideo;
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

}

void MainWindow::on_pausebtn_clicked()
{
     player->pause();
}

void MainWindow::on_newstepbtn_clicked()
{

}
