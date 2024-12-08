#include "include/entities/player/jumpingstate.h"
#include "include/entities/player/idlestate.h"
#include "include/entities/player/movingstate.h"
#include "include/entities/player/player.h"

JumpingState::JumpingState(Player * player) {
    if(player->getDirection() == Direction::RIGHT){
        player->changeFrame(Player::jumpingFrame);
    } else {
        player->changeFrame(Player::jumpingLFrame);
    }
}

void JumpingState::update(Player* player) {
    if (player->isOnPlatform()) {
        if (player->getHorizontalSpeed() != 0) {
            player->setState(new MovingState(player));
        } else {
            player->setState(new IdleState(player));
        }
    } else {
        if(player->getDirection() == Direction::RIGHT) {
            player->changeFrame(Player::jumpingFrame);
        } else {
            player->changeFrame(Player::jumpingLFrame);
        }
    }

}

