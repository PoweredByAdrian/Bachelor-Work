#include "p_marshall.h"

p_Marshall::p_Marshall(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Marshall, parent)
{}

bool p_Marshall::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Marshall::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
