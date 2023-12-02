#ifndef P_FOOTMAN_H
#define P_FOOTMAN_H

#include "figure.h"

class p_Footman : public Figure
{
    Q_OBJECT
public:
    explicit p_Footman(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Footman; }
};

#endif // P_FOOTMAN_H
