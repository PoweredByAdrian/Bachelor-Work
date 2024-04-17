#include "p_duke.h"

p_Duke::p_Duke(PlayerTeam team)
    : Figure(team, Duke)
{}


Figure::MoveResult p_Duke::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        for (int moveCol = col - 1; moveCol >= 0; --moveCol) {
            if(cells[row][moveCol]->hasFigure()){
                if(cells[row][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }

        }
        for (int moveCol = col + 1; moveCol < 6; ++moveCol) {
            if(cells[row][moveCol]->hasFigure()){
                if(cells[row][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
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
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
        for (int moveRow = row + 1; moveRow < 6; ++moveRow) {
            if(cells[moveRow][col]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
    }
    return{currentPosition, validMoves};
}


























