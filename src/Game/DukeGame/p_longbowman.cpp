#include "p_longbowman.h"

p_Longbowman::p_Longbowman(PlayerTeam team, QObject *parent)
    : Figure(team, Longbowman, parent)
{}

bool p_Longbowman::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Longbowman::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
