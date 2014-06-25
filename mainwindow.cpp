#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusPlay = true;
    m_statusReplay = false;
    m_posStart = 0;
    m_posEnd = 0;

    player = new QMediaPlayer(this);
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("D:\\phdstudy\\English\\readafterme\\L01_PT2_Q2.mp3"));
    player->setNotifyInterval(30);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->reset();
    ui->labelTimestamp->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
}

QString MainWindow::timeToString(qint64 timestamp)
{
    int seconds = (timestamp/1000) % 60;
    int minutes = (timestamp/60000) % 60;
    int hours = (timestamp/3600000) % 24;
    QTime time(hours, minutes,seconds);
    return time.toString();
}

void MainWindow::durationChanged(qint64 duration)
{
    player->setVolume(100);
//    qDebug()<<qPrintable(QString("duration changed: %1\n").arg(duration));
    ui->progressBar->setRange(0, duration);
    qDebug()<<"duration:"<<duration;
    ui->progressBar->reset();
}

void MainWindow::positionChanged(qint64 pos)
{
//    qDebug()<<qPrintable(QString("pos: %1\n").arg(pos));
    ui->progressBar->setValue(pos);
    ui->labelTimestamp->setText(QString("%1/%2").arg(timeToString(pos), timeToString(player->duration())));
    if(pos==player->duration())
    {
        m_statusPlay = true;
        ui->pushButtonPlay->setText("Play");
    }
    if(m_statusReplay)
    {
        if(player->position()>=m_posEnd)
        {
            player->pause();
        }
    }
}

void MainWindow::on_pushButtonPlay_clicked()
{
    if(m_statusPlay)
    {
        m_posStart = player->position();
        player->play();
        ui->pushButtonPlay->setText("Pause");
        m_statusReplay = false;
    }
    else
    {
        m_posEnd = player->position();
        player->pause();
        ui->pushButtonPlay->setText("Play");
    }
    m_statusPlay = !m_statusPlay;
}

void MainWindow::on_pushButtonReplay_clicked()
{
    m_statusReplay = true;
    player->setPosition(m_posStart);
    player->play();
}
