#ifndef BASEENEMY_H
#define BASEENEMY_H

#include "include/entities/hitable.h"

class BaseEnemy : public Hitable {
public:
    virtual ~BaseEnemy() = default;

    virtual void startAttacking() = 0;
    virtual void stopAttacking() = 0;
    virtual void advance(int phase) = 0;
    virtual void takeDamage(int damage) = 0;
};

struct EnemyData{
    int xPos;
};

#endif // BASEENEMY_H
