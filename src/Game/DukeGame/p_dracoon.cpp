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
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col +1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2, col - 2));

    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 1));

        // Check diagonal backward moves
        for (int moveRow = row - 1, moveCol = col - 1; row >= 0 && col >= 0; --moveRow, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }

        }

        for (int moveRow = row - 1, moveCol = col + 1; row >= 0 && col < 6; --moveRow, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
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

        if (cells[targetRow][targetCol]->hasFigure() && type != Strike) {
            move = validMoves.erase(move);
        } else {
            ++move;
        }
    }

    return{currentPosition, validMoves};
}
