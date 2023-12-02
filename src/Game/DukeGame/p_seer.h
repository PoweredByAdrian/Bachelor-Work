#ifndef P_SEER_H
#define P_SEER_H

#include "figure.h"

class p_Seer : public Figure
{
    Q_OBJECT
public:
    explicit p_Seer(QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Seer; }
};

#endif // P_SEER_H
