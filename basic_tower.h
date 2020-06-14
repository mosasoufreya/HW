#ifndef BASICTOWER_H
#define BASICTOWER_H
#include"tower.h"
#include"scene.h"
class Scene;
class BasicTower:public Tower
{
public:
    BasicTower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/IMG_0487-2.png"),int dam=2,const QSize fixedsize = QSize(35, 40), int attackrange=100, int attackrate=1000);
    ~BasicTower();
    void upgrade();
    static int getCost();
private slots:
    void shootWeapon();

private:
    static int _cost;
};

#endif // BASICTOWER_H
