#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QtDebug>
#include <QFileDialog>
#include <QVideoWidget>
#include <QString>
#include <QMovie>
#include <QPropertyAnimation>
#include <QVector>
#include <QtSql>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void nameof(QString name);


private slots:
    void namesystem(QString name);

    void on_openbtn_clicked();

    void on_progresslider_sliderMoved(int position);

    void on_positionnchanged(qint64 position);

    void on_durationnchanged(qint64 position);

    void on_playbtn_clicked();

    void on_stopbtn_clicked();

    void on_pausebtn_clicked();

    void on_newstepbtn_clicked();

    void klickbtn();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* wideo;
    QMovie* film;
    QVector<QPushButton*> a;
    QVector<QMovie*> movie;
    QString* nameofsystem;


};

#endif // MAINWINDOW_H
