#include "ice_tower.h"
#include"tower.h"
#include"scene.h"
#include"ice_bullet.h"
#include"enemy.h"
int IceTower::cost = 100;
IceTower::IceTower(QPoint pos,Scene *game,const QPixmap &pix,int towertype,int dam,
                       const QSize fixedsize , int attackrange, int attackrate,int hp,const QPixmap &update,const QPixmap &remove)
      :Tower(pos,game,pix,towertype,dam,fixedsize,attackrange,attackrate,hp,update,remove)

{

}
IceTower::~IceTower(){

}
void IceTower::upgrade()
{   _game->returnMoney(-100);
    this->pixmap = QPixmap(":/image/icetower2.png");
    this->sethasUpdate();
    this->attackRange = 120;
    this->attackRate = 300;
    this->damage = 5;
}

void IceTower::shootWeapon()
{   QPoint startpoint=getPos()+QPoint(27,22);
    QPoint targetpoint=targetEnemy->getCurrentPos()+QPoint(87,17);
    Bullet *bullet = new IceBullet(startpoint, targetpoint, targetEnemy, _game,damage);
    bullet -> move();
    _game -> addBullet(bullet);
}

int IceTower::getCost()
{
    return cost;
}
