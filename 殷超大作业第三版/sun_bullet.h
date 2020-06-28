#ifndef SUNBULLET_H
#define SUNBULLET_H


#include"bullet.h"
class Scene;
class Enemy;
class SunBullet:public Bullet
{
public:
    SunBullet(QPoint startPos, QPoint targetPoint, Enemy *target,
               Scene *game, int damage,const QPixmap &picture = QPixmap(":/image/sunbullet.png"),QSize fixedsize= QSize(10, 10),int attackrange=150);
    virtual void drawer(QPainter *painter);
    virtual void move();
private slots:
    void hitTarget();
private:
    int attackRange;
};
#endif // SUNBULLET_H
