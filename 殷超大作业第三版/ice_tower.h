#ifndef ICETOWER_H
#define ICETOWER_H
#include"tower.h"
#include"scene.h"

class IceTower:public Tower
{
public:
    IceTower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/icetower.png"),int towertype=2,int dam=2,const QSize fixedsize = QSize(35, 40), int attackrange=100, int attackrate=1000,int hp=50,const QPixmap &update= QPixmap(":/image/iceup.png"),const QPixmap &remove= QPixmap(":/image/remove.png"));
    ~IceTower();
    void upgrade();
    static int getCost();
private slots:
    void shootWeapon();

private:
    static int cost;
};

#endif // ICETOWER_H
