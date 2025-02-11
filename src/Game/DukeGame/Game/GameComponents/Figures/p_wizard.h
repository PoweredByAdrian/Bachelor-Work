#ifndef P_WIZARD_H
#define P_WIZARD_H

#include "figure.h"

class p_Wizard : public Figure
{
public:
    explicit p_Wizard(PlayerTeam team);

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Wizard; }
};

#endif // P_WIZARD_H
