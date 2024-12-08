#include "include/entities/enemy/enemy.h"
#include "include/entities/bullet.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#define HEALTH 100

Enemy::Enemy() {
    defaultPixmap = QPixmap(":/images/ghost/fGhostR.png").scaled(170, 170);

    defaultReversePixmap = QPixmap(":/images/ghost/fGhostL.png").scaled(170, 170);

    setPixmap(defaultPixmap);
    attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, &Enemy::performAttack);
    healthPoint = HEALTH;
    direction = Direction::LEFT;
    stage = 1;
    connect(this, &Enemy::secondStage, this, &Enemy::changeToSecondStage);

    xMin = 0;
    xMax = 900;
    yMin = 400;
    yMax = 0;
}

Enemy::~Enemy() {
    attackTimer->stop();
    delete attackTimer;
    disconnect(this, &Enemy::secondStage, this, &Enemy::changeToSecondStage);
}

void Enemy::startAttacking() { attackTimer->start(800); }
void Enemy::stopAttacking() { attackTimer->stop(); }

void Enemy::performAttack() {
    int randomAttack = QRandomGenerator::global()->bounded(3);
    if (randomAttack == 1)
        shootFireball();
    else if (randomAttack == 2)
        shootLaser();
    else
        shootSpreadShot();
}

void Enemy::shootFireball() {
    Bullet *fireball = new Bullet(x(), y(), 100, 100, 5, 0, 20, direction, this, QPixmap(":/images/bullet/fire(1).png"), this);
    scene()->addItem(fireball);
}

void Enemy::shootLaser() {
    Bullet *laser = new Bullet(x(), y(), 50, 25, 8, 0, 10, direction, this, QPixmap(":/images/bullet/fire(1).png"), this);
    scene()->addItem(laser);
}

void Enemy::shootSpreadShot() {
    for (int angle = -1; angle <= 1; ++angle) {
        Bullet *spreadBullet = new Bullet(x(), y(), 50, 50, 5, angle * 2, 10, direction, this, QPixmap(":/images/bullet/skullR.png"), this);
        scene()->addItem(spreadBullet);
    }
}

void Enemy::takeDamage(int damage) {
    healthPoint -= damage;
    if (stage == 1 && healthPoint <= HEALTH / 2){
        stage = 2;
        emit secondStage();
    }
    if (healthPoint <= 0) {
        emit enemyDead();
        // scene()->removeItem(this);
        // this->deleteLater();
    }
}

void Enemy::advance(int phase) {
    if (!phase) return;
    static int verticalDirection = -1;

    int random = QRandomGenerator::global()->bounded(1000);
    if (random < 5) {
        if (pos().x() == xMin) {
            setPixmap(defaultPixmap);
            setPos(xMax, pos().y());
            direction = Direction::LEFT;
        } else {
            setPixmap(defaultReversePixmap);
            setPos(xMin, pos().y());
            direction = Direction::RIGHT;            }
            return;
    }

    int currentY = pos().y();
    int step = 2;

    if (random % 379 == 0){
        qDebug() << "changed";
        verticalDirection *= -1;
    }


    if (currentY >= yMin) {
        verticalDirection = -1;

    } else if (currentY <= yMax) {
        verticalDirection = 1;
    }

    setPos(pos().x(), currentY + (step * verticalDirection));
}


void Enemy::changeToSecondStage(){
    defaultPixmap = QPixmap(":/images/ghost/sGhostR.png");
    defaultReversePixmap = QPixmap(":/images/ghost/sGhostL.png");
    attackTimer->start(600);
    if (x() == xMin){
        setPixmap(defaultReversePixmap);
    } else{
        setPixmap(defaultPixmap);
    }
}

EntityType Enemy::getEntityType() const{
    return EntityType::Enemy;
}
