#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

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
    void durationChanged(qint64);
    void positionChanged(qint64);
    void on_pushButtonPlay_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonReplay_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
};

#endif // MAINWINDOW_H
