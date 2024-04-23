#include "p_footman.h"

p_Footman::p_Footman(PlayerTeam team)
    : Figure(team, Footman)
{}



Figure::MoveResult p_Footman::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;


    QList<std::tuple<MoveTypes,int,int>> validMoves;
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));

    }
    else{

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));

        if((direction == 1 ? row != 5 : row != 0)){
            std::tie(Ptype, Pteam, Pflipped) = state.board[row + 1 * direction][col];
            if(Ptype == NoPiece){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col));
            }
        }
    }
    for (int i = validMoves.size() - 1; i >= 0; --i) {
        const auto& move = validMoves[i];
        int targetRow = std::get<1>(move);
        int targetCol = std::get<2>(move);



        if(targetRow >= 6 || targetCol >= 6 || targetRow < 0 || targetCol < 0){
            validMoves.removeAt(i);
            continue;
        }
        else{
            std::tie(Ptype, Pteam, Pflipped) = state.board[targetRow][targetCol];
        }

        if(Ptype != NoPiece){

            if(Pteam == this->team){
                validMoves.removeAt(i);
            }

        }

    }

    return{currentPosition, validMoves};
}
