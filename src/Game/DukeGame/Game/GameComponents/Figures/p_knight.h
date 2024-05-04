#ifndef P_KNIGHT_H
#define P_KNIGHT_H

#include "figure.h"

class p_Knight : public Figure
{
public:
    explicit p_Knight(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Knight; }
};

#endif // P_KNIGHT_H
