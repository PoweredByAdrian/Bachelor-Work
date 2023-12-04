#include "p_bowman.h"

p_Bowman::p_Bowman(PlayerTeam team, QObject *parent)
    : Figure(team, Bowman, parent)
{}

bool p_Bowman::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Bowman::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
