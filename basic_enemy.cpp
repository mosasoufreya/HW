#include "basic_enemy.h"
#include"enemy.h"
#include"scene.h"
BasicEnemy::BasicEnemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp)
 :Enemy(game,pixmap,fixedsize,curhp,speed,hp)
{
    addWaypoint();
    curpoint = waypoint_list.back()->pos();
    waypoint = waypoint_list.back()->nextWayPoint();
}
void BasicEnemy::summon(){
   _game->loadWave();
}

BasicEnemy::~BasicEnemy(){

}
