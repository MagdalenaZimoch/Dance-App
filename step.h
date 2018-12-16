#ifndef STEP_H
#define STEP_H

#include <QDialog>


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
public slots:

    void odbierznazwa(QString nazwa);

private:
    Ui::Step *ui;

public:
    QString *nazwaukladu;

};

#endif // STEP_H
