#include "p_general.h"

p_General::p_General(PlayerTeam team, QObject *parent)
    : Figure(team, General, parent)
{}

bool p_General::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_General::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
