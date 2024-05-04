#ifndef P_MARSHALL_H
#define P_MARSHALL_H

#include "figure.h"

class p_Marshall : public Figure
{
public:
    explicit p_Marshall(PlayerTeam team);

    // Override the markAvailableJumps function
   MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Marshall; }
};

#endif // P_MARSHALL_H
