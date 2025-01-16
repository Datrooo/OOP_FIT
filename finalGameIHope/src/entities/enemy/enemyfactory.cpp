#include "include/entities/enemy/enemyfactory.h"

void registerEnemies(UniversalFabric<BaseEnemy, EnemyData>* fabric) {
    fabric->registerObject("Mouse", [](const EnemyData& data) -> BaseEnemy* {
        return new FlyingEnemy(data);
    });

    fabric->registerObject("Ghost", [](const EnemyData& data) -> BaseEnemy* {
        return new Enemy(data);
    });
}
