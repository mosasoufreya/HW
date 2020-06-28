#include "basic_tower.h"
#include"tower.h"
#include"scene.h"
#include"basic_bullet.h"
#include"enemy.h"
#include <QVector2D>
#include <QtMath>

int BasicTower::cost = 80;
BasicTower::BasicTower(QPoint pos,Scene *game,const QPixmap &pix,int towertype,int dam,
                       const QSize fixedsize , int attackrange, int attackrate,int hp,const QPixmap &update,const QPixmap &remove)
      :Tower(pos,game,pix,towertype,dam,fixedsize,attackrange,attackrate,hp,update,remove)

{  rotationSprite=0.0;

}
BasicTower::~BasicTower(){

}
void BasicTower::upgrade()
{   _game->returnMoney(-80);
    this->pixmap = QPixmap(":/image/basictower2.png");
    this->sethasUpdate();
    this->attackRange = 150;
    this->attackRate = 300;
    this->damage = 3;
}

void BasicTower::shootWeapon()
{
   QPoint startpoint=getPos()+QPoint(27,22);
   QPoint targetpoint=targetEnemy->getCurrentPos()+QPoint(87,17);
    Bullet *bullet = new BasicBullet(startpoint, targetpoint,targetEnemy, _game,damage);
    bullet -> move();
    _game -> addBullet(bullet);
}

int BasicTower::getCost()
{
    return cost;
}
void BasicTower::checkInRange(){
    if (targetEnemy)
        {   QVector2D normalized(targetEnemy->getCurrentPos() -getPos());
            normalized.normalize();
             rotationSprite= qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;
            QPoint targetpoint=targetEnemy->getCurrentPos()+QPoint(60,-5);
            if (!distoCircle(getPos(), attackRange, targetpoint, 1))
                lostSight();
        }
        else
        {
            QList<Enemy *> enemyList = _game->enemylist();
    foreach (Enemy *enemy, enemyList)
    {
        if (distoCircle(getPos(), attackRange, enemy->getCurrentPos()+QPoint(60,-5), 1))
        {
            attackChoose(enemy);
            break;
        }
    }
  }
}
void BasicTower::drawer(QPainter *painter){
     painter->save();
     QPoint lifePoint = getPos() + QPoint(19, -10);

     painter->setPen(Qt::NoPen);
     painter->setBrush(Qt::white);
     QRect lifePointRect(lifePoint, QSize(10, 3));
     painter->drawRect(lifePointRect);

     painter->setBrush(Qt::green);
     QRect healthBarRect(lifePoint, QSize((double)curhp / Hp * 30, 3));
     painter->drawRect(healthBarRect);
    const QPoint newPos(15, 5);
    painter->translate(this->getPos());
    painter->rotate(rotationSprite);
    painter->drawPixmap(newPos.x(), newPos.y() , 35,40,  this->pixmap);

    painter->restore();
}
