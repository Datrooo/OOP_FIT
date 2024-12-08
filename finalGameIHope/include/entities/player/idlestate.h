#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "playerstate.h"
#include "include/entities/player/player.h"

class IdleState : public PlayerState {
public:
    IdleState(Player * player);
    void update(Player* player) override;
};

#endif // IDLESTATE_H
