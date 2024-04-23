#include "p_marshall.h"

p_Marshall::p_Marshall(PlayerTeam team)
    : Figure(team, Marshall)
{}



Figure::MoveResult p_Marshall::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    QList<std::tuple<MoveTypes,int,int>> validMoves;
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        for (int moveCol = col - 1; moveCol >= 0; --moveCol) {
            std::tie(Ptype, Pteam, Pflipped) = state.board[row][moveCol];
            if(Ptype != NoPiece){
                if(Pteam != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }
        }
        for (int moveCol = col + 1; moveCol < 6; ++moveCol) {
            std::tie(Ptype, Pteam, Pflipped) = state.board[row][moveCol];
            if(Ptype != NoPiece){
                if(Pteam != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }
        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2 * direction, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));

        if(col < 5){
            std::tie(Ptype, Pteam, Pflipped) = state.board[row][col + 1];
            if(Ptype == NoPiece){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 2));
            }
        }
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        if(col > 0){

            std::tie(Ptype, Pteam, Pflipped) = state.board[row][col - 1];
            if(Ptype == NoPiece){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 2));
            }

        }

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Command, row + 1 * direction, col - 1));
    }
    bool hasCommandFrom = false; // Flag to track existence of CommandFrom
    bool hasCommandTo = false; // Flag to track existence of CommandTo

    for (auto move = validMoves.begin(); move != validMoves.end();) {
        int targetRow = std::get<1>(*move);
        int targetCol = std::get<2>(*move);


        if(targetRow >= 6 || targetCol >= 6 || targetRow < 0 || targetCol < 0){
            move = validMoves.erase(move);
            continue;
        }
        else{
            std::tie(Ptype, Pteam, Pflipped) = state.board[targetRow][targetCol];
        }

        if(std::get<0>(*move) == Command){
            if(Ptype != NoPiece){
                if(Pteam == this->team){
                    std::get<0>(*move) = CommandFrom;
                    hasCommandFrom = true; // Set flag if CommandFrom is found
                }
                else{
                    std::get<0>(*move) = CommandTo;
                    hasCommandTo = true;
                }
            }
            else{
                std::get<0>(*move) = CommandTo;
                hasCommandTo = true;
            }
        }
        else if(Ptype != NoPiece){
            if(Pteam == this->team){
                move = validMoves.erase(move);
                continue;
            }

        }
        ++move; // Increment move


    }

    // Remove all CommandTo moves if no CommandFrom exists
    if (!hasCommandFrom || !hasCommandTo) {
        for (auto it = validMoves.begin(); it != validMoves.end();) {
            if (std::get<0>(*it) == CommandTo || std::get<0>(*it) == CommandFrom) {
                it = validMoves.erase(it);
            } else {
                ++it;
            }
        }
    }

    return{currentPosition, validMoves};
}
