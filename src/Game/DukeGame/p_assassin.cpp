#include "p_assassin.h"

p_Assassin::p_Assassin(PlayerTeam team)
    : Figure(team, Assassin)
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

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        for (int moveRow = row + 1 * direction; moveRow < maxRow; moveRow += 1 * direction) {
            if(cells[moveRow][col]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row - 1 * direction, moveCol = col - 1; row >= minRow && col >= 0; moveRow -= 1 * direction, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row - 1 * direction, moveCol = col + 1; row >= minRow && col < 6; moveRow -= 1 * direction, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }

        }

    }
    else{
        for (int moveRow = row - 1 * direction; moveRow >= minRow; moveRow -= 1 * direction) {

            if(cells[moveRow][col]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row + 1 * direction, moveCol = col - 1; row < maxRow && col >= 0; moveRow += 1 * direction, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row + 1 * direction, moveCol = col + 1; row < maxRow && col < 6; moveRow += 1 * direction, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][col]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
    }
    return{currentPosition, validMoves};
}
























