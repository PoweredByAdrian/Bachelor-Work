#include "p_general.h"

p_General::p_General(PlayerTeam team)
    : Figure(team, General)
{}

bool p_General::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_General::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 1));

        if(cells[row][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
        }
        if(cells[row][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));
    }
    else{

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 1));

        if(cells[row][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
        }
        if(cells[row][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1, col - 1));
    }
    //TODO Command
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
