#include "p_general.h"

p_General::p_General(PlayerTeam team)
    : Figure(team, General)
{}



Figure::MoveResult p_General::markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;
    int col = cell->getCol();
    int row = cell->getRow();
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));

        if(col < 5 && cells[row][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
        }
        if(col > 0 && cells[row][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));
    }
    else{

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));

        if(col < 5 && cells[row][col + 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
        }
        if(col > 0 && cells[row][col - 1]->hasFigure() == false){
            validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));


        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row - 1 * direction, col - 1));
    }
    bool hasCommandFrom = false; // Flag to track existence of CommandFrom
    for (auto move = validMoves.begin(); move != validMoves.end();) {
        int targetRow = std::get<1>(*move);
        int targetCol = std::get<2>(*move);


        if(targetRow >= 6 || targetCol >= 6 || targetRow < 0 || targetCol < 0){
            move = validMoves.erase(move);
        }
        else if(std::get<0>(*move) == Command){
            if(cells[targetRow][targetCol]->hasFigure()){
                if(cells[targetRow][targetCol]->getFigure()->getTeam() == this->team){
                    std::get<0>(*move) = CommandFrom;
                    hasCommandFrom = true; // Set flag if CommandFrom is found
                }
                else{
                    std::get<0>(*move) = CommandTo;
                }
            }
            else{
                std::get<0>(*move) = CommandTo;
            }
            ++move;
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
    // Remove all CommandTo moves if no CommandFrom exists
    if (!hasCommandFrom) {
        for (auto it = validMoves.begin(); it != validMoves.end();) {
            if (std::get<0>(*it) == CommandTo) {
                it = validMoves.erase(it);
            } else {
                ++it;
            }
        }
    }

    return{currentPosition, validMoves};
}
