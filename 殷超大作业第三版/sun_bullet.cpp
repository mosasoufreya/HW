#include "sun_bullet.h"
#include"scene.h"
#include<cmath>
SunBullet::SunBullet(QPoint startPos, QPoint targetPoint, Enemy *target, Scene *game, int damage,const QPixmap &picture,QSize fixedsize,int attackrange)
    :Bullet(startPos, targetPoint, damage, target, game,picture,fixedsize),attackRange(attackrange)
{

}
void SunBullet::hitTarget()
{
    if (_game->enemylist().indexOf(targetEnemy) != -1) {
            QList<Enemy *> enemyList = _game->enemylist();
            foreach (Enemy *enemy, enemyList){
                const double deltaX = enemy->getCurrentPos().x() - startPoint.x();
                const double deltaY = enemy->getCurrentPos().y() - startPoint.y();
                const double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
                if(distance<150&&enemy->getActive()==true){
                    enemy->HasFire();
                    enemy->getDamage(damage);
                }
            }
        }
        _game->removeBullet(this);

}
void SunBullet:: drawer(QPainter *painter){
    if(attackRange==150)attackRange=0;
        attackRange+=10;//扩散效果
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::yellow);
        const QPoint newPos(30, 20);
        painter->translate(getCurrentPos());
        painter->drawEllipse(newPos, this->attackRange, this->attackRange);
        painter->restore();

}
void SunBullet::move(){
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(hitTarget()));
        timer->start(500);
}

