#include "player.h"

Player::Player( PlayerTeam newTeam)
{
    team = newTeam;
    setPieceBag();
}

void Player::setPieceBag()
{
    figurebag = new figureBag(team);
}

figureBag* Player::getPieceBag() const
{
    return figurebag;
}

