#include "p_knight.h"

p_Knight::p_Knight(PlayerTeam team)
    : Figure(team, Knight)
{}

bool p_Knight::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Knight::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 1));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2, col + 2));

        for (int moveRow = row + 1; moveRow < 6; ++row) {
            if(cells[moveRow][col]->hasFigure()){
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

        if (cells[targetRow][targetCol]->hasFigure()) {
            move = validMoves.erase(move);
        } else {
            ++move;
        }
    }
    return{currentPosition, validMoves};
}
