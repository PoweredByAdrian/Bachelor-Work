#ifndef PLAYER_H
#define PLAYER_H

#include "figurebag.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player( PlayerTeam newTeam = NoTeam);

    void setPieceBag();
    figureBag* getPieceBag() const;

    Figure* getRandomPieceFromBag();
    PlayerTeam getTeam() {return team;}

private:
    figureBag* figurebag;
    PlayerTeam team;
signals:
};

#endif // PLAYER_H
