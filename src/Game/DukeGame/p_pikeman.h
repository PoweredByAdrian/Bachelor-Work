#ifndef P_PIKEMAN_H
#define P_PIKEMAN_H

#include "figure.h"
#include "cell.h"

class p_Pikeman : public Figure
{
    Q_OBJECT
public:
    explicit p_Pikeman(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(Cell *cells[6][6]) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Pikeman; }
};

#endif // P_PIKEMAN_H
