#ifndef P_DUKE_H
#define P_DUKE_H

#include "figure.h"
#include "cell.h"

class p_Duke : public Figure
{
    Q_OBJECT
public:
    explicit p_Duke(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *cells[6][6], int row, int col) const override;

    // Override the markAvailableJumps function
    MoveResult markAvailableJumps(Cell *cells[6][6]) const override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Duke; }
};

#endif // P_DUKE_H
