#ifndef P_FOOTMAN_H
#define P_FOOTMAN_H

#include "figure.h"
#include "cell.h"

class p_Footman : public Figure
{
public:
    explicit p_Footman(PlayerTeam team);

    // Override the isValidMove function
    //bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Footman; }
};

#endif // P_FOOTMAN_H
