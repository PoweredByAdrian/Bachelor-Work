#include "p_pikeman.h"

p_Pikeman::p_Pikeman(QObject *parent)
    : Figure{parent}
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
