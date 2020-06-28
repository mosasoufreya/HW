#include "enemy_bullet.h"
#include"scene.h"
#include"tower.h"
#include<QPropertyAnimation>
EnemyBullet::EnemyBullet(QPoint startpoint, QPoint targetpoint, int dam, Tower *target,Scene*game,const QPixmap &pic,QSize fixedsize)
    : QObject(0),pix(pic),targetTower(target),_game(game),damage(dam),fixedSize(fixedsize)
{   startPoint=startpoint;
    targetPoint=targetpoint;
    curpoint=startpoint;

}
void EnemyBullet:: drawer(QPainter *painter){
    painter->drawPixmap(curpoint.x(),curpoint.y(),fixedSize.width(),fixedSize.height(),pix);
}
void EnemyBullet::move(){

    QPropertyAnimation*anima=new QPropertyAnimation(this,"curpoint");
    anima->setDuration(200);
    anima->setStartValue(startPoint);
    anima->setEndValue(targetPoint);
    connect(anima, SIGNAL(finished()), this, SLOT(hitTarget()));
    anima->start();

}
void EnemyBullet::setCurrentPos(QPoint pos){
    curpoint=pos;
}
QPoint EnemyBullet::getCurrentPos(){
    return curpoint;
}
void EnemyBullet::hitTarget()
{
    if (_game->towerlist().indexOf(targetTower) != -1) {
        targetTower->getDamage(damage);
    }
    _game->removeEnemyBullet(this);
}
