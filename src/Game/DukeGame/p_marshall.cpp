#include "p_marshall.h"

p_Marshall::p_Marshall(QObject *parent)
    : Figure{parent}
{}

bool p_Marshall::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Marshall::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
