#include "p_longbowman.h"

p_Longbowman::p_Longbowman(PlayerTeam team)
    : Figure(team, Longbowman)
{}



Figure::MoveResult p_Longbowman::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    QList<std::tuple<MoveTypes,int,int>> validMoves;
    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 3 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col));
    }

    for (int i = validMoves.size() - 1; i >= 0; --i) {
        const auto& move = validMoves[i];
        MoveTypes type = std::get<0>(move);
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
        else if(type == Strike && Ptype == NoPiece){
            validMoves.removeAt(i);
        }

    }
    return{currentPosition, validMoves};
}
