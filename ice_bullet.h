#ifndef ICEBULLET_H
#define ICEBULLET_H
#include"bullet.h"
class Scene;
class IceBullet:public Bullet
{
public:
    IceBullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
              Scene *game, const QPixmap &picture = QPixmap(":/image/IMG_0462.png"));
private slots:
    void hit_target();
};

#endif // ICEBULLET_H
