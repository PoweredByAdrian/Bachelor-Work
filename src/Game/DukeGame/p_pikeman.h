#ifndef P_PIKEMAN_H
#define P_PIKEMAN_H

#include "figure.h"

class p_Pikeman : public Figure
{
    Q_OBJECT
public:
    explicit p_Pikeman(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Pikeman; }
};

#endif // P_PIKEMAN_H
