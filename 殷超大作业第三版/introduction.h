#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QMainWindow>

class Introduction : public QMainWindow
{
    Q_OBJECT
public:
    explicit Introduction(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
signals:
    void chooseBack();
public slots:

};

#endif // INTRODUCTION_H
