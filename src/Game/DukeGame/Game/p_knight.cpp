#include "p_knight.h"

p_Knight::p_Knight(PlayerTeam team)
    : Figure(team, Knight)
{}



Figure::MoveResult p_Knight::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));

        if(direction == 1 && row != 0 || direction == -1 && row != 5){
            if(cells[row - 1 * direction][col]->hasFigure() == false){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col));
            }
        }



        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));


        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));


        if(direction == 1 && row != 0 || direction == -1 && row != 5){
            if(col > 0 && cells[row - 1 * direction][col - 1]->hasFigure() == false){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col - 2));
            }
            if(col < 5 && cells[row - 1 * direction][col + 1]->hasFigure() == false){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col + 2));
            }
        }


        for (int moveRow = row + 1 * direction; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow); moveRow += 1 * direction) {
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
