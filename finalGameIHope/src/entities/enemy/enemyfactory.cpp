#include "include/entities/enemy/enemyfactory.h"
#include <stdexcept>
#include "include/entities/enemy/enemy.h"
#include "include/entities/enemy/flyingenemy.h"

EnemyFactory& EnemyFactory::instance() {
    qDebug() << "EnemyFactory::instance() called";
    static EnemyFactory factory;
    return factory;
}

void EnemyFactory::registerEnemy(const QString& type, Creator creator) {
    creators[type] = creator;
}

BaseEnemy* EnemyFactory::createEnemy(const QString& type) const {
    auto it = creators.find(type);
    if (it != creators.end()) {
        return (it->second)();
    }
    throw std::runtime_error("Unknown enemy type: " + type.toStdString());
}

void registerEnemies(EnemyFactory& factory) {
    factory.registerEnemy("BOSSEnemy", []() -> BaseEnemy* {
        return new Enemy();
    });

    factory.registerEnemy("FlyingEnemy", []() -> BaseEnemy* {
        return new FlyingEnemy();
    });
}
