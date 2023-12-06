#include "p_champion.h"

p_Champion::p_Champion(PlayerTeam team, QObject *parent)
    : Figure(team, Champion, parent)
{}

bool p_Champion::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Champion::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row - 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
    }
    return{currentPosition, validMoves};
}
