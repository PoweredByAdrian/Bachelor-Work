#include "p_pikeman.h"

p_Pikeman::p_Pikeman(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Pikeman, parent)
{}

bool p_Pikeman::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Pikeman::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
