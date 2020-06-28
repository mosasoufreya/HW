#ifndef ICEBULLET_H
#define ICEBULLET_H
#include"bullet.h"
class Scene;
class IceBullet:public Bullet
{
public:
    IceBullet(QPoint startPos, QPoint targetPoint, Enemy *target,
              Scene *game,  int damage,const QPixmap &picture = QPixmap(":/image/icebullet.png"),QSize fixedsize= QSize(10, 10));
private slots:
    void hitTarget();
};

#endif // ICEBULLET_H
