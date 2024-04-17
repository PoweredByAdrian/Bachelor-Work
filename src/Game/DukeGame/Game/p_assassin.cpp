#include "p_assassin.h"

p_Assassin::p_Assassin(PlayerTeam team)
    : Figure(team, Assassin)
{}

/*bool p_Assassin::isValidMove(Cell *cells[6][6], int row, int col) const
{
    // Get all valid moves from markAvailableJumps
    MoveResult moves = markAvailableJumps(cells);

    // Check if the desired move (row, col) is present in the validMoves list
    for (const auto& move : moves.validMoves) {
        // Extract destination coordinates from the tuple
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);

        // If the desired move matches any valid move, return true
        if (row == moveRow && col == moveCol) {
            return true;
        }
    }

    // If the desired move is not found in validMoves, return false
    return false;
}*/

Figure::MoveResult p_Assassin::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        for (int moveRow = row + 1 * direction; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow); moveRow += 1 * direction) {
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
        for (int moveRow = row - 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol >= 0; moveRow -= 1 * direction, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row - 1 * direction, moveCol = col + 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol < 6; moveRow -= 1 * direction, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }

        }

    }
    else{
        for (int moveRow = row - 1 * direction; (direction == 1 ? moveRow >= minRow : moveRow < minRow); moveRow -= 1 * direction) {

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
        for (int moveRow = row + 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow) && moveCol >= 0; moveRow += 1 * direction, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row + 1 * direction, moveCol = col + 1;(direction == 1 ? moveRow < maxRow : moveRow >= maxRow) && moveCol < 6; moveRow += 1 * direction, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
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
























