#include "p_dracoon.h"

p_Dracoon::p_Dracoon(PlayerTeam team)
    : Figure(team, Dracoon)
{}



Figure::MoveResult p_Dracoon::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
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
        if((direction == 1 ? row != 5 : row != 0) && cells[row + 1 * direction][col]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col));
        }


        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));

        // Check diagonal backward moves
        for (int moveRow = row - 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol >= 0; moveRow -= 1 * direction, --moveCol) {
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

        for (int moveRow = row - 1 * direction, moveCol = col + 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol < 6; moveRow -= 1 * direction, ++moveCol) {
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
        else if(type == Strike && !cells[targetRow][targetCol]->hasFigure()){
            move = validMoves.erase(move);
        }
        else{
            ++move;
        }
    }

    return{currentPosition, validMoves};
}
