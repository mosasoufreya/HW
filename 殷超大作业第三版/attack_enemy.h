#ifndef ATTACKENEMY_H
#define ATTACKENEMY_H
#include"enemy.h"
#include"scene.h"
#include"enemy_bullet.h"
#include"tower.h"
#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
class Scene;
class EnemyBullet;
class  Tower;
class AttackEnemy:public Enemy
{
public:
    AttackEnemy(Scene*game, const QPixmap &pixmap= QPixmap(":/image/attackenemy.png"),QSize fixedsize= QSize(50, 50),
                int curhp=150,int speed=2,int hp=150,int mon=300,const QPixmap &iceenemy=QPixmap(":/image/iceattackenemy.png"),const QPixmap&fireenemy=QPixmap(":/image/fireattackenemy.png"));
    void summon();
    ~AttackEnemy();
    void drawRange(QPainter *painter);
    void attack();
    void attackChoose(Tower *tower);
    void checkInRange();
    void loseSight();
    bool distoCircle(QPoint p1, double r1, QPoint p2, double r2);
    void targetDied();
protected:
    Tower *targetTower;
private slots:
    void shootWeapon();


private:
    QTimer* shootTimer;
};

#endif // ATTACKENEMY_H
