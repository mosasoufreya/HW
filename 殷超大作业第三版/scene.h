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
#include"enemy_bullet.h"
#include<QSound>
class Tower;
class Enemy;
class Waypoint;
class Bullet;
class EnemyBullet;

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
    void loadWave();
    void removeBullet(Bullet*bullet);
    void removeEnemy(Enemy *enemy);
    void removeTower(Tower *tower);
    QList<Enemy *> enemylist() const;
    QList<Tower *> towerlist() const;
    void getDamage(int dam=1);
    void addBullet(Bullet*bullet);
    void addEnemyBullet(EnemyBullet*bullet);
    void returnMoney(int mon);
    void setScene(int scenenumber);
    int getSceneNumber();
    void removeEnemyBullet(EnemyBullet*bullet);
    void removeDiedTower(Tower *tower);
    void loadEnemy();
    void setSound();
    void reset();
signals:
        void chooseBack();
public slots:
    void updateScreen();
    void on_basicTower_clicked();
    void gameStart();
    void on_iceTower_clicked();
    void on_sunTower_clicked();

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
        QList<EnemyBullet *>    enemybullet_list;
        QList<WayPoint*> waypoint_list;
        Tower * curChoose = NULL;
        TowerPosition *curtowerPos = NULL;
        int wave;
        QPoint startPoint;
        QPoint home;
        int homeHP;
        bool dochoose;
        int money;
        bool win;
        bool lose;
        int towerType;
        int sceneNumber;
        QPixmap scene;
        int enemyData[3][100];
        QSound *scenePlayer;
        bool error;
};

#endif // SCENE_H
