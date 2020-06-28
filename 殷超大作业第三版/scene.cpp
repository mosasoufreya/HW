#include "scene.h"
#include "ui_scene.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTimer>
#include"mybutton.h"
#include"tower.h"
#include<QList>
#include"enemy.h"
#include"towerposition.h"
#include<QPixmap>
#include"bullet.h"
#include<QPoint>
#include <QDebug>
#include"basic_tower.h"
#include"basic_enemy.h"
#include"attack_enemy.h"
#include"ice_tower.h"
#include"sun_tower.h"
#include"boss.h"
#include<QSound>
Scene::Scene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scene),
    wave(0),homeHP(10),money(1500),win(false),lose(false),towerType(0),sceneNumber(0),error(false)
{
  setFixedSize(1200,600);
    ui->setupUi(this);

      if(sceneNumber==1){
      startPoint.setX(0);
      startPoint.setY(0);
      home.setX(700);
      home.setY(158);
      }
      if(sceneNumber==2){
          startPoint.setX(205);
          startPoint.setY(160);
          home.setX(820);
          home.setY(160);
      }
      dochoose=false;


      MyButton*back_bin=new MyButton(":/image/backbin.png");//返回按钮
      back_bin->setParent(this);
      back_bin->move(0,0);
      connect(back_bin,&MyButton::clicked,this,[=](){
          QSound *buttonplayer=new QSound("qrc:/bgm/button.wav");
          buttonplayer->play();
          back_bin->zoomdown();
          back_bin->zoomup();
          QTimer::singleShot(500,this,[=](){
          emit chooseBack();
              if(!scenePlayer->isFinished()){
                  scenePlayer->stop();
              }
              reset();
      });
     });





      QTimer*timer=new QTimer(this);
      connect(timer, SIGNAL(timeout()),this,SLOT(updateScreen()));
      timer->start(30);


}

Scene::~Scene()
{  for(auto &enemy: this->enemy_list)
    {
        enemy->getRemoved();
    }

    for(auto &bullet: this->bullet_list)
    {
        removeBullet(bullet);
    }

    for(auto &tower: this->tower_list)
    {
        removeTower(tower);
    }
    delete ui;

}
void Scene::paintEvent(QPaintEvent*){
   //画地图
    if(sceneNumber==1)
    {   scene=QPixmap(":/image/scene1.png");
    }
    if(sceneNumber==2){
        scene=QPixmap(":/image/scene2.png");
    }
   //画塔位、敌人、子弹、塔、特殊提示
    QPainter Painter(&scene);
    for(auto &towerPosition: this->towerpos_list)
    {       if(towerPosition.hasShow())
            towerPosition.drawer(&Painter);
    }
   for(auto &enemy: this->enemy_list)
   {
       enemy->drawer(&Painter);
       enemy->drawRange(&Painter);
    }
   for(auto &Tower: this->tower_list)
   {       Tower->drawer(&Painter);
       if(Tower->hasShowRange())
           Tower->drawRange(&Painter);
   }
   for(auto &bullet: this->bullet_list)
   {
       bullet->drawer(&Painter);   }
   for(auto &bullet: this->enemybullet_list)
   {       bullet->drawer(&Painter);
   }
   drawHP(&Painter);
   drawMoney(&Painter);
   drawWaves(&Painter);
   QPainter painter(this);
   painter.drawPixmap(0,0,this->width(),this->height(),scene);
   if(win){

       QPixmap win(":/image/win.png");
       painter.drawPixmap(0, 100, 1200, 600, win);
   }
   if(lose){

       QPixmap lose(":/image/lose.png");
       painter.drawPixmap(0, 100, 1200, 600, lose);
   }
   if(error){
       QPixmap error(":/image/lackmoney.png");
       painter.drawPixmap(500, 300, error.width()/3, error.height()/3, error);
   }
}


void Scene::updateScreen(){
    if(lose)return;
    for(auto &enemy: this->enemy_list){
        enemy->move();

    }    for(auto &tower: this->tower_list){
        tower->checkInRange();
    }
         update();
}
//设置塔可以放置的位置
void Scene::LoadTowerPos(){
    qDebug("loadtowerpos");
    if(sceneNumber==1){
    QPoint pos[] =
    {
        //first row
        QPoint(320, 158),
        QPoint(385, 158),
        QPoint(505, 158),
        QPoint(565, 158),
        QPoint(625, 158),

        //second row
        QPoint(320, 220),
        QPoint(385, 220),
        QPoint(505, 220),
        QPoint(565, 220),
        QPoint(625, 220),
        QPoint(750, 220),
        QPoint(810, 220),
        //third row
        QPoint(505, 282),
        QPoint(565, 282),
        QPoint(625, 282),
        //fourth row
        QPoint(385, 344),
        QPoint(445, 344),
        QPoint(505, 344),
        QPoint(565, 344),
        QPoint(625, 344),
        QPoint(690, 344),
        QPoint(750, 344),

    };
    int num = sizeof(pos) / sizeof(pos[0]);

    for(int i = 0; i < num; ++ i)
        this->towerpos_list.push_back(TowerPosition(pos[i]));
    }
    if(sceneNumber==2){
    QPoint pos[] =
    {
        //first row
        QPoint(205, 150),
        QPoint(565, 150),

        //second row
       QPoint(205, 212),
       QPoint(385, 212),
       QPoint(445, 212),
       QPoint(565, 212),
       QPoint(690, 212),
       QPoint(750, 212),
       QPoint(935, 212),

        //third row
       QPoint(445, 274),
       QPoint(565, 274),
       QPoint(690, 274),
        //fourth row
       QPoint(265, 336),
       QPoint(325, 336),
       QPoint(445, 336),
       QPoint(565, 336),
       QPoint(690, 336),
       QPoint(810, 336),
       QPoint(870, 336),
       //fifth row
       QPoint(445, 398),
       QPoint(690, 398),


    };
    int num = sizeof(pos) / sizeof(pos[0]);

    for(int i = 0; i < num; ++ i)
        this->towerpos_list.push_back(TowerPosition(pos[i]));
    }
}

//画towerposition

void Scene::mousePressEvent(QMouseEvent *event){
    QPoint pressPos = event->pos();
    for(auto &curPos: towerpos_list)  {
        if(curChoose && curChoose->inUpdateRange(pressPos))         //实现升级
               {   if((curChoose->getTowerType()==1&&money<80)||(curChoose->getTowerType()==2&&money<100)||(curChoose->getTowerType()==3&&money<150)){
                        QSound *errorSound=new QSound("qrc:/bgm/error.wav");
                        errorSound->play();
                        error=true;
                        QTimer::singleShot(1000,this,[=](){
                            error=false;
                        });
                        return;
                    }else{
                   QSound *updateSound=new QSound("qrc:/bgm/update.wav");
                   updateSound->play();
                   qDebug("test->10");
                   curChoose->upgrade();
                   curChoose->setHasShowRange(false);
                   curChoose = NULL;
                   break;
                    }
               }
               else if(curChoose && curChoose->inRemoveRange(pressPos))   //实现卖掉防御塔
               {
                   int returnedmoney;
                   if(curChoose->getTowerType()==1)returnedmoney=100;
                   if(curChoose->getTowerType()==2)returnedmoney=100;
                   if(curChoose->getTowerType()==3)returnedmoney=100;
                   returnMoney(returnedmoney);
                   removeTower(curChoose);
                   curChoose = NULL;
                   curtowerPos->sethasTower(false);
                   curtowerPos = NULL;
               }
        if(curPos.inRange(pressPos))
        {  qDebug("test->2");
            if(curPos.inRange(pressPos))
            {   qDebug("test->1");
                curChoose = NULL;
            }
            if(curPos.hasShow() && !curPos.hasTower())//建塔
            {

                if(towerType==1){
                    qDebug("888");
                    curPos.sethasTower();
                    Tower *tower = new BasicTower(curPos.getPos(),this);
                    this->tower_list.push_back(tower);
                    returnMoney(-BasicTower::getCost());

                }
                if(towerType==2){

                    curPos.sethasTower();
                    Tower *tower = new IceTower(curPos.getPos(),this);
                    this->tower_list.push_back(tower);
                    returnMoney(-IceTower::getCost());

                }
                if(towerType==3){

                    curPos.sethasTower();
                    Tower *tower = new SunTower(curPos.getPos(),this);
                    this->tower_list.push_back(tower);
                   returnMoney(-SunTower::getCost());

                }


            }

            else if(curPos.hasTower())//显示攻击范围
            {qDebug("test->4");
                bool break_flag = false;
                for(auto &curTower: tower_list)
                {
                    if(curTower->getPos() == curPos.getPos())
                    { qDebug("test->5");
                        break_flag = true;
                        if(!curTower->hasShowRange()) {
                            curTower->setHasShowRange();
                            curChoose = curTower;
                            curtowerPos = &curPos;
                        }
                        else {qDebug("test->6");
                           curTower->setHasShowRange(false);
                            if(curChoose)
                                curChoose = NULL;
                        }
                        break;
                    }
                }
                if(break_flag)
                    break;
           }
        }
        else
        {
            if(curChoose) {qDebug("test->7");
                curChoose->setHasShowRange(false);
                curChoose = NULL;
            }
        }
  }
    this->setCursor(Qt::ArrowCursor);
    for(auto &temp: this->towerpos_list)
        {
            temp.sethasShow(false);
        }
 update();

}

void Scene::gameStart(){
  loadWave();
}
//加载敌人
void Scene::loadWave(){
    if(!enemy_list.empty()){
            return;
        }
    qDebug("222");
    if (wave >= 3){
        if(!lose){
        scenePlayer->stop();
        QSound *winSound=new QSound("qrc:/bgm/win.wav");
        winSound->play();
        win=true;
    }
        return;
    }

    for(int i=0;i<100;++i){
        if(enemyData[wave][i]==1){
            Enemy*enemy=new BasicEnemy(this);
            enemy_list.push_back(enemy);
            QTimer::singleShot(5000+i*2000,enemy,SLOT(doActive()));
        }
        if(enemyData[wave][i]==2){
            Enemy*enemy=new AttackEnemy(this);
            enemy_list.push_back(enemy);
            QTimer::singleShot(5000+i*2000,enemy,SLOT(doActive()));
        }
        if(enemyData[wave][i]==3){
            Enemy*enemy=new Boss(this);
            enemy_list.push_back(enemy);
            QTimer::singleShot(5000+i*2000,enemy,SLOT(doActive()));
        }
        if(enemyData[wave][i]==0)break;
    }
    wave++;
    return;
}
void Scene::on_basicTower_clicked(){
    if(money<80){
        QSound *errorSound=new QSound("qrc:/bgm/error.wav");
        errorSound->play();
        error=true;
        QTimer::singleShot(1000,this,[=](){
            error=false;
        });
        return;
    }
    towerType=1;
    QCursor *myCursor = new QCursor(QPixmap(":/image/basictower.png"),-1,-1);
    this->setCursor(*myCursor);
    for(auto &temp: this->towerpos_list)
    {
        temp.sethasShow();

    }

    update();
}
QList<Enemy *> Scene::enemylist() const
{
    return enemy_list;
}
void Scene::getDamage(int dam){
   homeHP -= dam;
   QSound *damSound=new QSound("qrc:/bgm/carrot.wav");
   damSound->play();
   if(homeHP <= 0)
            gameOver();
}
void Scene::removeEnemy(Enemy *enemy){


       enemy->summon();

       enemy_list.removeOne(enemy);

       delete enemy;

       if (enemy_list.empty())
           {
              loadWave();
           }

}
void Scene::removeBullet(Bullet *bullet){
   if (bullet_list.indexOf(bullet) != -1)

        bullet_list.removeOne(bullet);
       delete bullet;
}
void Scene::addBullet(Bullet *bullet){

       bullet_list.push_back(bullet);
}
void Scene::addEnemyBullet(EnemyBullet *bullet){

       enemybullet_list.push_back(bullet);
}
void Scene::returnMoney(int mon){
    money=money+mon;
}
void Scene::gameOver()
{

    if (!lose)
    {   scenePlayer->stop();
        QSound *loseSound=new QSound("qrc:/bgm/lose.wav");
        loseSound->play();
        lose = true;

    }
}
void Scene::removeTower(Tower *tower)
{   tower->loseTarget();
    foreach(Enemy *enemy,enemy_list){
        enemy->lostSight(tower);
    }
    tower_list.removeOne(tower);
    delete tower;
}
void Scene::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    if(sceneNumber==1){
    painter->drawText(QRect(760, 133, 20, 25), QString("%70").arg(homeHP));
    }
    if(sceneNumber==2){
    painter->drawText(QRect(943, 133, 20, 25), QString("%70").arg(homeHP));
    }
}

void Scene::drawMoney(QPainter *painter)
{
    QFont font("宋体",15,QFont::Bold,false);
    painter->setFont(font);
    painter->setPen(QPen(Qt::white));
    painter->drawText(QRect(300, 20, 80, 50), QString("%70").arg(money));
}
void Scene::drawWaves(QPainter *painter)
{
    QFont font("宋体",15,QFont::Bold,false);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(QRect(540, 20, 80, 50), QString("%70").arg(wave));
    painter->drawText(QRect(600, 20, 80, 50), QString("%70").arg(3));
}

void Scene::on_iceTower_clicked()
{   if(money<100){
        QSound *errorSound=new QSound("qrc:/bgm/error.wav");
        errorSound->play();
        error=true;
        QTimer::singleShot(1000,this,[=](){
            error=false;
        });
        return;
    }
    towerType=2;
    QCursor *myCursor = new QCursor(QPixmap(":/image/icetower.png"),-1,-1);
    this->setCursor(*myCursor);
    for(auto &temp: this->towerpos_list)
    {
        temp.sethasShow();

    }

    update();
}

void Scene::on_sunTower_clicked()
{   if(money<150){
        QSound *errorSound=new QSound("qrc:/bgm/error.wav");
        errorSound->play();
        error=true;
        QTimer::singleShot(1000,this,[=](){
            error=false;
        });
        return;
    }
    towerType=3;
    QCursor *myCursor = new QCursor(QPixmap(":/image/suntower.png"),-1,-1);
    this->setCursor(*myCursor);
    for(auto &temp: this->towerpos_list)
    {
        temp.sethasShow();

    }

    update();
}
void Scene::setScene(int scenenumber){
    sceneNumber=scenenumber;
}

int Scene::getSceneNumber(){
    return sceneNumber;
}
QList<Tower *> Scene::towerlist() const
{
    return tower_list;
}
void Scene::removeEnemyBullet(EnemyBullet *bullet){
   if (enemybullet_list.indexOf(bullet) != -1)

        enemybullet_list.removeOne(bullet);
       delete bullet;
}
void Scene::removeDiedTower(Tower *tower){
    for(auto &curPos: towerpos_list)  {
        if(curPos.getPos()==tower->getPos()){
            TowerPosition *curpos=&curPos;
            curpos->sethasTower(false);
        }
    }
    tower_list.removeOne(tower);
    delete tower;
}
//存放敌人数据
void Scene::loadEnemy(){
    if(sceneNumber==1){
        int edata[3][100]={
            {1,1,1,1,1},
            {1,2,1,2,1,2},
            {1,2,2,1,2,2,1,2,2}
        };
        for(int i=0;i<3;i++){
            for(int j=0;j<100;j++){
                enemyData[i][j]=edata[i][j];
            }
        }
    }
    if(sceneNumber==2){
        int edata[3][100]={
            {1,1,2,2,3},
            {1,1,1,2,2,2,3,3,3,3},
            {2,2,2,2,2,2,3,3,3,3,3,3}
        };
        for(int i=0;i<3;i++){
            for(int j=0;j<100;j++){
                enemyData[i][j]=edata[i][j];
            }
        }
    }

}
void Scene::setSound(){
    if(sceneNumber==1){
        scenePlayer=new QSound("qrc:/bgm/scene1.wav");
        scenePlayer->setLoops(-1);
        scenePlayer->play();
    }
    if(sceneNumber==2){
        scenePlayer=new QSound("qrc:/bgm/scene2.wav");
        scenePlayer->setLoops(-1);
        scenePlayer->play();
    }
}
//返回时重启
void Scene::reset(){
    for(auto &enemy: this->enemy_list)
        {
        enemy_list.removeOne(enemy);

        delete enemy;

        }

        for(auto &bullet: this->bullet_list)
        {
            removeBullet(bullet);
        }
        for(auto &bullet: this->enemybullet_list)
        {
            removeEnemyBullet(bullet);
        }
        for(auto &tower: this->tower_list)
        {
            removeTower(tower);
        }
       wave=0;
       money=1500;
       homeHP=10;
       win=false;
       lose=false;
       for(int i=0;i<3;i++){
           for(int j=0;j<100;j++){
               enemyData[i][j]=0;
           }
       }
    towerpos_list.clear();
    curChoose=NULL;
    curtowerPos-NULL;
}
