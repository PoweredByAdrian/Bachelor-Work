#include "p_assassin.h"

p_Assassin::p_Assassin(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Assassin, parent)
{}

bool p_Assassin::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Assassin::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
