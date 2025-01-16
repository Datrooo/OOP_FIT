#include "include/interface/gamescene.h"
#include "include/interface/platform.h"
#include "include/entities/enemy/enemyfactory.h"
#include "include/entities/enemy/flyingenemy.h"
#include <QRandomGenerator>



GameScene::GameScene() : player(new Player()) {

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


    QList<QRectF> platformSettings = {
        QRectF(0, 570, 1072, 45),
        QRectF(100, 450, 200, 20),
        QRectF(300, 350, 300, 20),
        QRectF(200, 250, 200, 20),
        QRectF(700, 450, 200, 20),
        QRectF(700, 250, 100, 20)
    };

    for (const QRectF& rect : platformSettings) {
        Platform* platform = new Platform(rect.x(), rect.y(), rect.width(), rect.height(), ":/images/interface/platform.png");
        addItem(platform);
        platforms.append(platform);
    }

    fabric = new UniversalFabric<BaseEnemy, EnemyData>();
    registerEnemies(fabric);
    addData("bossData", 600, 200, 500);
    enemy = dynamic_cast<Enemy*>(fabric->createObject("Ghost", findData("bossData")));
    addItem(dynamic_cast<QGraphicsItem*>(enemy));
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

    connect(player->getChargeTimer(), &QTimer::timeout, player, &Player::updateCharge);
    connect(player, &Player::callToUpdateCharge, this, &GameScene::updateChargeBar);
    connect(player, &Player::callUpdateHealthBar, this, &GameScene::updateHealthBar);
    connect(player->getSpammingTimer(), &QTimer::timeout, player, &Player::startSpamming);
    connect(enemy, &Enemy::enemyDead, this, &GameScene::levelCompleted);
    connect(player, &Player::playerDead, this, &GameScene::gameOver);

}

GameScene::~GameScene() {
    //qDebug() << "nachalo";
    disconnect(player, &Player::fireModeChanged, this, &GameScene::updateFireModeIcon);
    //qDebug() << "1111";
    disconnect(gameTimer, &QTimer::timeout, this, &QGraphicsScene::advance);
    //qDebug() << "1221";
    disconnect(player->getChargeTimer(), &QTimer::timeout, player, &Player::updateCharge);
    //qDebug() << "1333";
    disconnect(player, &Player::callToUpdateCharge, this, &GameScene::updateChargeBar);
    //qDebug() << "1111";
    disconnect(player, &Player::callUpdateHealthBar, this, &GameScene::updateHealthBar);
    //qDebug() << "1222";
    disconnect(player->getSpammingTimer(), &QTimer::timeout, player, &Player::startSpamming);
    //qDebug() << "1333";
    disconnect(enemy, &Enemy::enemyDead, this, &GameScene::levelCompleted);
    //qDebug() << "1111";
    disconnect(player, &Player::playerDead, this, &GameScene::gameOver);
    //qDebug() << "1222";
    disconnect(enemy, &Enemy::secondStage, this, &GameScene::spawnMouse);
    //qDebug() << "nachalo 1";
    if (gameTimer){
        gameTimer->stop();
        delete gameTimer;
    }

    //qDebug() << "really";
    if (mouse) {
        qDebug() << "really";
        removeItem(mouse);
        mouse->deleteLater();
        disconnect(mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    }

    if (fireModeIcon){
        delete fireModeIcon;
    }
    if (healthBar) {
        delete healthBar;
    }
    if (healthBarBackground) {
        delete healthBarBackground;
    }
    if (chargeBar) {
        delete chargeBar;
    }
    if (chargeBarBackground) {
        delete chargeBarBackground;
    }
    if (player) {
        delete player;
    }
    if (enemy) {
        delete enemy;
    }

    //qDebug() << "1111";
    for (Platform* platform : platforms) {
        //qDebug() << "1";
        removeItem(platform);
        delete platform;
    }
    //qDebug() << "12222";
    platforms.clear();
    delete fabric;
    //qDebug() << "1333";
    clear();
}

void GameScene::addData(const QString & type, qreal posX, qreal posY, qreal health){
    enemiesData[type] = (EnemyData){posX, posY, health};
}

EnemyData GameScene::findData(const QString & type){
    auto it = enemiesData.find(type);
    if (it != enemiesData.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Type not registered: " + type.toStdString());
    }
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
    addData("mouseData1", 100, 400, 50);

    mouse = dynamic_cast<FlyingEnemy*>(fabric->createObject("Mouse", findData("mouseData1")));
    addItem(dynamic_cast<QGraphicsItem*>(mouse));

    mouse->startAttacking();
    connect(mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    connect(mouse, &FlyingEnemy::takeDamagePlayer, player, &Player::takeDamage);

    qDebug() << "spawn Mouse";
}

void GameScene::mouseDead() {
    disconnect(mouse, &FlyingEnemy::enemyDead, this, &GameScene::mouseDead);
    disconnect(mouse, &FlyingEnemy::takeDamagePlayer, player, &Player::takeDamage);
    removeItem(mouse);
    mouse->deleteLater();
    mouse = nullptr;

}
