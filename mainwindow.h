#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>

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
    void on_openbtn_clicked();

    void on_progresslider_sliderMoved(int position);

    void on_positionnchanged(qint64 position);

    void on_durationnchanged(qint64 position);

    void on_playbtn_clicked();

    void on_stopbtn_clicked();

    void on_skipbtn_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
};

#endif // MAINWINDOW_H
