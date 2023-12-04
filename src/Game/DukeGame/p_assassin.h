#ifndef P_ASSASSIN_H
#define P_ASSASSIN_H

#include "figure.h"

class p_Assassin : public Figure
{
    Q_OBJECT
public:
    explicit p_Assassin(PlayerTeam team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;
protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Assassin; }
};

#endif // P_ASSASSIN_H
