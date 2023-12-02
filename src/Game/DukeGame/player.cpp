#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{}

void Player::setPieceBag(figureBag* bag)
{
    figurebag = bag;
}

figureBag* Player::getPieceBag() const
{
    return figurebag;
}

Figure* Player::getRandomPieceFromBag()
{
    if (figurebag)
    {
        return figurebag->takeRandomPiece();
    }
    else
    {
        return nullptr; // Player has no piece bag
    }
}
