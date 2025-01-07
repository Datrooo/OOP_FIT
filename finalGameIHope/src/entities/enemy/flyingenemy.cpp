#include "include/entities/enemy/flyingenemy.h"
#include "include/entities/bullet.h"
#include <QGraphicsScene>
#include <cmath>
#include "include/entities/entitytype.h"
#include "include/entities/player/player.h"

FlyingEnemy::FlyingEnemy() {
    healthPoint = 100;
    xSpeed = 3.0;
    amplitude = 50.0;
    frequency = 0.05;
    currentTime = 0.0;
    currentFrameIndex = 0;
    direction = Direction::LEFT;

    animationFrames = {
        QPixmap(":/images/mouse/firstframe.png"),
        QPixmap(":/images/mouse/secondframe.png"),
        QPixmap(":/images/mouse/thirdframe.png"),
        QPixmap(":/images/mouse/fourthframe.png")
    };

    setPixmap(animationFrames[currentFrameIndex]);

    attackTimer = new QTimer(this);
    connect(attackTimer, &QTimer::timeout, this, &FlyingEnemy::dropBomb);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &FlyingEnemy::updateAnimationFrame);
    animationTimer->start(100);
}

FlyingEnemy::~FlyingEnemy() {
    attackTimer->stop();
    animationTimer->stop();
    delete attackTimer;
    delete animationTimer;
    animationFrames.clear();
}

void FlyingEnemy::startAttacking() {
    attackTimer->start(1000);
}

void FlyingEnemy::stopAttacking() {
    attackTimer->stop();
}

void FlyingEnemy::advance(int phase) {
    if (!phase) return;
    updatePosition();
    checkCollisionsWithPlayer();
}

void FlyingEnemy::updatePosition() {
    currentTime += frequency;
    setPos(x() - xSpeed, 300 + amplitude * std::sin(currentTime));
    if (x() < 0){
        direction = Direction::RIGHT;
        xSpeed *= -1;
    } else if (x() > scene()->width() - 40){
        direction = Direction::LEFT;
        xSpeed *= -1;
    }

}

void FlyingEnemy::updateAnimationFrame() {
    if (direction == Direction::LEFT){
        setPixmap(animationFrames[currentFrameIndex]);
    } else{
        QTransform transform;
        transform.scale(-1.0, 1);
        setPixmap(animationFrames[currentFrameIndex].transformed(transform));
    }
    currentFrameIndex = (currentFrameIndex + 1) % animationFrames.size();
}

void FlyingEnemy::dropBomb() {
    Bullet *bomb = new Bullet(x(), y(), 30, 30, 0, 5, 5, Direction::NONE, this, QPixmap(":/images/mouse/bomb.png"), this);
    scene()->addItem(bomb);
}

void FlyingEnemy::takeDamage(int damage) {
    healthPoint -= damage;
    if (healthPoint <= 0) {
        emit enemyDead();
    }
}


EntityType FlyingEnemy::getEntityType() const{
    return EntityType::Enemy;
}

void FlyingEnemy::checkCollisionsWithPlayer(){
    QList<QGraphicsItem *> collidingList = collidingItems();
    for (QGraphicsItem* item : collidingList){
        Player *player = dynamic_cast<Player*>(item);
        if (player){
            emit takeDamagePlayer(1);
        }
    }
}
