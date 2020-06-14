#include "scene.h"
#include "ui_scene.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include"mybutton.h"
#include"tower.h"
#include<QList>
#include"enemy.h"
#include"towerposition.h"
#include<QPixmap>
#include"bullet.h"
#include<QPoint>
#include <QDebug>
#include"basic_tower.h"
#include"basic_enemy.h"
Scene::Scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scene),
    wave(0),homeHP(10),money(900),win(false),lose(false)
{
  setFixedSize(1200,600);
    ui->setupUi(this);


      startpoint.setX(0);
      startpoint.setY(0);
      home.setX(700);
      home.setY(158);
      dochoose=false;

      LoadTowerPos();

      MyButton*back_bin=new MyButton(":/image/IMG_0450-2.png");//返回按钮
      back_bin->setParent(this);
      back_bin->move(0,0);
      connect(back_bin,&MyButton::clicked,this,[=](){
          back_bin->zoomdown();
          back_bin->zoomup();
          QTimer::singleShot(500,this,[=](){
          emit chooseBack();
      });
     });





      QTimer*timer=new QTimer(this);
      connect(timer, SIGNAL(timeout()),this,SLOT(updateScreen()));
      timer->start(30);
      QTimer::singleShot(3000, this, SLOT(gamestart()));

}

Scene::~Scene()
{  for(auto &enemy: this->enemy_list)
    {
        enemy->getRemoved();
    }

    for(auto &bullet: this->bullet_list)
    {
        removeBullet(bullet);
    }

    for(auto &tower: this->tower_list)
    {
        removeTower(tower);
    }
    delete ui;

}
void Scene::paintEvent(QPaintEvent*){
    if(lose){
            QPainter painter(this);
            QPixmap loseBQB(":/image/IMG_0460.PNG");
            painter.drawPixmap(0,0,1950,1080,loseBQB);
            return;
        }
   //画地图
   QPixmap pixmap(":/image/WechatIMG45.png");

   //画塔位、敌人、子弹、塔
   QPainter Painter(&pixmap);
   for(auto &towerPosition: this->towerpos_list)
   {
       if(towerPosition.hasShow())
           towerPosition.drawer(&Painter);
   }

   for(auto &enemy: this->enemy_list)
   {
       enemy->drawer(&Painter);
   }

   for(auto &Tower: this->tower_list)
   {
       Tower->drawer(&Painter);
       if(Tower->hasShowRange())
           Tower->drawRange(&Painter);
   }
   for(auto &bullet: this->bullet_list)
   {
       bullet->drawer(&Painter);
   }
   drawHP(&Painter);
   drawMoney(&Painter);
   drawWaves(&Painter);
  QPainter painter(this);
  painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
  if(win){
          QPixmap back(":/image/IMG_0460.PNG");
          QPixmap victory(":/image/IMG_0460.PNG");
          painter.drawPixmap(0,0,1980,1080,back);
          painter.drawPixmap(700, 200, 549, 441, victory);
      }


}

void Scene::updateScreen(){
    for(auto &enemy: this->enemy_list)
        enemy->move();
    for(auto &tower: this->tower_list)
        tower->checkInRange();
    update();
}

//设置塔可以放置的位置
void Scene::LoadTowerPos(){
    qDebug("loadtowerpos");
    QPoint pos[] =
    {
        //first row
        QPoint(320, 158),
        QPoint(385, 158),
        QPoint(505, 158),
        QPoint(565, 158),
        QPoint(625, 158),
        QPoint(750, 158),
        QPoint(810, 158),

        //second row
        QPoint(320, 220),
        QPoint(385, 220),
        QPoint(505, 220),
        QPoint(565, 220),
        QPoint(625, 220),
        QPoint(750, 220),
        QPoint(810, 220),
        //third row
        QPoint(505, 282),
        QPoint(565, 282),
        QPoint(625, 282),
        //fourth row
        QPoint(385, 344),
        QPoint(445, 344),
        QPoint(505, 344),
        QPoint(565, 344),
        QPoint(625, 344),
        QPoint(690, 344),
        QPoint(750, 344),

    };
    int num = sizeof(pos) / sizeof(pos[0]);

    for(int i = 0; i < num; ++ i)
        this->towerpos_list.push_back(TowerPosition(pos[i]));
}

//画towerposition

void Scene::mousePressEvent(QMouseEvent *event){
    QPoint pressPos = event->pos();
    for(auto &curPos: towerpos_list)  {
        if(curPos.inRange(pressPos))
        {  qDebug("test->2");
            if(curPos.inRange(pressPos))
            {   qDebug("test->1");
                curChoose = NULL;
            }
            if(curPos.hasShow() && !curPos.hasTower())
            {   qDebug("test->3");
                curPos.sethasTower();
                Tower *tower = new BasicTower(curPos.getPos(),this);
                this->tower_list.push_back(tower);
                returnmoney(-BasicTower::getCost());


            }

            else if(curPos.hasTower())
            {qDebug("test->4");
                bool break_flag = false;
                for(auto &curTower: tower_list)
                {
                    if(curTower->getPos() == curPos.getPos())
                    { qDebug("test->5");
                        break_flag = true;
                        if(!curTower->hasShowRange()) {
                            curTower->setHasShowRange();
                            curChoose = curTower;
                            curtowerPos = &curPos;
                        }
                        else {qDebug("test->6");
                           curTower->setHasShowRange(false);
                            if(curChoose)
                                curChoose = NULL;
                        }
                        break;
                    }
                }
                if(break_flag)
                    break;
           }
        }
        else
        {
            if(curChoose) {qDebug("test->7");
                curChoose->setHasShowRange(false);
                curChoose = NULL;
            }
        }
  }
    this->setCursor(Qt::ArrowCursor);
    for(auto &temp: this->towerpos_list)
        {
            temp.sethasShow(false);
        }
 update();

}

void Scene::gamestart(){
  loadWave();
}
bool Scene::loadWave(){
    if (wave >= 9)
        return false;
    int start_interval[]={1000,5000,9000};
    for(int i=0;i<3;++i){
        Enemy*enemy=new BasicEnemy(this);
        enemy_list.push_back(enemy);
        QTimer::singleShot(start_interval[i],enemy,SLOT(doActive()));
    }
    return true;
}
void Scene::on_tower_clicked(){
   qDebug("test->9");
    QCursor *myCursor = new QCursor(QPixmap(":/image/IMG_0487-2.png"),-1,-1);
    this->setCursor(*myCursor);
    for(auto &temp: this->towerpos_list)
    {
        temp.sethasShow();

    }

    update();
}
QList<Enemy *> Scene::enemylist() const
{
    return enemy_list;
}
void Scene::getDamage(int dam){
   homeHP -= dam;
   if(homeHP <= 0)
            gameOver();
}
void Scene::removeEnemy(Enemy *enemy){
       enemy->summon();
       enemy_list.removeOne(enemy);
       delete enemy;
       if (enemy_list.empty())
           {
               ++ wave;
           }
}
void Scene::removeBullet(Bullet *bullet){
   if (bullet_list.indexOf(bullet) != -1)

        bullet_list.removeOne(bullet);
       delete bullet;
}
void Scene::addBullet(Bullet *bullet){

       bullet_list.push_back(bullet);
}
void Scene::returnmoney(int mon){
    money=money+mon;
}
void Scene::gameOver()
{

    if (!lose)
    {
        lose = true;

    }
}
void Scene::removeTower(Tower *tower)
{
    tower_list.removeOne(tower);
    delete tower;
}
void Scene::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(760, 133, 20, 25), QString("%70").arg(homeHP));
}

void Scene::drawMoney(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    painter->drawText(QRect(300, 20, 80, 50), QString("%70").arg(money));
}
void Scene::drawWaves(QPainter *painter)//incomplete
{
    painter->setPen(Qt::red);

}
