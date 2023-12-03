#ifndef P_WIZARD_H
#define P_WIZARD_H

#include "figure.h"

class p_Wizard : public Figure
{
    Q_OBJECT
public:
    explicit p_Wizard(Figure::Team team, QObject *parent = nullptr);

    // Override the isValidMove function
    bool isValidMove(Cell *destination) const override;

    // Override the markAvailableJumps function
    void markAvailableJumps() override;

protected:
    // Implementation of the type method for the Pawn class
    PieceType type() const override { return Wizard; }
};

#endif // P_WIZARD_H
