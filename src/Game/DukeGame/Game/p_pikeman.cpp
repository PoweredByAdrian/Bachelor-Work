#include "p_pikeman.h"

p_Pikeman::p_Pikeman(PlayerTeam team)
    : Figure(team, Pikeman)
{}



Figure::MoveResult p_Pikeman::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col + 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col - 1));


        if(direction == 1 && row != 5 || direction == -1 && row != 0){
            if(col < 5 && cells[row + 1 * direction][col + 1]->hasFigure() == false){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col + 2));
            }
            if(col > 0 && cells[row + 1 * direction][col - 1]->hasFigure() == false){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col - 2));
            }
        }
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));
        if((direction == 1 ? row != 0 : row != 5) && cells[row - 1 * direction][col]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col + 1));
    }

    for (auto move = validMoves.begin(); move != validMoves.end();) {
        MoveTypes type = std::get<0>(*move);
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
        else if(type == Strike && !cells[targetRow][targetCol]->hasFigure()){
            move = validMoves.erase(move);
        }
        else{
            ++move;
        }
    }
    return{currentPosition, validMoves};
}
