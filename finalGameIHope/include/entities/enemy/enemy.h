#ifndef ENEMY_H
#define ENEMY_H

#include "baseenemy.h"
#include <QObject>
#include <QTimer>
#include "include/entities/direction.h"

class Enemy : public QObject, public BaseEnemy {
    Q_OBJECT
public:
    Enemy(const EnemyData& data);
    ~Enemy() override;

    void takeDamage(int damage) override;
    EntityType getEntityType() const override;

    void startAttacking() override;
    void stopAttacking() override;


signals:
    void enemyDead();
    void secondStage();

private slots:
    void performAttack();
    void changeToSecondStage();

private:
    char stage;
    QTimer *attackTimer;
    qreal healthPoints;
    qreal currentHealthPoints;
    Direction direction;

    QPixmap defaultPixmap;
    QPixmap defaultReversePixmap;

    void shootFireball();
    void shootLaser();
    void shootSpreadShot();
    void advance(int phase) override;


    qreal xMin;
    qreal xMax;
    qreal yMin;
    qreal yMax;
};

#endif // ENEMY_H
