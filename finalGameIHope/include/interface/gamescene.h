#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "include/entities/player/player.h"
#include "include/entities/enemy/enemy.h"
#include <QObject>
#include "include/entities/enemy/enemyfactory.h"
#include "include/entities/enemy/flyingenemy.h"
#include "include/universalfabric.h"

class GameScene : public QGraphicsScene {
    Q_OBJECT
public:
    GameScene();
    ~GameScene();
    Player * getPlayer();
    QTimer * getTimer();


signals:
    void levelCompleted();
    void gameOver();


private slots:
    void updateHealthBar(qreal healthPoints);
    void updateChargeBar(int currentPower);
    void updateFireModeIcon(Player::FireMode mode);
    void spawnMouse();
    void mouseDead();


private:
    Player* player = nullptr;
    Enemy * enemy = nullptr;
    FlyingEnemy * mouse = nullptr;
    QVector<Platform *> platforms;
    UniversalFabric<BaseEnemy, EnemyData> *fabric;

    QTimer * gameTimer;
    QGraphicsRectItem* healthBar;
    QGraphicsRectItem* healthBarBackground;
    QGraphicsRectItem* chargeBar;
    QGraphicsRectItem* chargeBarBackground;
    QGraphicsPixmapItem* fireModeIcon;

};



#endif // GAMESCENE_H
