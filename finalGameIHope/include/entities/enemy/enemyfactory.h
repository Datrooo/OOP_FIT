#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "include/universalfabric.h"
#include "include/entities/enemy/baseenemy.h"
#include "include/entities/enemy/enemy.h"
#include "include/entities/enemy/flyingenemy.h"

void registerEnemies(UniversalFabric<BaseEnemy, EnemyData> * fabric);

#endif // ENEMYFACTORY_H
