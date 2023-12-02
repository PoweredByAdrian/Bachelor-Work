#ifndef P_BOWMAN_H
#define P_BOWMAN_H

#include "figure.h"

class p_Bowman : public Figure
{
    Q_OBJECT

public:
    explicit p_Bowman(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Bowman; }
};

#endif // P_BOWMAN_H
