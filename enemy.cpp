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


Enemy::Enemy( Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp)
    :QObject(0),pix(pixmap),HP(hp),curHP(curhp),Speed(speed),damage(0),_game(game),fixedSize(fixedsize)
{
  active=false;
}
Enemy::~Enemy()
{
    attacker_list.clear();
    waypoint = NULL;
    _game = NULL;
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

         painter->drawPixmap(offsetPoint.x(), offsetPoint.y(), 50 ,50, pix);

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
                {
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
}
void Enemy::setCurrentPos(QPoint pos){
    curpoint=pos;
}
QPoint Enemy::getCurrentPos(){
    return curpoint;
}
void Enemy::lostSight(Tower *attacker)
{
    //attacker_list.removeOne(attacker);
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
              getRemoved();
          }
}

void Enemy::getRemoved()
{
   if(attacker_list.empty())
        return;
  for(auto &attacker: attacker_list)
        attacker->targetdied();

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
