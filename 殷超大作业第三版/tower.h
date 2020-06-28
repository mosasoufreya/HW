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
    Tower(QPoint pos,Scene *game,const QPixmap &pix= QPixmap(":/image/basictower-2.png"),int towertype=1,int dam=2,const QSize fixedsize = QSize(40, 45), int attackrange=100, int attackrate=500,int hp=50,const QPixmap &update= QPixmap(":/image/basicup.png"),const QPixmap &remove= QPixmap(":/image/remove.png"));
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
    bool inUpdateRange(const QPoint &pos) const;
    bool inRemoveRange(const QPoint &pos) const;
    void loseSight(Enemy *attacker);
    void getAttack(Enemy *attacker);
    void getDamage(int dam);
    void getRemoved();
    int getTowerType();
    void sethasUpdate();
    void loseTarget();
signals:

public slots:
    virtual void shootWeapon() = 0;
protected:
    QPixmap pixmap;
    int attackRange;
    int towerType;
    int damage;
    int attackRate;
    int Hp;
    int curhp;
    Scene*_game;
    Enemy* targetEnemy;
    QList<Enemy *>	attacker_list;
private:
    QPoint _pos;
    bool  _hasShowRange;
    QTimer* shootTimer;
    const QSize fixedSize;
    QPixmap _update;
    QPixmap _remove;
    qreal rotationSprite;
    bool _hasUpdate;
};

#endif // TOWER_H
