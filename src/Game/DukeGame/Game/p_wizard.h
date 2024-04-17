#ifndef P_WIZARD_H
#define P_WIZARD_H

#include "figure.h"
#include "cell.h"

class p_Wizard : public Figure
{
public:
    explicit p_Wizard(PlayerTeam team);

    // Override the isValidMove function
    //bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Wizard; }
};

#endif // P_WIZARD_H
