#ifndef BASICENEMY_H
#define BASICENEMY_H
#include "enemy.h"
#include "mainwindow.h"
class Scene;
class BasicEnemy:public Enemy
{
public:
    BasicEnemy(Scene*game, const QPixmap &pixmap= QPixmap(":/image/IMG_0455-2.png"),QSize fixedsize= QSize(50, 50),
               int curhp=100,int speed=1,int hp=100);

    void summon();
    ~BasicEnemy();
};

#endif // BASICENEMY_H
