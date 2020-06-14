#ifndef TOWER_H
#define TOWER_H
#include<QTimer>
#include <QObject>
#include <QPixmap>
#include <QPainter>
#include "enemy.h"
#include<QList>
#include<QSize>
class Enemy;
class Scene;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/IMG_0487-2.png"),int dam=2,const QSize fixedsize = QSize(40, 45), int attackrange=100, int attackrate=1000);
    virtual ~Tower();
    void drawer(QPainter *painter);
    void drawRange(QPainter *painter);
    void attack();
    void attackChoose(Enemy *enemy);
    void checkInRange();
    void lostSight();
    bool hasShowRange() const;
    void setHasShowRange(bool hasShowRange = true);
    bool distoCircle(QPoint p1, double r1, QPoint p2, double r2);
    QPoint getPos() const;
    void targetdied();
    virtual void upgrade() = 0;
signals:

public slots:
    virtual void shootWeapon() = 0;
protected:
    QPixmap pixmap;
    int attackRange;
    int damage;
    int attackRate;
    Scene*_game;
    Enemy* targetEnemy;
private:
    QPoint _pos;
    bool _hasShowRange;
    QTimer* shootTimer;
    const QSize fixedSize;

};

#endif // TOWER_H
