#ifndef P_KNIGHT_H
#define P_KNIGHT_H

#include "figure.h"

class p_Knight : public Figure
{
    Q_OBJECT
public:
    explicit p_Knight(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Knight; }
};

#endif // P_KNIGHT_H
