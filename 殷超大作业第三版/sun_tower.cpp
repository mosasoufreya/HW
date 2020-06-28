#include "sun_tower.h"
#include"tower.h"
#include"scene.h"
#include"enemy.h"
#include"sun_bullet.h"
int SunTower::cost = 150;
SunTower::SunTower(QPoint pos,Scene *game,const QPixmap &pix,int towertype,int dam,
                       const QSize fixedsize , int attackrange, int attackrate,int hp,const QPixmap &update,const QPixmap &remove)
      :Tower(pos,game,pix,towertype,dam,fixedsize,attackrange,attackrate,hp,update,remove)

{

}
SunTower::~SunTower(){

}
void SunTower::upgrade()
{   _game->returnMoney(-150);
    this->pixmap = QPixmap(":/image/suntower2.png");
    this->sethasUpdate();
    this->attackRange = 150;
    this->attackRate = 500;
    this->damage = 5;
}

void SunTower::shootWeapon()
{
    Bullet *bullet = new SunBullet(getPos(), targetEnemy->getCurrentPos(), targetEnemy, _game,damage);
    bullet -> move();
    _game -> addBullet(bullet);

}

int SunTower::getCost()
{
    return cost;
}
