#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

#include "playerstate.h"
#include "include/entities/player/player.h"

class JumpingState : public PlayerState {
public:
    JumpingState(Player * player);
    void update(Player* player) override;
};

#endif // JUMPINGSTATE_H
