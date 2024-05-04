#ifndef P_SEER_H
#define P_SEER_H

#include "figure.h"

class p_Seer : public Figure
{
public:
    explicit p_Seer(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Seer; }
};

#endif // P_SEER_H
