#ifndef P_BOWMAN_H
#define P_BOWMAN_H

#include "figure.h"


class p_Bowman : public Figure
{
public:
    explicit p_Bowman(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;
protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Bowman; }
};

#endif // P_BOWMAN_H
