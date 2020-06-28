#include "introduction.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include"menu.h"
#include"mybutton.h"
#include "scene.h"
#include<QSound>

Introduction::Introduction(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200,600);
    MyButton*back_bin=new MyButton(":/image/backbin.png");//返回按钮
    back_bin->setParent(this);
    back_bin->move(0,0);
    connect(back_bin,&MyButton::clicked,this,[=](){
        QSound *buttonplayer=new QSound("qrc:/bgm/button.wav");
        buttonplayer->play();
        back_bin->zoomdown();
        back_bin->zoomup();
        QTimer::singleShot(500,this,[=](){
        emit chooseBack();
    });
   });

}
void Introduction::paintEvent(QPaintEvent*){
   QPainter painter(this);
   QPixmap pixmap(":/image/introduction.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

}
