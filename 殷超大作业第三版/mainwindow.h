#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPainter>
#include <QPaintEvent>
#include <QMediaPlayer>
#include<QSound>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void playSound();
    void stopSound();
private:
    Ui::MainWindow *ui;
    QSound *player;

};
#endif // MAINWINDOW_H
