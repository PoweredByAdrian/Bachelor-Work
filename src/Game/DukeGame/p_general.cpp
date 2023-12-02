#include "p_general.h"

p_General::p_General(QObject *parent)
    : Figure{parent}
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
