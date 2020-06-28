#ifndef BULLET_H
#define BULLET_H

#include <QPoint>

#include <QPixmap>
#include <QObject>
#include <QPainter>
#include"enemy.h"
#include<QSize>

class Enemy;
class Scene;
class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint curpoint READ getCurrentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos, QPoint targetPoint, int dam, Enemy *target,Scene*game,const QPixmap &pic, QSize fixedsize);
    virtual void drawer(QPainter *painter);
    virtual void move();
    void setCurrentPos(QPoint pos);
    QPoint getCurrentPos();

signals:


public slots:
   virtual void hitTarget()=0;
protected:
    QPoint  startPoint;
    QPoint  targetPoint;
    QPixmap pix;
    Enemy *targetEnemy;
    Scene* _game;
    int	   damage;
private:

    QPoint curpoint;
    QSize fixedSize;

};

#endif // BULLET_H
