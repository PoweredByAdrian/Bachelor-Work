#include "p_longbowman.h"

p_Longbowman::p_Longbowman(PlayerTeam team)
    : Figure(team, Longbowman)
{}

bool p_Longbowman::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Longbowman::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 3, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col));
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
