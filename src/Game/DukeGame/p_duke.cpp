#include "p_duke.h"

p_Duke::p_Duke(PlayerTeam team, QObject *parent)
    : Figure(team, Duke, parent)
{}
bool p_Duke::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Duke::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, 0));
        validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, 5));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, 0));
        validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, 5));
    }
    return{currentPosition, validMoves};
}
