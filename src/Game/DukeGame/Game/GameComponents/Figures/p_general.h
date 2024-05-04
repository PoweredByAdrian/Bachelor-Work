#ifndef P_GENERAL_H
#define P_GENERAL_H

#include "figure.h"

class p_General : public Figure
{
public:
    explicit p_General(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return General; }
};

#endif // P_GENERAL_H
