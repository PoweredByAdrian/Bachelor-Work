#ifndef P_PRIEST_H
#define P_PRIEST_H

#include "figure.h"

class p_Priest : public Figure
{
public:
    explicit p_Priest(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Priest; }
};

#endif // P_PRIEST_H
