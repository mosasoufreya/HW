#ifndef SUNTOWER_H
#define SUNTOWER_H
#include"tower.h"
#include"scene.h"
#include"sun_bullet.h"
class SunTower:public Tower
{
public:
    SunTower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/suntower.png"),int towertype=3,int dam=5,const QSize fixedsize = QSize(35, 40), int attackrange=150, int attackrate=1000,int hp=50,const QPixmap &update= QPixmap(":/image/sunup.png"),const QPixmap &remove= QPixmap(":/image/remove.png"));
    ~SunTower();
    void upgrade();
    static int getCost();
private slots:
    void shootWeapon();

private:
    static int cost;
};

#endif // SUNTOWER_H
