#ifndef P_PIKEMAN_H
#define P_PIKEMAN_H

#include "figure.h"
#include "cell.h"

class p_Pikeman : public Figure
{
public:
    explicit p_Pikeman(PlayerTeam team);

    // Override the isValidMove function
    //bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Pikeman; }
};

#endif // P_PIKEMAN_H
