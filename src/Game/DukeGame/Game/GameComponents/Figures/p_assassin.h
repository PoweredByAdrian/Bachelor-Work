#ifndef P_ASSASSIN_H
#define P_ASSASSIN_H

#include "figure.h"

class p_Assassin : public Figure
{
public:
    explicit p_Assassin(PlayerTeam team);

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;
protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Assassin; }
};

#endif // P_ASSASSIN_H
