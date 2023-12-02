#ifndef P_MARSHALL_H
#define P_MARSHALL_H

#include "figure.h"

class p_Marshall : public Figure
{
    Q_OBJECT
public:
    explicit p_Marshall(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Marshall; }
};

#endif // P_MARSHALL_H
