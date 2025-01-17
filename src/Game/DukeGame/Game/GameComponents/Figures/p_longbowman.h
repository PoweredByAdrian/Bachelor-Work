#ifndef P_LONGBOWMAN_H
#define P_LONGBOWMAN_H

#include "figure.h"

class p_Longbowman : public Figure
{
public:
    explicit p_Longbowman(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Longbowman; }
};

#endif // P_LONGBOWMAN_H
