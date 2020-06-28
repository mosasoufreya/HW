#include "enemy.h"
#include "tower.h"
#include"cmath"
#include "waypoint.h"
#include"scene.h"
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include <QList>
#include"sun_bullet.h"
#include<QSound>
#include <QMediaPlayer>
Enemy::Enemy( Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp,int mon,const QPixmap &iceenemy,const QPixmap&fireenemy)
    :QObject(0),pix(pixmap),HP(hp),curHP(curhp),Speed(speed),damage(0),_game(game),fixedSize(fixedsize),money(mon),iceEnemy(iceenemy),fireEnemy(fireenemy)
{
  active=false;
  slowTime = new QTimer(this);
  connect(slowTime,SIGNAL(timeout()), this, SLOT(normalSpeed()));
  hasSlowDown=false;
  hasFired=false;
  fireTime=new QTimer(this);
  connect(fireTime,SIGNAL(timeout()), this, SLOT(stopFire()));
}
Enemy::~Enemy()
{
    attacker_list.clear();
    waypoint = NULL;
    _game = NULL;
    delete slowTime;
    slowTime = NULL;
    delete fireTime;
    fireTime= NULL;
}

void Enemy:: drawer(QPainter *painter){
    if (!active)
            return;
       painter->save();

        QPoint lifePoint = curpoint + QPoint(75, -10);

        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::white);
        QRect lifePointRect(lifePoint, QSize(10, 3));
        painter->drawRect(lifePointRect);

        painter->setBrush(Qt::green);
        QRect healthBarRect(lifePoint, QSize((double)curHP / HP * 30, 3));
        painter->drawRect(healthBarRect);
        static const QPoint offsetPoint(60, -5);
         painter->translate(curpoint);
      if(!hasSlowDown){
         painter->drawPixmap(offsetPoint.x(), offsetPoint.y(), fixedSize.width() ,fixedSize.height(), pix);
     }
      if(hasSlowDown){
          painter->drawPixmap(offsetPoint.x(), offsetPoint.y(), fixedSize.width() ,fixedSize.height(), iceEnemy);
         }
      if(hasFired){
          painter->drawPixmap(offsetPoint.x(), offsetPoint.y(), fixedSize.width() ,fixedSize.height(), fireEnemy);
         }
         painter->restore();
}
void Enemy::move(){
    if (!active)
        return;

    if (distoCircle(curpoint, 1, waypoint->pos(), 1))
    {

        if (waypoint->nextWayPoint())
        {
            curpoint = waypoint->pos();
            waypoint = waypoint->nextWayPoint();
        }
        else
                {if(!attacker_list.empty()){
                for(auto &attacker:attacker_list)
                    attacker->targetdied();
            }
                QList<Tower *>towerList=_game->towerlist();
               foreach(Tower *tower,towerList){
                    tower->loseSight(this);
                }
                     active=false;
                    _game->getDamage();
                    _game->removeEnemy(this);
                    return;
    }
  }


    QPoint targetPoint = waypoint->pos();
    qreal movementSpeed = Speed;
    QVector2D normalized(targetPoint - curpoint);
    normalized.normalize();
    curpoint += normalized.toPoint() * movementSpeed;
    checkInRange();
}
void Enemy::setCurrentPos(QPoint pos){
    curpoint=pos;
}
QPoint Enemy::getCurrentPos(){
    return curpoint;
}
void Enemy::lostSight(Tower *attacker)
{
    attacker_list.removeOne(attacker);
}

void Enemy::getAttack(Tower *attacker)
{
    attacker_list.push_back(attacker);
}
void Enemy::doActive(){
    active=true;
}
bool Enemy::distoCircle(QPoint p1, double r1, QPoint p2, double r2)
{
    const double deltaX = p1.x() - p2.x();
    const double deltaY = p1.y() - p2.y();
    const double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if(distance < r1 + r2)
        return true;

    return false;
}

void Enemy::getDamage(int dam)
{
     curHP=curHP-dam;
      if (curHP <= 0)
          {
              QSound *enemyPlayer;
              if(enemyType==1)enemyPlayer=new QSound("qrc:/bgm/basic.wav");
              if(enemyType==2)enemyPlayer=new QSound("qrc:/bgm/attack.wav");
              if(enemyType==3)enemyPlayer=new QSound("qrc:/bgm/boss.wav");

              enemyPlayer->play();
              getRemoved();
          }
}

void Enemy::getRemoved()
{
   if(attacker_list.empty())
        return;
  for(auto &attacker: attacker_list)
        attacker->targetdied();
  QList<Tower *> towerList = _game->towerlist();
foreach (Tower *tower, towerList)
{
    tower->loseSight(this);
}
    _game->returnMoney(100);
    _game->removeEnemy(this);
}
void Enemy::addWaypoint(){
    WayPoint *wayPointz = new WayPoint(QPoint(640, 158));
        waypoint_list.push_back(wayPointz);
        WayPoint *wayPoint1 = new WayPoint(QPoint(640, 280));
       waypoint_list.push_back(wayPoint1);
        wayPoint1->setNextWayPoint(wayPointz);
        WayPoint *wayPoint2 = new WayPoint(QPoint(760, 280));
        waypoint_list.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);
        WayPoint *wayPoint3= new WayPoint(QPoint(760, 400));
        waypoint_list.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);
        WayPoint *wayPoint4 = new WayPoint(QPoint(280, 400));
        waypoint_list.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);
        WayPoint *wayPoint5 = new WayPoint(QPoint(280, 280));
        waypoint_list.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);
        WayPoint *wayPoint6 = new WayPoint(QPoint(385, 280));
        waypoint_list.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);
        WayPoint *wayPoint7 = new WayPoint(QPoint(385,158));
        waypoint_list.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);
}
//减速
void Enemy::slowDown(){
    slowTime->start(3000);

    if(!hasSlowDown){
        Speed/=2;
        hasSlowDown=true;
    }

}
//恢复原速
void Enemy::normalSpeed(){
    if(hasSlowDown){
        Speed*=2;
        hasSlowDown=false;
    }
}
//火焰特效
void Enemy::HasFire(){
    fireTime->start(500);
    hasFired=true;
}
void Enemy::stopFire(){
    if(hasFired){
        hasFired=false;
    }
}
void Enemy::addWaypoint2(){
    WayPoint *wayPointz = new WayPoint(QPoint(820, 160));
        waypoint_list.push_back(wayPointz);
        WayPoint *wayPoint1 = new WayPoint(QPoint(820, 274));
       waypoint_list.push_back(wayPoint1);
        wayPoint1->setNextWayPoint(wayPointz);
        WayPoint *wayPoint2 = new WayPoint(QPoint(880, 274));
        waypoint_list.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);
        WayPoint *wayPoint3= new WayPoint(QPoint(880, 398));
        waypoint_list.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);
        WayPoint *wayPoint4 = new WayPoint(QPoint(700, 398));
        waypoint_list.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);
        WayPoint *wayPoint5 = new WayPoint(QPoint(700, 274));
        waypoint_list.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);
        WayPoint *wayPoint6 = new WayPoint(QPoint(748, 274));
        waypoint_list.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);
        WayPoint *wayPoint7 = new WayPoint(QPoint(748,150));
        waypoint_list.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);
        WayPoint *wayPoint8 = new WayPoint(QPoint(575,150));
        waypoint_list.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);
        WayPoint *wayPoint9 = new WayPoint(QPoint(575,398));
        waypoint_list.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);
        WayPoint *wayPoint10 = new WayPoint(QPoint(450,398));
        waypoint_list.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);
        WayPoint *wayPoint11 = new WayPoint(QPoint(450,150));
        waypoint_list.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);
        WayPoint *wayPoint12 = new WayPoint(QPoint(270,150));
        waypoint_list.push_back(wayPoint12);
        wayPoint12->setNextWayPoint(wayPoint11);
        WayPoint *wayPoint13= new WayPoint(QPoint(270,274));
        waypoint_list.push_back(wayPoint13);
        wayPoint13->setNextWayPoint(wayPoint12);
        WayPoint *wayPoint14 = new WayPoint(QPoint(330,274));
        waypoint_list.push_back(wayPoint14);
        wayPoint14->setNextWayPoint(wayPoint13);
        WayPoint *wayPoint15 = new WayPoint(QPoint(330,398));
        waypoint_list.push_back(wayPoint15);
        wayPoint15->setNextWayPoint(wayPoint14);
        WayPoint *wayPoint16 = new WayPoint(QPoint(155,398));
        waypoint_list.push_back(wayPoint16);
        wayPoint16->setNextWayPoint(wayPoint15);
        WayPoint *wayPoint17 = new WayPoint(QPoint(155,274));
        waypoint_list.push_back(wayPoint17);
        wayPoint17->setNextWayPoint(wayPoint16);
        WayPoint *wayPoint18 = new WayPoint(QPoint(205,274));
        waypoint_list.push_back(wayPoint18);
        wayPoint18->setNextWayPoint(wayPoint17);
        WayPoint *wayPoint19 = new WayPoint(QPoint(205,160));
        waypoint_list.push_back(wayPoint19);
        wayPoint19->setNextWayPoint(wayPoint18);


}
bool Enemy::getActive(){
    return  active;
}

