#include "p_duke.h"

p_Duke::p_Duke(PlayerTeam team)
    : Figure(team, Duke)
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
        for (int moveCol = col - 1; moveCol >= 0; ++moveCol) {
            if(cells[row][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }

        }
        for (int moveCol = col + 1; moveCol < 6; ++moveCol) {
            if(cells[row][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }

        }
    }
    else{
        for (int moveRow = row - 1; moveRow >= 0; --moveRow) {
            if(cells[moveRow][col]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
        for (int moveRow = row + 1; moveRow < 6; ++moveRow) {
            if(cells[moveRow][col]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
    }
    return{currentPosition, validMoves};
}



























