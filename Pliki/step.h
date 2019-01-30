#ifndef STEP_H
#define STEP_H

#include <QDialog>
#include <QMediaPlayer>


namespace Ui {
class Step;
}

class Step : public QDialog
{
    Q_OBJECT

public:
    explicit Step(QWidget *parent = 0);
    ~Step();

private slots:

    void on_cancelbtn_clicked();

    void on_okbtn_clicked();

    void on_radioustaw_clicked();

    void on_radiozostaw_clicked();

    void on_sprawdzbtn_clicked();

public slots:

    void odbierznazwa(QString nazwa);

    void odbierzposition(qint32 position);

    void odbierzfilename(QString fileEname);

    void zakoncz();

private:
    Ui::Step *ui;

public:
    QString *nazwaukladu;
    QTime *time;
    qint32 radio;
    QMediaPlayer* player;
    QMovie* movie;


signals:
    void wyslij_path(QString path_sprawdz);
    void wyslij_speed(qint32 speed);
    void wyslij_posi(qint32 position_start);


};

#endif // STEP_H
