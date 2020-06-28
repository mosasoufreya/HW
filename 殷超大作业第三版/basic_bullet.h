#ifndef BASICBULLET_H
#define BASICBULLET_H

#include"bullet.h"
class Scene;
class Enemy;
class BasicBullet:public Bullet
{
public:
    BasicBullet(QPoint startPos, QPoint targetPoint, Enemy *target,
               Scene *game,  int damage,const QPixmap &picture = QPixmap(":/image/basicbullet.png"),QSize fixedsize= QSize(10, 10));
private slots:
    void hitTarget();
};

#endif // BASICBULLET_H
