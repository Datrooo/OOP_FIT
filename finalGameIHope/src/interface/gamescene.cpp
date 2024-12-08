#include "include/interface/gamescene.h"
#include "include/interface/platform.h"
#include "include/entities/enemy/enemyfactory.h"
#include "include/entities/enemy/flyingenemy.h"
#include <QRandomGenerator>


GameScene::GameScene() : player(new Player()), factory(EnemyFactory::instance()) {

    setSceneRect(0, 0, 1072, 603);

    QImage backgroundImage(":/images/interface/background/castle.png");
    QPixmap backgroundPixmap = QPixmap::fromImage(backgroundImage);
    QPixmap scaledPixmap = backgroundPixmap.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    QBrush brush(scaledPixmap);
    setBackgroundBrush(brush);

    addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    fireModeIcon = new QGraphicsPixmapItem(QPixmap(":/images/interface/background/charger.png"));
    fireModeIcon->setPos(10, 0);
    addItem(fireModeIcon);

    connect(player, &Player::fireModeChanged, this, &GameScene::updateFireModeIcon);



    Platform* ground = new Platform(0, 570, 1072, 45, ":/images/interface/platform.png");
    addItem(ground);
    platforms.append(ground);

    Platform* platform1 = new Platform(100, 450, 200, 20, ":/images/interface/platform.png");
    Platform* platform2 = new Platform(300, 350, 300, 20, ":/images/interface/platform.png");
    Platform* platform3 = new Platform(200, 250, 200, 20, ":/images/interface/platform.png");
    Platform* platform4 = new Platform(700, 450, 200, 20, ":/images/interface/platform.png");
    Platform* platform5 = new Platform(700, 250, 100, 20, ":/images/interface/platform.png");

    addItem(platform1);
    platforms.append(platform1);
    addItem(platform2);
    platforms.append(platform2);
    addItem(platform3);
    platforms.append(platform3);
    addItem(platform4);
    platforms.append(platform4);
    addItem(platform5);
    platforms.append(platform5);


    registerEnemies(factory);

    enemy =dynamic_cast<Enemy*>(factory.createEnemy("BOSSEnemy"));
    addItem(dynamic_cast<QGraphicsItem*>(enemy));
    enemy->setPos(900, 600);
    enemy->startAttacking();
    connect(enemy, &Enemy::secondStage, this, &GameScene::spawnMouse);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    gameTimer->start(1000/60);




    healthBarBackground = new QGraphicsRectItem(80, 7.5, 110, 20);
    healthBarBackground->setBrush(Qt::gray);
    healthBarBackground->setPos(10, 10);
    addItem(healthBarBackground);

    healthBar = new QGraphicsRectItem(healthBarBackground->boundingRect().x(), healthBarBackground->boundingRect().y(), 0, 20);
    healthBar->setBrush(Qt::red);
    healthBar->setPos(10, 10);
    healthBar->setRect(healthBar->boundingRect().x(), healthBar->boundingRect().y(), 110, 20);
    addItem(healthBar);

    chargeBarBackground = new QGraphicsRectItem(80, 35.5, 110, 20);
    chargeBarBackground->setBrush(Qt::gray);
    chargeBarBackground->setPos(10, 10);
    addItem(chargeBarBackground);

    chargeBar = new QGraphicsRectItem(chargeBarBackground->boundingRect().x(), chargeBarBackground->boundingRect().y(), 0, 20);
    chargeBar->setBrush(Qt::green);
    chargeBar->setPos(10, 10);
    addItem(chargeBar);

    connect(this->player->getChargeTimer(), &QTimer::timeout, this->player, &Player::updateCharge);
    connect(this->player, &Player::callToUpdateCharge, this, &GameScene::updateChargeBar);
    connect(this->player, &Player::callUpdateHealthBar, this, &GameScene::updateHealthBar);
    connect(this->player->getSpammingTimer(), &QTimer::timeout, this->player, &Player::startSpamming);
    connect(this->enemy, &Enemy::enemyDead, this, &GameScene::levelCompleted);
    connect(this->player, &Player::playerDead, this, &GameScene::gameOver);

}

GameScene::~GameScene() {
    qDebug() << "nachalo";
    disconnect(player, &Player::fireModeChanged, this, &GameScene::updateFireModeIcon);
    qDebug() << "1111";
    disconnect(gameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    qDebug() << "1221";
    disconnect(this->player->getChargeTimer(), &QTimer::timeout, this->player, &Player::updateCharge);
    qDebug() << "1333";
    disconnect(this->player, &Player::callToUpdateCharge, this, &GameScene::updateChargeBar);
    qDebug() << "1111";
    disconnect(this->player, &Player::callUpdateHealthBar, this, &GameScene::updateHealthBar);
    qDebug() << "1222";
    disconnect(this->player->getSpammingTimer(), &QTimer::timeout, this->player, &Player::startSpamming);
    qDebug() << "1333";
    disconnect(this->enemy, &Enemy::enemyDead, this, &GameScene::levelCompleted);
    qDebug() << "1111";
    disconnect(this->player, &Player::playerDead, this, &GameScene::gameOver);
    qDebug() << "1222";
    disconnect(enemy, &Enemy::secondStage, this, &GameScene::spawnMouse);
    qDebug() << "nachalo 1";
    gameTimer->stop();
    delete gameTimer;
    qDebug() << "really";
    if (mouse) {
        qDebug() << "really";
        removeItem(mouse);
        mouse->deleteLater();
        disconnect(this->mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    }
    qDebug() << "nachalo 2";
    delete fireModeIcon;
    delete healthBar;
    delete healthBarBackground;
    delete chargeBar;
    delete chargeBarBackground;
    delete player;
    delete enemy;
    qDebug() << "1111";
    for (Platform* platform : platforms) {
        qDebug() << "1";
        removeItem(platform);
        delete platform;
    }
    qDebug() << "12222";
    platforms.clear();
    qDebug() << "1333";
    //clear();
}

void GameScene::updateHealthBar(qreal healthPoints) {
    healthBar->setRect(healthBarBackground->boundingRect().x(), healthBarBackground->boundingRect().y(), healthPoints * 110/ MAX_HEALTH, 20);
}

void GameScene::updateChargeBar(int currentPower) {
    chargeBar->setRect(chargeBarBackground->boundingRect().x(), chargeBarBackground->boundingRect().y(), currentPower * 110 / MAX_POWER, 20);
}

void GameScene::updateFireModeIcon(Player::FireMode mode) {
    QPixmap pixmap;

    if (mode == Player::ChargingMode) {
        pixmap = QPixmap(":/images/interface/background/charger.png");
    } else if (mode == Player::SpammingMode) {
        pixmap = QPixmap(":/images/interface/background/spam.png");
    }

    fireModeIcon->setPixmap(pixmap);
}

Player * GameScene::getPlayer() {
    return player;
}

QTimer * GameScene::getTimer() {
    return gameTimer;
}

void GameScene::spawnMouse() {
    mouse = dynamic_cast<FlyingEnemy*>(factory.createEnemy("FlyingEnemy"));
    addItem(dynamic_cast<QGraphicsItem*>(mouse));

    mouse->setPos(900, QRandomGenerator::global()->bounded(100, 400));
    mouse->startAttacking();
    connect(this->mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    connect(this->mouse, &FlyingEnemy::takeDamagePlayer, this->player, &Player::takeDamage);

    qDebug() << "spawn Mouse";
}

void GameScene::mouseDead() {
    disconnect(this->mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    disconnect(this->mouse, &FlyingEnemy::takeDamagePlayer, this->player, &Player::takeDamage);
    removeItem(mouse);
    mouse->deleteLater();
    mouse = nullptr;

}
