#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QObject>
#include "include/entities/direction.h"
#include "include/entities/hitable.h"
#include <QGraphicsPixmapItem>
#include <QList>

#define MAX_POWER 200
#define MAX_HEALTH 100

class PlayerState;
class Platform;

class Player : public QObject, public Hitable {
    Q_OBJECT
public:
    Player();
    ~Player();

    enum FireMode {
        ChargingMode,
        SpammingMode
    };

    void setState(PlayerState* newState);

    Direction getDirection();
    EntityType getEntityType() const override;
    void takeDamage(int damage) override;

    bool isOnPlatform();
    qreal getHorizontalSpeed();


    bool charging;
    void updateCharge();


    QTimer * getChargeTimer();
    QTimer * getSpammingTimer();

    enum PixtureState{
        idleFrame,
        movingFrame,
        jumpingFrame,
        idleLFrame,
        movingLFrame,
        jumpingLFrame
    };

    void changeFrame(PixtureState state);

signals:
    void posChanged(qreal x, qreal y);
    void callToUpdateCharge(int currentPower);
    void fireModeChanged(FireMode newMode);
    void callUpdateHealthBar(qreal healthPoints);
    void playerDead();

public slots:
    void startSpamming();
    void startShooting();
    void shootBullet();
    void moveLeft();
    void moveRight();
    void jump();
    void goDown();
    void changeShootingMode();
    void stopMoving();

private:
    QPixmap bul;

    Direction direction;
    PlayerState* state;
    qreal healthPoint;
    qreal jumpSpeed;
    qreal gravity;
    bool onPlat;

    qreal horizontalSpeed;

    void advance(int phase) override;

    QList<QGraphicsItem *> collidingItemsWithToleance(QGraphicsItem * parent, qreal tolerance);
    void onCollisionWithPlatform();

    FireMode currentFireMode;
    int currentPower = 0;
    bool canShoot;
    void shoot();
    QTimer * chargeTimer;
    QTimer* spammingTimer;

    typedef std::function<void()> frimeChanger;
    std::unordered_map<int, frimeChanger> frameChangers;
    std::vector<QPixmap> animationFrames;

};

#endif // PLAYER_H
