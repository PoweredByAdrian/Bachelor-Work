#include "p_assassin.h"

p_Assassin::p_Assassin(PlayerTeam team, QObject *parent)
    : Figure(team, Assassin, parent)
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
