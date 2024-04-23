#include "p_champion.h"

p_Champion::p_Champion(PlayerTeam team)
    : Figure(team, Champion)
{}



Figure::MoveResult p_Champion::markAvailableJumps(GameState state) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;

    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 1, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row - 1, col));

        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row, col - 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row - 2, col));
    }


    for (int i = validMoves.size() - 1; i >= 0; --i) {
        const auto& move = validMoves[i];
        MoveTypes type = std::get<0>(move);
        int targetRow = std::get<1>(move);
        int targetCol = std::get<2>(move);

        PieceType Ptype;
        PlayerTeam Pteam;
        bool Pflipped;


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
