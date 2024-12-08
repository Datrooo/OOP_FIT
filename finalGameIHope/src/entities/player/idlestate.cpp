#include "include/entities/player/idlestate.h"
#include "include/entities/player/movingstate.h"
#include "include/entities/player/jumpingstate.h"
#include "include/entities/player/player.h"

IdleState::IdleState(Player * player) {
    if (player->getDirection() == Direction::RIGHT) {
        player->changeFrame(Player::idleFrame);
    } else {
        player->changeFrame(Player::idleLFrame);
    }

}

void IdleState::update(Player* player) {
    if (!player->isOnPlatform()) {
        player->setState(new JumpingState(player));
    } else if (player->getHorizontalSpeed() < 0) {
        player->setState(new MovingState(player));
    } else if (player->getHorizontalSpeed() > 0) {
        player->setState(new MovingState(player));
    }
}
