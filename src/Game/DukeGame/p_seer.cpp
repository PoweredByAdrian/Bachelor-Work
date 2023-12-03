#include "p_seer.h"

p_Seer::p_Seer(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Seer, parent)
{}

bool p_Seer::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Seer::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
