#include "p_marshall.h"

p_Marshall::p_Marshall(PlayerTeam team)
    : Figure(team, Marshall)
{}

bool p_Marshall::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Marshall::markAvailableJumps(Cell *cells[6][6]) const
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

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));

        if(cells[row][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
        }
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        if(cells[row][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1, col - 1));
    }
    //TODO command
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
