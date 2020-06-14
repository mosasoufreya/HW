#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QMainWindow>
#include"tower.h"
#include<QList>
#include"enemy.h"
#include<QTimer>
#include<towerposition.h>
#include"bullet.h"
#include<QPoint>
#include"basic_enemy.h"
#include"basic_tower.h"
class Tower;
class Enemy;
class Waypoint;

namespace Ui {
class Scene; 
}

class Scene : public QMainWindow
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();
    void paintEvent(QPaintEvent*);
    void LoadTowerPos();

    void mousePressEvent(QMouseEvent *event);
    bool loadWave();
    void removeBullet(Bullet*bullet);
    void removeEnemy(Enemy *enemy);
    void removeTower(Tower *tower);
    QList<Enemy *> enemylist() const;
    void getDamage(int dam=1);
    void addBullet(Bullet*bullet);
    void returnmoney(int mon);

signals:
        void chooseBack();
public slots:
    void updateScreen();
    void on_tower_clicked();
    void gamestart();

private:
    void gameOver();
    void drawHP(QPainter *painter);
    void drawMoney(QPainter *painter);
    void drawWaves(QPainter *painter);


    Ui::Scene *ui;
    QList<Tower*> tower_list;
        QList<Enemy*>enemy_list;
        QList<TowerPosition>towerpos_list;
        QList<Bullet *>    bullet_list;
        QList<WayPoint*> waypoint_list;
        Tower * curChoose = NULL;
        TowerPosition *curtowerPos = NULL;
        int wave;
        QPoint startpoint;
        QPoint home;
        int homeHP;
        bool dochoose;
        int money;
        bool win;
        bool lose;
};

#endif // SCENE_H
