#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "enums.h"
#include <tuple>
#include <QList>
#include "cell.h"

class MoveValidator
{
public:
    MoveValidator();

    QList<std::tuple<MoveTypes, int, int>> validateMoves(Cell *cells[6][6], QPair<int, int> currentPosition, QList<std::tuple<MoveTypes, int, int>>& moves);
private:
    Cell *board[6][6];
    QPair<int, int> currPos;
    bool isValidMove(int toX, int toY);
    bool isValidJump(int toX, int toY);
    bool isValidSlide(int toX, int toY);
    bool isValidJumpSlide(int toX, int toY);
    bool isValidStrike(int toX, int toY);
    bool isValidCommand(int toX, int toY);
};

#endif // MOVEVALIDATOR_H
