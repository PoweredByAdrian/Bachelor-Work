#ifndef P_FOOTMAN_H
#define P_FOOTMAN_H

#include "figure.h"

class p_Footman : public Figure
{
public:
    explicit p_Footman(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Footman; }
};

#endif // P_FOOTMAN_H
