#ifndef P_CHAMPION_H
#define P_CHAMPION_H

#include "figure.h"

class p_Champion : public Figure
{
    Q_OBJECT
public:
    explicit p_Champion(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Champion; }
};

#endif // P_CHAMPION_H
