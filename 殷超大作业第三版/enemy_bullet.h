#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include <QPoint>

#include <QPixmap>
#include <QObject>
#include <QPainter>
#include"tower.h"
#include<QSize>

class Tower;
class Scene;
class EnemyBullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint curpoint READ getCurrentPos WRITE setCurrentPos)
public:
    EnemyBullet(QPoint startPos, QPoint targetPoint, int dam, Tower *target,Scene*game,const QPixmap &pic= QPixmap(":/image/enemybullet.png"), QSize fixedsize= QSize(10, 10));
    void drawer(QPainter *painter);
    void move();
    void setCurrentPos(QPoint pos);
    QPoint getCurrentPos();

signals:


public slots:
   void hitTarget();
protected:
    QPoint startPoint;
    QPoint targetPoint;
    QPixmap pix;
    Tower *targetTower;
    Scene* _game;
    int	   damage;
private:

    QPoint curpoint;
    QSize fixedSize;

};

#endif // ENEMYBULLET_H
