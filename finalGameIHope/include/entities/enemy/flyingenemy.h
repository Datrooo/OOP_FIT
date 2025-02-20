#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "baseenemy.h"
#include <QObject>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include "include/entities/direction.h"

class FlyingEnemy : public QObject, public BaseEnemy {
    Q_OBJECT
public:
    FlyingEnemy(const EnemyData& data);
    ~FlyingEnemy() override;

    void takeDamage(int damage) override;
    EntityType getEntityType() const override;

    void startAttacking() override;
    void stopAttacking() override;


signals:
    void enemyDead();
    void takeDamagePlayer(int dmg);

private slots:
    void dropBomb();
    void updateAnimationFrame();

private:
    qreal healthPoints;
    qreal currentHealthPoints;
    QTimer *attackTimer;
    QTimer *animationTimer;
    qreal xSpeed;
    qreal amplitude;
    qreal frequency;
    qreal currentTime;
    Direction direction;

    std::vector<QPixmap> animationFrames;
    int currentFrameIndex;

    void updatePosition();
    void checkCollisionsWithPlayer();
    void advance(int phase) override;

};

#endif // FLYINGENEMY_H
