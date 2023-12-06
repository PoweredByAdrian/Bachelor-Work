#ifndef P_PRIEST_H
#define P_PRIEST_H

#include "figure.h"
#include "cell.h"

class p_Priest : public Figure
{
    Q_OBJECT
public:
    explicit p_Priest(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(Cell *cells[6][6]) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Priest; }
};

#endif // P_PRIEST_H
