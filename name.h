#ifndef NAME_H
#define NAME_H

#include <QWidget>

namespace Ui {
class Name;
}

class Name : public QWidget
{
    Q_OBJECT

public:
    explicit Name(QWidget *parent = 0);
    ~Name();

private slots:
    void on_gobtn_clicked();


private:
    Ui::Name *ui;
public:
    QString* nazwa;

signals:
    void wyslijnazwe(QString nazwa);
};

#endif // NAME_H
