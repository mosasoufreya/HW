#ifndef BOSS_H
#define BOSS_H


#include "enemy.h"
#include "mainwindow.h"
class Scene;
class Boss:public Enemy
{
public:
    Boss(Scene*game, const QPixmap &pixmap= QPixmap(":/image/boss.png"),QSize fixedsize= QSize(70, 70),
               int curhp=300,int speed=2,int hp=300,int mon=400,const QPixmap &iceenemy=QPixmap(":/image/iceboss.png"),const QPixmap&fireenemy=QPixmap(":/image/fireboss.png"));

    void summon();
    ~Boss();
    void targetDied();
    void checkInRange();
    void drawRange(QPainter *painter);
private slots:
    void shootWeapon();
};

#endif // BOSS_H
