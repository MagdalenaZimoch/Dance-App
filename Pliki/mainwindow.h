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

    QVector<QString> path_sprawdz;

    QVector<QString> disc_sprawdz;

    QVector<qint32> speed_sprawdz;





public slots:
    void odtworz(int l);

    void startnewanim();

    void ostatni();

    void path_ostatni(QString path);

    void position_ostatni(qint32 position);

    void speed_ostatni(qint32 speed);
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
    QVector<QPushButton*> a;
    QVector<QMovie*> film;
    QString* nameofsystem;
signals:
    void wyslij(qint32 position);
    void wyslij_filename(QString fileEname);

};

#endif // MAINWINDOW_H
