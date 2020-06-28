#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include"menu.h"
#include"mybutton.h"
#include"introduction.h"
#include <QMediaPlayer>
#include<QSound>
#include<QMediaPlaylist>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

  setFixedSize(1200,600);
    ui->setupUi(this);

   MyButton*bin1=new MyButton(":/image/backbin.png");//quit按钮
   bin1->setParent(this);
   bin1->move(800,300);
   connect(bin1,&MyButton::clicked,this,[=](){
       QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
       buttonPlayer->play();
       bin1->zoomdown();
       bin1->zoomup();
       QTimer::singleShot(500,this,[=](){
           this->close();
   });

  });

   MyButton*bin2=new MyButton(":/image/startbin.png");//start按钮
   bin2->setParent(this);
   bin2->move(220,320);
   Menu*scene=new Menu;
   connect(bin2,&QPushButton::clicked,this,[=](){
       QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
       buttonPlayer->play();
       bin2->zoomdown();
       bin2->zoomup();
       QTimer::singleShot(500,this,[=](){
           this->close();
           scene->show();

       });
   });
   connect(scene,&Menu::chooseBack,this,[=](){
       scene->hide();
       show();
   });
   MyButton*bin3=new MyButton(":/image/introductionBin.png");//介绍按钮
   bin3->setParent(this);
   bin3->move(120,200);
   Introduction*intro=new Introduction;
   connect(bin3,&QPushButton::clicked,this,[=](){
       QSound *buttonPlayer=new QSound("qrc:/bgm/button.wav");
       buttonPlayer->play();
       bin3->zoomdown();
       bin3->zoomup();
       QTimer::singleShot(500,this,[=](){
           this->close();
           intro->show();
       });
   });
   connect(intro,&Introduction::chooseBack,this,[=](){
       intro->hide();
       show();
   });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*){
   QPainter painter(this);
   QPixmap pixmap(":/image/open.PNG");
   painter.drawPixmap(0,0,this->width(),this->height(),pixmap);


}
