#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <QKeyEvent>


class Player;

class PlayerState {
public:
    virtual ~PlayerState() = default;
    virtual void update(Player* player) = 0;
};

#endif // PLAYERSTATE_H
