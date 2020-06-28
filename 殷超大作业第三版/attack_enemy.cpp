#include "attack_enemy.h"
#include"scene.h"
#include"enemy.h"
#include<cmath>
#include "tower.h"
#include <QPixmap>
#include <QPainter>
#include<QTimer>
#include"enemy.h"
#include<QList>
#include<cmath>
#include "scene.h"
#include"enemy_bullet.h"
AttackEnemy::AttackEnemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp,int mon,const QPixmap &iceenemy,const QPixmap&fireenemy)
    :Enemy(game,pixmap,fixedsize,curhp,speed,hp,mon,iceenemy,fireenemy),targetTower(NULL)
{enemyType=2;
    if(_game->getSceneNumber()==1){
    addWaypoint();
    }
    if(_game->getSceneNumber()==2){
        addWaypoint2();
    }
    curpoint = waypoint_list.back()->pos();
    waypoint = waypoint_list.back()->nextWayPoint();
    shootTimer = new QTimer(this);
    connect(shootTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

void AttackEnemy::summon(){
    _game->loadWave();

}

AttackEnemy::~AttackEnemy(){

}
void AttackEnemy::drawRange(QPainter *painter){
    if(!active)return;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::red);
    const QPoint newPos(85, 20);
    painter->translate(this->curpoint);
    painter->drawEllipse(newPos, 100, 100);
    painter->restore();
}
void AttackEnemy::attack()
{
    shootTimer->start(300);
}

void AttackEnemy::attackChoose(Tower *tower)
{
    targetTower = tower;
    attack();
    targetTower->getAttack(this);
}



void AttackEnemy::loseSight()
{
    targetTower->loseSight(this);
    if (targetTower)
        targetTower = NULL;

    shootTimer->stop();

}

void AttackEnemy::checkInRange(){
    if (targetTower)
        {
            QPoint targetpoint=targetTower->getPos()+QPoint(27,22);
            if (!distoCircle(curpoint+QPoint(87,17), 100, targetpoint, 1))
                loseSight();
        }
        else
        {
            QList<Tower *> towerList = _game->towerlist();
    foreach (Tower *tower, towerList)
    {
        if (distoCircle(curpoint+QPoint(87,17), 100, tower->getPos()+QPoint(27,22), 1))
        {
            attackChoose(tower);
            break;
        }
    }
  }
}

bool AttackEnemy::distoCircle(QPoint p1, double r1, QPoint p2, double r2)
{
    const double deltaX = p1.x() - p2.x();
    const double deltaY = p1.y() - p2.y();
    const double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if(distance < r1 + r2)
        return true;

    return false;
}

void AttackEnemy::shootWeapon(){
    QPoint startpoint=getCurrentPos()+QPoint(87,17);
    QPoint targetpoint=targetTower->getPos()+QPoint(27,22);
    EnemyBullet *bullet = new EnemyBullet(startpoint, targetpoint,2,targetTower, _game);

     bullet -> move();
    _game -> addEnemyBullet(bullet);
}
void AttackEnemy::targetDied(){
    if(targetTower)
            targetTower = NULL;

        shootTimer->stop();
}
