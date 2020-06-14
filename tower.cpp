#include "tower.h"
#include <QPixmap>
#include <QPainter>
#include<QTimer>
#include"enemy.h"
#include<QList>
#include<cmath>
#include "scene.h"

Tower::Tower(QPoint pos,Scene *game,const QPixmap &pix,int dam,const QSize fixedsize, int attackrange, int attackrate)
    : QObject(0),pixmap(pix),attackRange(attackrange),
      damage(dam),attackRate(attackrate),_game(game), targetEnemy(NULL),_pos(pos),_hasShowRange(false),fixedSize(fixedsize){
   shootTimer = new QTimer(this);
   connect(shootTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}
Tower::~Tower()
{
    delete shootTimer;
    shootTimer = NULL;
}
void Tower::drawer(QPainter *painter){
     painter->save();
    const QPoint newPos(15, 5);
    painter->translate(this->_pos);
    painter->drawPixmap(newPos.x(), newPos.y() , fixedSize.width(), fixedSize.height(),  this->pixmap);

    painter->restore();
}
void Tower:: drawRange(QPainter *painter){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::white);
    const QPoint newPos(30, 20);
    painter->translate(this->_pos);
    painter->drawEllipse(newPos, this->attackRange, this->attackRange);
    painter->restore();
}

void Tower::attack()
{
    shootTimer->start(500);
}

void Tower::attackChoose(Enemy *enemy)
{
    targetEnemy = enemy;
    attack();
    targetEnemy->getAttack(this);
}

void Tower::checkInRange(){
    if (targetEnemy)
        {
            if (!distoCircle(_pos, attackRange, targetEnemy->getCurrentPos(), 1))
                lostSight();
        }
        else
        {
            QList<Enemy *> enemyList = _game->enemylist();
    foreach (Enemy *enemy, enemyList)
    {
        if (distoCircle(_pos, attackRange, enemy->getCurrentPos(), 1))
        {
            attackChoose(enemy);
            break;
        }
    }
  }
}

void Tower::lostSight()
{
    targetEnemy->lostSight(this);
    if (targetEnemy)
        targetEnemy = NULL;

    shootTimer->stop();

}



bool Tower::distoCircle(QPoint p1, double r1, QPoint p2, double r2)
{
    const double deltaX = p1.x() - p2.x();
    const double deltaY = p1.y() - p2.y();
    const double distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if(distance < r1 + r2)
        return true;

    return false;
}


bool Tower::hasShowRange() const
{
    return this->_hasShowRange;
}


void Tower::setHasShowRange(bool hasShowRange)
{
    this->_hasShowRange = hasShowRange;
}
QPoint Tower::getPos() const{
    return _pos;
}
void Tower::targetdied(){
    if(targetEnemy)
            targetEnemy = NULL;

        shootTimer->stop();
}
