#include "p_pikeman.h"

p_Pikeman::p_Pikeman(PlayerTeam team)
    : Figure(team, Pikeman)
{}

bool p_Pikeman::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Pikeman::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col + 1));
        if(cells[row + 1][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2, col + 2));
        }
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col - 1));
        if(cells[row + 1][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2, col - 2));
        }
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));
        if(cells[row - 1][col]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2, col));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col + 1));
    }
    //TODO Strike
    for (auto move = validMoves.begin(); move != validMoves.end();) {
        int targetRow = std::get<1>(*move);
        int targetCol = std::get<2>(*move);

        // if (cells[targetRow][targetCol]->hasFigure()) {
        //     move = validMoves.erase(move);
        // } else {
        //     ++move;
        // }

        if(cells[targetRow][targetCol]->hasFigure()){
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
