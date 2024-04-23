#include "p_knight.h"

p_Knight::p_Knight(PlayerTeam team)
    : Figure(team, Knight)
{}



Figure::MoveResult p_Knight::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    QList<std::tuple<MoveTypes,int,int>> validMoves;
    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col));

        if(direction == 1 && row != 0 || direction == -1 && row != 5){
            std::tie(Ptype, Pteam, Pflipped) = state.board[row - 1 * direction][col];
            if(Ptype == NoPiece){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col));
            }
        }



        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));
    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col - 1));


        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 1 * direction, col + 1));


        if(direction == 1 && row != 0 || direction == -1 && row != 5){
            if(col > 0){
                std::tie(Ptype, Pteam, Pflipped) = state.board[row - 1 * direction][col - 1];
                if(Ptype == NoPiece){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col - 2));
                }
            }
            if(col < 5){
                std::tie(Ptype, Pteam, Pflipped) = state.board[row - 1 * direction][col + 1];
                if(Ptype == NoPiece){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Move, row - 2 * direction, col + 2));
                }
            }
        }


        for (int moveRow = row + 1 * direction; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow); moveRow += 1 * direction) {
            std::tie(Ptype, Pteam, Pflipped) = state.board[moveRow][col];

            if(Ptype != NoPiece){
                if(Pteam != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
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
