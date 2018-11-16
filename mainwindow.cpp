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
    wideo = new QVideoWidget(this);
    player->setVideoOutput(wideo);
    wideo->show();

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
    QString filename = QFileDialog::getOpenFileName(this,"Open a file","","Music File(*.mp3)");
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
}

void MainWindow::on_stopbtn_clicked()
{
    player->stop();

}

void MainWindow::on_skipbtn_clicked()
{
     player->pause();
}

void MainWindow::on_newstepbtn_clicked()
{

}
