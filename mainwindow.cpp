#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("D:\\phdstudy\\English\\readafterme\\L01_PT2_Q2.mp3"));
    player->setVolume(200);
    player->setNotifyInterval(30);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->reset();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

void MainWindow::durationChanged(qint64 duration)
{
//    qDebug()<<qPrintable(QString("duration changed: %1\n").arg(duration));
    ui->progressBar->setRange(0, player->duration());
//    qDebug()<<"duration:"<<player->duration();
    ui->progressBar->reset();
}

void MainWindow::positionChanged(qint64 pos)
{
    qDebug()<<qPrintable(QString("pos: %1\n").arg(pos));
    ui->progressBar->setValue(pos);
    double seconds = pos*0.001;
    ui->labelTimestamp->setText(QString("%1").arg(seconds));
}

void MainWindow::on_pushButtonPlay_clicked()
{
    player->play();
}

void MainWindow::on_pushButtonPause_clicked()
{
    player->pause();
}

void MainWindow::on_pushButtonReplay_clicked()
{
    player->setPosition(2000);
    player->play();
}
