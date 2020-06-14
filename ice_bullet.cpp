#include "ice_bullet.h"
#include"scene.h"
IceBullet::IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game,const QPixmap &picture)
    :Bullet(startPos, targetPoint, damage, target, game, picture)
{

}
void IceBullet::hit_target()
{
    if (_game->enemylist().indexOf(targetEnemy) != -1) {
        targetEnemy->getDamage(damage);
    }
    _game->removeBullet(this);
}
