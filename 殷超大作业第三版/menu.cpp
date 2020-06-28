#include "menu.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include"menu.h"
#include"mybutton.h"
#include "scene.h"
#include<QSound>
Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
  setFixedSize(1200,600);
  MyButton*back_bin=new MyButton(":/image/backbin.png");//返回按钮
  back_bin->setParent(this);
  back_bin->move(0,0);
  connect(back_bin,&MyButton::clicked,this,[=](){
      QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
      buttonPlayer->play();
      back_bin->zoomdown();
      back_bin->zoomup();
      QTimer::singleShot(500,this,[=](){
      emit chooseBack();
  });
 });

  MyButton*bin1=new MyButton(":/image/startbin2.png");//start按钮
  bin1->setParent(this);
  bin1->move(90,190);
  Scene*scene=new Scene;
  connect(bin1,&QPushButton::clicked,this,[=](){
      QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
      buttonPlayer->play();
      bin1->zoomdown();
      bin1->zoomup();
      QTimer::singleShot(500,this,[=](){
          scene->setScene(1);
          scene->LoadTowerPos();
          scene->loadEnemy();
          scene->setSound();
          this->close();
          scene->show();
          scene->gameStart();
      });
  });
  connect(scene,&Scene::chooseBack,this,[=](){
      scene->hide();
      show();
  });

  MyButton*bin2=new MyButton(":/image/startbin2.png");//start按钮
  bin2->setParent(this);
  bin2->move(90,320);
  Scene*scene2=new Scene;
  connect(bin2,&QPushButton::clicked,this,[=](){
      QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
      buttonPlayer->play();
      bin2->zoomdown();
      bin2->zoomup();
      QTimer::singleShot(500,this,[=](){
          scene2->setScene(2);
          scene2->LoadTowerPos();
          scene2->loadEnemy();
          scene2->setSound();
          this->close();
          scene2->show();
          scene2->gameStart();
      });
  });
  connect(scene2,&Scene::chooseBack,this,[=](){
      scene2->hide();
      show();
  });


}
void Menu::paintEvent(QPaintEvent*){
   QPainter painter(this);
   QPixmap pixmap(":/image/menu.PNG");
   painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

}
