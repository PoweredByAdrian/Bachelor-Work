#include "p_assassin.h"

p_Assassin::p_Assassin(PlayerTeam team, QObject *parent)
    : Figure(team, Assassin, parent)
{}

bool p_Assassin::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Assassin::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        for (int moveRow = row + 1; moveRow < 6; ++row) {
            if(cells[moveRow][col]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row - 1, moveCol = col - 1; row >= 0 && col >= 0; --moveRow, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row - 1, moveCol = col + 1; row >= 0 && col < 6; --moveRow, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }

        }

    }
    else{
        for (int moveRow = row - 1; moveRow < 0; ++row) {

            if(cells[moveRow][col]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row + 1, moveCol = col - 1; row < 6 && col >= 0; --moveRow, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row + 1, moveCol = col + 1; row < 6 && col < 6; --moveRow, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
    }
    return{currentPosition, validMoves};
}
























