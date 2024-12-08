#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "include/entities/enemy/baseenemy.h"
#include <functional>
#include <QString>

class EnemyFactory {
public:
    using Creator = std::function<BaseEnemy*()>;

    static EnemyFactory& instance();

    void registerEnemy(const QString& type, Creator creator);

    BaseEnemy* createEnemy(const QString& type) const;

private:
    std::map<QString, Creator> creators;

    EnemyFactory() = default;
};

void registerEnemies(EnemyFactory & factory);

#endif // ENEMYFACTORY_H
