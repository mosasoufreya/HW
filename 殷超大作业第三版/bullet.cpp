#include "bullet.h"
#include"scene.h"
#include"enemy.h"
Bullet::Bullet(QPoint startpoint, QPoint targetpoint, int dam, Enemy *target,Scene*game,const QPixmap &pic,QSize fixedsize)
    : QObject(0),pix(pic),targetEnemy(target),_game(game),damage(dam),fixedSize(fixedsize)
{   startPoint=startpoint;
    targetPoint=targetpoint;
    curpoint=startpoint;

}
void Bullet:: drawer(QPainter *painter){
    painter->drawPixmap(curpoint.x(),curpoint.y(),fixedSize.width(),fixedSize.height(),pix);
}
void Bullet::move(){

    QPropertyAnimation*anima=new QPropertyAnimation(this,"curpoint");
    anima->setDuration(200);
    anima->setStartValue(startPoint);
    anima->setEndValue(targetPoint);
    connect(anima, SIGNAL(finished()), this, SLOT(hitTarget()));
    anima->start();

}
void Bullet::setCurrentPos(QPoint pos){
    curpoint=pos;
}
QPoint Bullet::getCurrentPos(){
    return curpoint;
}
