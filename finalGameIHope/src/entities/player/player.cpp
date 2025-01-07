#include "include/entities/player/player.h"
#include "include/entities/player/idlestate.h"
#include "include/interface/platform.h"
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "include/entities/bullet.h"
#include <QTimer>
#include "include/entities/player/jumpingstate.h"



Player::Player() : jumpSpeed(-15), gravity(0.4) {

    setPos(100, 300);
    setFlag(QGraphicsItem::ItemIsMovable);

    direction = Direction::RIGHT;
    healthPoint = MAX_HEALTH;
    horizontalSpeed = 0;
    onPlat = false;


    currentFireMode = ChargingMode;
    bul = QPixmap(":/new/prefix1/redFireRight.png");
    chargeTimer = new QTimer();
    charging = false;
    spammingTimer = new QTimer(this);
    canShoot = true;

    setTransformationMode(Qt::SmoothTransformation);


    animationFrames = {
        QPixmap(":/images/player/assasin/idleAs.png"),
        QPixmap(":/images/player/assasin/move.png"),
        QPixmap(":/images/player/assasin/jump.png"),
        QPixmap(":/images/player/assasin/idleAsL.png"),
        QPixmap(":/images/player/assasin/moveL.png"),
        QPixmap(":/images/player/assasin/jumpL.png")
    };
    state = new IdleState(this);

    frameChangers[idleFrame] = [this]() { setPixmap(animationFrames[idleFrame]); };
    frameChangers[idleLFrame] = [this]() { setPixmap(animationFrames[idleLFrame]); };
    frameChangers[movingFrame] = [this]() { setPixmap(animationFrames[movingFrame]); };
    frameChangers[movingLFrame] = [this]() { setPixmap(animationFrames[movingLFrame]); };
    frameChangers[jumpingFrame] = [this]() { setPixmap(animationFrames[jumpingFrame]); };
    frameChangers[jumpingLFrame] = [this]() { setPixmap(animationFrames[jumpingLFrame]); };

}


Player::~Player() {
    chargeTimer->stop();
    spammingTimer->stop();
    delete chargeTimer;
    delete spammingTimer;
    delete state;
    animationFrames.clear();
}

void Player::setState(PlayerState* newState) {
    if (state) {
        delete state;
    }
    state = newState;
}


QList<QGraphicsItem *> Player::collidingItemsWithToleance(QGraphicsItem *parent, qreal tolerance) {
    QList<QGraphicsItem *> collidingList;

    QList<QGraphicsItem *> sceneItems = parent->scene()->items();
    QRectF parentSceneRect = parent->mapToScene(parent->boundingRect()).boundingRect();

    for (QGraphicsItem* item : sceneItems) {
        if (item == parent) {
            continue;
        }

        QRectF itemSceneRect = item->mapToScene(item->boundingRect()).boundingRect();

        qreal yDiff = qAbs(parentSceneRect.bottom() - itemSceneRect.top());

        if (yDiff <= tolerance && parentSceneRect.intersects(itemSceneRect)) {
            collidingList.append(item);
        }
    }
    return collidingList;
}

void Player::onCollisionWithPlatform(){
    onPlat = false;
    QList<QGraphicsItem*> collidingItems = collidingItemsWithToleance(this, 15);
    for (QGraphicsItem* item : collidingItems) {
        Platform* platform = dynamic_cast<Platform*>(item);
        if (platform) {
            if (y() + boundingRect().height() >= platform->sceneBoundingRect().y() - 1 &&
                y() <= platform->sceneBoundingRect().y() && jumpSpeed >= 0) {
                setPos(x(), platform->sceneBoundingRect().y() - boundingRect().height());
                jumpSpeed = 0;
                onPlat = true;
                break;
            }
        }
    }
}

void Player::advance(int phase) {

    if (!phase) {
        return;
    }

    if (jumpSpeed <= 10) {
        jumpSpeed += gravity;
    }

    if (x() < 0) {
        setPos(0, y() + jumpSpeed);
    } else if (x() > 1037) {
        setPos(1037, y() + jumpSpeed);
    } else {
        setPos(x() + horizontalSpeed, y() + jumpSpeed);
    }


    emit posChanged(x(), y());

    onCollisionWithPlatform();

    state->update(this);
}

Direction Player::getDirection() {
    return direction;
}

void Player::takeDamage(int damage){
    healthPoint -= damage;
    qDebug() << "health" << healthPoint;
    emit callUpdateHealthBar(healthPoint);
    if (healthPoint <= 0) {
        healthPoint = 0;
        emit playerDead();
    }
}



void Player::shoot() {
    if (canShoot) {
        Bullet* bullet = new Bullet(x(), y(), 30, 15, 5, 0, 10, direction, this, QPixmap(":/images/bullet/redFireRight.png"), this);

        if (currentFireMode == ChargingMode) {
            bullet->setPower(currentPower);
        } else if (currentFireMode == SpammingMode) {
            bullet->setPower(10);
        }
        scene()->addItem(bullet);

        if (currentFireMode == ChargingMode) {
            currentPower = 0;
            emit callToUpdateCharge(currentPower);
        }

        canShoot = false;
        QTimer::singleShot(500, this, [this]() {
            canShoot = true;
        });
    }
}

void Player::updateCharge() {
    if (currentPower < MAX_POWER) {
        currentPower += 5;
        emit callToUpdateCharge(currentPower);
    } else{
        chargeTimer->stop();
    }
}

void Player::startSpamming() {
    if (canShoot) {
        shoot();
    }
}

void Player::startShooting() {
    if (currentFireMode == ChargingMode && !charging){
        charging = true;
        chargeTimer->start(50);
    } else if (currentFireMode == SpammingMode){
        if (!spammingTimer->isActive()) {
            spammingTimer->start(50);
        }
    }
}

void Player::shootBullet() {
    if (currentFireMode == SpammingMode) {
        spammingTimer->stop();
    } else if (currentFireMode == ChargingMode && charging) {
        charging = false;
        chargeTimer->stop();
        shoot();
    }
}

void Player::moveLeft() {
    direction = Direction::LEFT;
    horizontalSpeed = -5;
}

void Player::moveRight() {
    direction = Direction::RIGHT;
    horizontalSpeed = 5;
}

void Player::jump() {
    if (onPlat) {
        setState(new JumpingState(this));
        jumpSpeed = -10;
    }
}

void Player::goDown(){
    if (onPlat && y() < 500) {
        setState(new JumpingState(this));
        jumpSpeed = 0;
        setPos(x(), y() + 20);
    }
}

void Player::changeShootingMode() {
    shootBullet();
    if (currentFireMode == ChargingMode){
        currentFireMode = SpammingMode;
    } else {
        spammingTimer->stop();
        currentFireMode = ChargingMode;
    }
    emit fireModeChanged(currentFireMode);
}

void Player::stopMoving(){
    horizontalSpeed = 0;
}


EntityType Player::getEntityType() const{
    return EntityType::Player;
}

bool Player::isOnPlatform() {
    return onPlat;
}

QTimer *Player::getChargeTimer() {
    return chargeTimer;
}

QTimer *Player::getSpammingTimer() {
    return spammingTimer;
}

void Player::changeFrame(PixtureState state) {
    auto it = frameChangers.find(state);
    if (it != frameChangers.end()) {
        it->second();
    }
}

qreal Player::getHorizontalSpeed() {
    return horizontalSpeed;
}
