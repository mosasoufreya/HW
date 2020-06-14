#include "basic_bullet.h"
#include"scene.h"

BasicBullet::BasicBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, Scene *game,const QPixmap &picture)
    :Bullet(startPos, targetPoint, damage, target, game, picture)
{

}
void BasicBullet::hit_target()
{
    if (_game->enemylist().indexOf(targetEnemy) != -1) {
        targetEnemy->getDamage(damage);
    }
    _game->removeBullet(this);
}
