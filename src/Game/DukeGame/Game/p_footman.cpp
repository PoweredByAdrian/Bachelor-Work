#include "p_footman.h"

p_Footman::p_Footman(PlayerTeam team)
    : Figure(team, Footman)
{}



Figure::MoveResult p_Footman::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));

    }
    else{

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));

        if((direction == 1 ? row != 5 : row != 0) && cells[row + 1 * direction][col]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col));
        }


    }
    for (auto move = validMoves.begin(); move != validMoves.end();) {
        int targetRow = std::get<1>(*move);
        int targetCol = std::get<2>(*move);

        // if (cells[targetRow][targetCol]->hasFigure()) {
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
