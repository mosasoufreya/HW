#ifndef BASICENEMY_H
#define BASICENEMY_H
#include "enemy.h"
#include "mainwindow.h"
class Scene;
class BasicEnemy:public Enemy
{
public:
    BasicEnemy(Scene*game, const QPixmap &pixmap= QPixmap(":/image/basicenemy.png"),QSize fixedsize= QSize(50, 50),
               int curhp=50,int speed=3,int hp=50,int mon=100,const QPixmap &iceenemy=QPixmap(":/image/icebasicenemy.png"),const QPixmap&fireenemy=QPixmap(":/image/firebasicenemy.png"));

    void summon();
    ~BasicEnemy();
    void targetDied();
    void checkInRange();
    void drawRange(QPainter *painter);
private slots:
    void shootWeapon();
};

#endif // BASICENEMY_H
