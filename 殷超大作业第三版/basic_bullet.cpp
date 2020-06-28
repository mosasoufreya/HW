#include "basic_bullet.h"
#include"scene.h"

BasicBullet::BasicBullet(QPoint startPos, QPoint targetPoint, Enemy *target, Scene *game, int damage,const QPixmap &picture,QSize fixedsize)
    :Bullet(startPos, targetPoint, damage, target, game, picture,fixedsize)
{

}
void BasicBullet::hitTarget()
{
    if (_game->enemylist().indexOf(targetEnemy) != -1) {
        targetEnemy->getDamage(damage);
    }
    _game->removeBullet(this);
}
