#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include "tower.h"
#include"waypoint.h"
class Tower;
class WayPoint;
class Scene;
class Enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    Enemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp,int mon,const QPixmap &iceenemy,const QPixmap&fireenemy);
    virtual ~Enemy();
    void drawer(QPainter *painter);
    virtual void drawRange(QPainter *painter)=0;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint getCurrentPos();
    void lostSight(Tower *attacker);
    void getAttack(Tower *attacker);
    bool distoCircle(QPoint p1, double r1, QPoint p2, double r2);
    void getDamage(int dam);
    void getRemoved();
    void addWaypoint();
    virtual void summon() = 0;
    void slowDown();
    void HasFire();
    void addWaypoint2();
    virtual void targetDied()=0;
    virtual void checkInRange()=0;
    bool getActive();
protected:
    QPoint curpoint;
    QPixmap pix;
    QList<Tower *>	attacker_list;
    bool active;
    WayPoint *waypoint;
    QList<WayPoint *> waypoint_list;
    int HP;
    int curHP;
    int Speed;
    int damage;
    Scene* _game;
    const QSize fixedSize;
    int money;
    bool hasSlowDown;
    QTimer* slowTime;
    QPixmap iceEnemy;
    bool hasFired;
    QTimer*fireTime;
    QPixmap fireEnemy;
    int enemyType;

signals:

public slots:
    void doActive();
    void normalSpeed();
    void stopFire();
    virtual void shootWeapon() = 0;

};

#endif // ENEMY_H
