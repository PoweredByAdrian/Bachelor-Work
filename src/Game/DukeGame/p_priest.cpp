#include "p_priest.h"

p_Priest::p_Priest(PlayerTeam team)
    : Figure(team, Priest)
{}

bool p_Priest::isValidMove(Cell *cells[6][6], int row, int col) const
{
    //TODO
    return true;
}

Figure::MoveResult p_Priest::markAvailableJumps(Cell *cells[6][6]) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        // Check diagonal backward moves
        for (int moveRow = row - 1, moveCol = col - 1; moveRow >= 0 && moveCol >= 0; --moveRow, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }
        }
        for (int moveRow = row - 1, moveCol = col + 1; moveRow >= 0 && moveCol < 6; --moveRow, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }
        }
        // Check diagonal forward moves
        for (int moveRow = row + 1, moveCol = col - 1; moveRow < 6 && moveCol >= 0; ++moveRow, --moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }
        }
        for (int moveRow = row + 1, moveCol = col + 1; moveRow < 6 && moveCol < 6; ++moveRow, ++moveCol) {
            if(cells[moveRow][moveCol]->hasFigure()){
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }
        }
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col - 2));
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
