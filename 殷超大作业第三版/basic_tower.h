#ifndef BASICTOWER_H
#define BASICTOWER_H
#include"tower.h"
#include"scene.h"
class Scene;
class BasicTower:public Tower
{
public:
    BasicTower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/basictower.png"),int towertype=1,int dam=1,const QSize fixedsize = QSize(35, 40), int attackrange=100, int attackrate=1000,int hp=50,const QPixmap &update= QPixmap(":/image/basicup.png"),const QPixmap &remove= QPixmap(":/image/remove.png"));
    ~BasicTower();
    void upgrade();
    static int getCost();
    void checkInRange();
    void drawer(QPainter *painter);
private slots:
    void shootWeapon();

private:
    static int cost;
    qreal rotationSprite;
};

#endif // BASICTOWER_H
