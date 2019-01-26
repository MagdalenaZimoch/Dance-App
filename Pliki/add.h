#ifndef ADD_H
#define ADD_H

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

private slots:


private:
    Ui::MainWindow *add;

};

#endif // ADD_H
