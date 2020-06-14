#ifndef BULLET_H
#define BULLET_H

#include <QPoint>

#include <QPixmap>
#include <QObject>
#include <QPainter>
#include"enemy.h"

class Enemy;
class Scene;
class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint _currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int dam, Enemy *target,Scene*game,const QPixmap &pic);
    virtual void drawer(QPainter *painter);
    virtual void move();
    void setCurrentPos(QPoint pos);
    QPoint getCurrentPos();

signals:


public slots:
   virtual void hit_target()=0;
protected:
    QPoint _startpoint;
    QPoint _targetpoint;
    QPixmap pix;
    Enemy *targetEnemy;
    Scene* _game;
    int	   damage;
private:

    QPoint curpoint;


};

#endif // BULLET_H
