#include "p_duke.h"

p_Duke::p_Duke(PlayerTeam team, QObject *parent)
    : Figure(team, Duke, parent)
{}
bool p_Duke::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Duke::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
