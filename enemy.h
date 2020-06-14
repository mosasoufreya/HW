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
    Enemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp);
    virtual ~Enemy();
    void drawer(QPainter *painter);
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
    Scene*_game;
    const QSize fixedSize;
signals:

public slots:
    void doActive();



};

#endif // ENEMY_H
