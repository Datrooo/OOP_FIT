#include "include/entities/enemy/enemyfactory.h"

void registerEnemies(UniversalFabric<BaseEnemy, EnemyData>* fabric) {
    fabric->registerObject("Mouse", []() -> BaseEnemy* {
        return new FlyingEnemy();
    });

    fabric->registerObject("Ghost", []() -> BaseEnemy* {
        return new Enemy();
    });
}
