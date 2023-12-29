#include "p_dracoon.h"

p_Dracoon::p_Dracoon(PlayerTeam team)
    : Figure(team, Dracoon)
{}

bool p_Dracoon::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Dracoon::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col +1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col - 2));

    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));
        if(cells[row + 1 * direction][col]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col));
        }


        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));

        // Check diagonal backward moves
        for (int moveRow = row - 1 * direction, moveCol = col - 1; row >= minRow && col >= 0; moveRow -= 1 * direction, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                   validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }

        }

        for (int moveRow = row - 1 * direction, moveCol = col + 1; row >= minRow && col < 6; moveRow -= 1 * direction, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                if(cells[moveRow][moveCol]->getFigure()->getTeam() != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }

        }
    }
    //TODO Strike
    for (auto move = validMoves.begin(); move != validMoves.end();) {
        MoveTypes type = std::get<0>(*move);
        int targetRow = std::get<1>(*move);
        int targetCol = std::get<2>(*move);

        // if (cells[targetRow][targetCol]->hasFigure() && type != Strike) {
        //     move = validMoves.erase(move);
        // } else {
        //     ++move;
        // }
        if(targetRow >= 6 || targetCol >= 6 || targetRow < 0 || targetCol < 0){
            move = validMoves.erase(move);
        }
        else if(cells[targetRow][targetCol]->hasFigure()){
            Figure* target = cells[targetRow][targetCol]->getFigure();
            if(target->getTeam() == this->team){
                move = validMoves.erase(move);
            }
            else{
                ++move;
            }
        }
        else{
            ++move;
        }
    }

    return{currentPosition, validMoves};
}
