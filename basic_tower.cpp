#include "basic_tower.h"
#include"tower.h"
#include"scene.h"
#include"basic_bullet.h"
#include"enemy.h"

int BasicTower::_cost = 100;
BasicTower::BasicTower(QPoint pos,Scene *game,const QPixmap &pix,int dam,
                       const QSize fixedsize , int attackrange, int attackrate)
      :Tower(pos,game,pix,dam,fixedsize,attackrange,attackrate)

{

}
BasicTower::~BasicTower(){
    this->_game->returnmoney(_cost / 2);
}
void BasicTower::upgrade()
{
    this->pixmap = QPixmap(":/image/IMG_0487-2.png");
    this->attackRange = 300;
    this->attackRate = 500;
    this->damage = 5;
}

void BasicTower::shootWeapon()
{

    Bullet *bullet = new BasicBullet(getPos(), targetEnemy->getCurrentPos(), damage, targetEnemy, _game);
    bullet -> move();
    _game -> addBullet(bullet);
}

int BasicTower::getCost()
{
    return _cost;
}
