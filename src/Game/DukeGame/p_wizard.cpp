#include "p_wizard.h"

p_Wizard::p_Wizard(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Wizard, parent)
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
