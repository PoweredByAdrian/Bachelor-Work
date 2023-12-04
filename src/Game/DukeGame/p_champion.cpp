#include "p_champion.h"

p_Champion::p_Champion(PlayerTeam team, QObject *parent)
    : Figure(team, Champion, parent)
{}

bool p_Champion::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Champion::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
