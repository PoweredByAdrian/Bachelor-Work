#ifndef P_GENERAL_H
#define P_GENERAL_H

#include "figure.h"

class p_General : public Figure
{
    Q_OBJECT
public:
    explicit p_General(Figure::Team team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return General; }
};

#endif // P_GENERAL_H
