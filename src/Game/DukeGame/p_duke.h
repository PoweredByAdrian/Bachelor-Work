#ifndef P_DUKE_H
#define P_DUKE_H

#include "figure.h"

class p_Duke : public Figure
{
    Q_OBJECT
public:
    explicit p_Duke(Figure::Team team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Duke; }
};

#endif // P_DUKE_H
