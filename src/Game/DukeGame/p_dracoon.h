#ifndef P_DRACOON_H
#define P_DRACOON_H

#include "figure.h"

class p_Dracoon : public Figure
{
    Q_OBJECT
public:
    explicit p_Dracoon(Figure::Team team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Dracoon; }
};

#endif // P_DRACOON_H
