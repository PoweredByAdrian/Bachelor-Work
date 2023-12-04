#ifndef P_PRIEST_H
#define P_PRIEST_H

#include "figure.h"

class p_Priest : public Figure
{
    Q_OBJECT
public:
    explicit p_Priest(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Priest; }
};

#endif // P_PRIEST_H
