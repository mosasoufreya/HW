#include "boss.h"
#include"enemy.h"
#include"scene.h"
Boss::Boss(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp,int mon,const QPixmap &iceenemy,const QPixmap&fireenemy)
 :Enemy(game,pixmap,fixedsize,curhp,speed,hp,mon,iceenemy,fireenemy)
{enemyType=3;
    if(_game->getSceneNumber()==1){
    addWaypoint();
   }
    if(_game->getSceneNumber()==2){
        addWaypoint2();
    }
    curpoint = waypoint_list.back()->pos();
    waypoint = waypoint_list.back()->nextWayPoint();
}
void Boss::summon(){
   _game->loadWave();
}

Boss::~Boss(){

}
void Boss::drawRange(QPainter *painter){

}
void Boss::targetDied(){

}
void Boss::checkInRange(){

}
void Boss::shootWeapon(){

}
