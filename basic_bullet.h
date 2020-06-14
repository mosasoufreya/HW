#ifndef BASICBULLET_H
#define BASICBULLET_H

#include"bullet.h"
class Scene;
class Enemy;
class BasicBullet:public Bullet
{
public:
    BasicBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
               Scene *game, const QPixmap &picture = QPixmap(":/image/IMG_0462-2.png"));
private slots:
    void hit_target();
};

#endif // BASICBULLET_H
