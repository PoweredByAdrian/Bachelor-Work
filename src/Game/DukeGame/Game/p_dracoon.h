#ifndef P_DRACOON_H
#define P_DRACOON_H

#include "figure.h"
#include "cell.h"

class p_Dracoon : public Figure
{
public:
    explicit p_Dracoon(PlayerTeam team);

    // Override the isValidMove function
    //bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Dracoon; }
};

#endif // P_DRACOON_H
