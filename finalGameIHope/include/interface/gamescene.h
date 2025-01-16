#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "include/entities/player/player.h"
#include "include/entities/enemy/enemy.h"
#include <QObject>
#include "include/entities/enemy/enemyfactory.h"
#include "include/entities/enemy/flyingenemy.h"
#include "include/universalfabric.h"
#include <QString>

class GameScene : public QGraphicsScene {
    Q_OBJECT
public:
    GameScene();
    ~GameScene();
    Player * getPlayer();
    QTimer * getTimer();
    void addData(const QString & str, qreal posX, qreal posY, qreal health);
    EnemyData findData(const QString & str);


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
    std::map<const QString, EnemyData> enemiesData;

};



#endif // GAMESCENE_H
