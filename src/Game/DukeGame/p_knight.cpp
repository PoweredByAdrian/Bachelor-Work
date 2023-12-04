#include "p_knight.h"

p_Knight::p_Knight(PlayerTeam team, QObject *parent)
    : Figure(team, Knight, parent)
{}

bool p_Knight::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Knight::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
