#include "p_wizard.h"

p_Wizard::p_Wizard(PlayerTeam team, QObject *parent)
    : Figure(team, Wizard, parent)
{}

bool p_Wizard::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Wizard::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
