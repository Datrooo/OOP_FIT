#include "include/entities/player/movingstate.h"
#include "include/entities/player/idlestate.h"
#include "include/entities/player/jumpingstate.h"

MovingState::MovingState(Player * player) {
    if (player->getDirection() == Direction::RIGHT) {
        player->changeFrame(Player::movingFrame);
    } else {
        player->changeFrame(Player::movingLFrame);
    }
}


void MovingState::update(Player* player) {
    if (player->getHorizontalSpeed() == 0) {
        player->setState(new IdleState(player));
    } else if (!player->isOnPlatform()) {
        player->setState(new JumpingState(player));
    } else{
        if(player->getDirection() == Direction::RIGHT) {
            player->changeFrame(Player::movingFrame);
        } else {
            player->changeFrame(Player::movingLFrame);
        }
    }
    //qDebug() << "moving State";
}
