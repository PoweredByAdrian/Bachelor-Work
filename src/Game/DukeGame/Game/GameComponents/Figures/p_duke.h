#ifndef P_DUKE_H
#define P_DUKE_H

#include "figure.h"

class p_Duke : public Figure
{
public:
    explicit p_Duke(PlayerTeam team);


    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(GameState state) const override;
    QList<QPair<int, int>> getPlacableCellsForNewPiece(GameState state, bool emptyCheck) override;
protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Duke; }
};

#endif // P_DUKE_H
