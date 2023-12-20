#ifndef P_KNIGHT_H
#define P_KNIGHT_H

#include "figure.h"
#include "cell.h"

class p_Knight : public Figure
{
public:
    explicit p_Knight(PlayerTeam team);

    // Override the isValidMove function
    bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(Cell *cells[6][6]) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Knight; }
};

#endif // P_KNIGHT_H
