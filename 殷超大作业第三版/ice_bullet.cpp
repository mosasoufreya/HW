#include "ice_bullet.h"
#include"scene.h"
IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, Enemy *target, Scene *game,int damage,const QPixmap &picture,QSize fixedsize)
    :Bullet(startPos, targetPoint, damage, target, game, picture,fixedsize)
{

}
void IceBullet::hitTarget()
{
    if (_game->enemylist().indexOf(targetEnemy) != -1) {
        targetEnemy->slowDown();
        targetEnemy->getDamage(damage);
    }
    _game->removeBullet(this);
}
