#ifndef ATTACKENEMY_H
#define ATTACKENEMY_H
#include"enemy.h"
class Scene;
class AttackEnemy:public Enemy
{
public:
    AttackEnemy(Scene*game, const QPixmap &pixmap= QPixmap(":/image/IMG_0455-2.png"),QSize fixedsize= QSize(73, 60),
                int curhp=100,int speed=1,int hp=100);
    void summon();
    ~AttackEnemy();
};

#endif // ATTACKENEMY_H
