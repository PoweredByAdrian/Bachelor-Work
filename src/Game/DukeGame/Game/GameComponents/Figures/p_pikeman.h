#ifndef P_PIKEMAN_H
#define P_PIKEMAN_H

#include "figure.h"

class p_Pikeman : public Figure
{
public:
    explicit p_Pikeman(PlayerTeam team);

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Pikeman; }
};

#endif // P_PIKEMAN_H
