#ifndef P_LONGBOWMAN_H
#define P_LONGBOWMAN_H

#include "figure.h"

class p_Longbowman : public Figure
{
    Q_OBJECT
public:
    explicit p_Longbowman(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Longbowman; }
};

#endif // P_LONGBOWMAN_H
