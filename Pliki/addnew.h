#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class addnew;
}

class addnew : public QDialog
{
    Q_OBJECT

public:
    explicit addnew(QWidget *parent = 0);
    ~addnew();

private slots:


    void on_loadbtn_clicked();

    void on_okbtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::addnew *ui;
};

#endif // ADDNEW_H
