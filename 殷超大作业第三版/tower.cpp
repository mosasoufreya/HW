#include "tower.h"
#include <QPixmap>
#include <QPainter>
#include<QTimer>
#include"enemy.h"
#include<QList>
#include<cmath>
#include "scene.h"
#include <QVector2D>
#include <QtMath>

Tower::Tower(QPoint pos,Scene *game,const QPixmap &pix,int towertype,int dam,const QSize fixedsize, int attackrange, int attackrate,int hp,const QPixmap &update,const QPixmap &remove)
    : QObject(0),pixmap(pix),attackRange(attackrange),
      towerType(towertype),damage(dam),attackRate(attackrate),Hp(hp),curhp(hp),_game(game), targetEnemy(NULL),_pos(pos),_hasShowRange(false),fixedSize(fixedsize),_update(update),_remove(remove){
   shootTimer = new QTimer(this);
   connect(shootTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
   rotationSprite=0.0;
   _hasUpdate=false;
}
Tower::~Tower()
{
    delete shootTimer;
    shootTimer = NULL;
}
void Tower::drawer(QPainter *painter){
     painter->save();
     QPoint lifePoint = _pos + QPoint(19, -10);

     painter->setPen(Qt::NoPen);
     painter->setBrush(Qt::white);
     QRect lifePointRect(lifePoint, QSize(10, 3));
     painter->drawRect(lifePointRect);

     painter->setBrush(Qt::green);
     QRect healthBarRect(lifePoint, QSize((double)curhp / Hp * 30, 3));
     painter->drawRect(healthBarRect);
    const QPoint newPos(15, 5);
    painter->translate(this->_pos);
    if(towerType==1){
        painter->translate(30,25);
        painter->rotate(rotationSprite+180);
        painter->translate(-30,-25);
    }
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
    QPoint updatePos(13,-35);
    QPoint removePos(13,50);
    if(!_hasUpdate)painter->drawPixmap(updatePos.x(), updatePos.y(), 40, 40, _update);
    painter->drawPixmap(removePos.x(), removePos.y(), 40, 40, _remove);
    painter->restore();
}

void Tower::attack()
{
    shootTimer->start(attackRate);
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
            if(towerType==1){
                QVector2D normalized(targetEnemy->getCurrentPos()+QPoint(60,-5) -getPos());
                            normalized.normalize();
                             rotationSprite= qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;
            }
            QPoint targetpoint=targetEnemy->getCurrentPos()+QPoint(60,-5);
            if (!distoCircle(_pos, attackRange, targetpoint, 1)&&targetEnemy->getActive()==true)
                lostSight();
        }
        else
        {
            QList<Enemy *> enemyList = _game->enemylist();
    foreach (Enemy *enemy, enemyList)
    {
        if (distoCircle(_pos, attackRange, enemy->getCurrentPos()+QPoint(60,-5), 1)&&enemy->getActive())
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
bool Tower::inUpdateRange(const QPoint &pos) const
{
    bool inX = (_pos.x() + 13 < pos.x()) && (pos.x() < _pos.x() +43);
    bool inY = (_pos.y() -35 < pos.y()) && (pos.y() < _pos.y()+5);
    return inX && inY;
}

bool Tower::inRemoveRange(const QPoint &pos) const
{
    bool inX = (_pos.x() +13 < pos.x()) && (pos.x() < _pos.x() +43);
    bool inY = (_pos.y() +50 < pos.y()) && (pos.y() < _pos.y()+90);
    return inX && inY;
}

void Tower::loseSight(Enemy *attacker)
{
    attacker_list.removeOne(attacker);
}

void Tower::getAttack(Enemy *attacker)
{
    attacker_list.push_back(attacker);
}
void Tower::getDamage(int dam)
{
     curhp=curhp-dam;
      if (curhp <= 0)
          {
              getRemoved();
          }
}

void Tower::getRemoved()
{
   if(attacker_list.empty())
        return;
  for(auto &attacker: attacker_list)
        attacker->targetDied();
  QList<Enemy *> enemyList = _game->enemylist();
foreach (Enemy *enemy, enemyList)
{
 enemy->lostSight(this);
}
    _game->removeDiedTower(this);
}
int Tower::getTowerType(){
    return towerType;
}
void Tower::sethasUpdate(){
    _hasUpdate=true;
}
void Tower::loseTarget(){
    if(attacker_list.empty())
         return;
   for(auto &attacker: attacker_list)
         attacker->targetDied();
}

