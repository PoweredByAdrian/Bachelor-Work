#include "p_priest.h"

p_Priest::p_Priest(PlayerTeam team, QObject *parent)
    : Figure(team, Priest, parent)
{}

bool p_Priest::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Priest::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
