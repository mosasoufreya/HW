#include "basic_enemy.h"
#include"enemy.h"
#include"scene.h"
BasicEnemy::BasicEnemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp,int mon,const QPixmap &iceenemy,const QPixmap&fireenemy)
 :Enemy(game,pixmap,fixedsize,curhp,speed,hp,mon,iceenemy,fireenemy)
{enemyType=1;
    if(_game->getSceneNumber()==1){
    addWaypoint();
   }
    if(_game->getSceneNumber()==2){
        addWaypoint2();
    }
    curpoint = waypoint_list.back()->pos();
    waypoint = waypoint_list.back()->nextWayPoint();
}
void BasicEnemy::summon(){
   _game->loadWave();
}

BasicEnemy::~BasicEnemy(){

}
void BasicEnemy::drawRange(QPainter *painter){

}
void BasicEnemy::targetDied(){

}
void BasicEnemy::checkInRange(){

}
void BasicEnemy::shootWeapon(){

}
