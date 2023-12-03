#include "p_footman.h"

p_Footman::p_Footman(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Footman, parent)
{}

bool p_Footman::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Footman::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
