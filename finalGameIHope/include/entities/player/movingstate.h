#ifndef MOVINGSTATE_H
#define MOVINGSTATE_H

#include "include/entities/player/playerstate.h"
#include "include/entities/player/player.h"

class MovingState : public PlayerState {
public:
    explicit MovingState(Player * player);
    void update(Player* player) override;
};

#endif // MOVINGSTATE_H
