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

    connect(player, &QMediaPlayer::positionChanged,this,&MainWindow::on_positionnchanged);
    connect(player, &QMediaPlayer::durationChanged,this,&MainWindow::on_durationnchanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

void MainWindow::on_openbtn_clicked()
{

}

void MainWindow::on_progresslider_sliderMoved(int position)
{
    player->setPosition(position);
    qDebug()<<position/1000;
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
    //Load the file
    player->setMedia(QUrl::fromLocalFile("C:/Users/Magda/Desktop/Saymyname.mp3"));
    player->setVolume(100);
    player->play();
    qDebug()<<player->errorString();


}

void MainWindow::on_stopbtn_clicked()
{
    player->stop();

}

void MainWindow::on_skipbtn_clicked()
{
     player->pause();

}
