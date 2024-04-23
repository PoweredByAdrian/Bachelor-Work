#include "p_seer.h"

p_Seer::p_Seer(PlayerTeam team)
    : Figure(team, Seer)
{}


Figure::MoveResult p_Seer::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    QList<std::tuple<MoveTypes,int,int>> validMoves;

    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col - 2));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col - 2));

        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
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



















