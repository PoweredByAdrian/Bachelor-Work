#ifndef P_GENERAL_H
#define P_GENERAL_H

#include "figure.h"
#include "cell.h"

class p_General : public Figure
{
public:
    explicit p_General(PlayerTeam team);

    // Override the isValidMove function
    bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(Cell *cells[6][6]) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return General; }
};

#endif // P_GENERAL_H
