#include "attack_enemy.h"
#include"scene.h"

AttackEnemy::AttackEnemy(Scene*game, const QPixmap &pixmap,QSize fixedsize,int curhp,int speed,int hp):Enemy(game,pixmap,fixedsize,curhp,speed,hp)
{
    curpoint = waypoint_list.back()->pos();
    waypoint = waypoint_list.back()->nextWayPoint();
}

void AttackEnemy::summon(){
    _game->loadWave();
}

AttackEnemy::~AttackEnemy(){

}
