#include "bullet.h"
#include"scene.h"
#include"enemy.h"
Bullet::Bullet(QPoint startpoint, QPoint targetpoint, int dam, Enemy *target,Scene*game,const QPixmap &pic)
    : QObject(0),pix(pic),targetEnemy(target),_game(game),damage(dam)
{   curpoint=startpoint;
    _targetpoint=targetpoint;


}
void Bullet:: drawer(QPainter *painter){
    painter->drawPixmap(curpoint,pix);
}
void Bullet::move(){

    QPropertyAnimation*anima=new QPropertyAnimation(this,"curpoint");
    anima->setDuration(2000);
    anima->setStartValue(_startpoint);
    anima->setEndValue(_targetpoint);
    connect(anima, SIGNAL(finished()), this, SLOT(hit_target()));
    anima->start();

}
void Bullet::setCurrentPos(QPoint pos){
    curpoint=pos;
}
QPoint Bullet::getCurrentPos(){
    return curpoint;
}
