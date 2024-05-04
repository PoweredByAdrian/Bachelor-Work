#ifndef P_CHAMPION_H
#define P_CHAMPION_H

#include "figure.h"

class p_Champion : public Figure
{
public:
    explicit p_Champion(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Champion; }
};

#endif // P_CHAMPION_H
