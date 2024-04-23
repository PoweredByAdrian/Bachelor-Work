#include "p_dracoon.h"

p_Dracoon::p_Dracoon(PlayerTeam team)
    : Figure(team, Dracoon)
{}



Figure::MoveResult p_Dracoon::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;


    QList<std::tuple<MoveTypes,int,int>> validMoves;

    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col +1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row, col - 1));

        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col + 2));
        validMoves.append(std::tuple<MoveTypes,int,int>(Strike, row + 2 * direction, col - 2));

    }
    else{
        validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 1 * direction, col));      
        if((direction == 1 ? row != 5 : row != 0)){
            std::tie(Ptype, Pteam, Pflipped) = state.board[row + 1 * direction][col];
            if(Ptype == NoPiece){
                validMoves.append(std::tuple<MoveTypes,int,int>(Move, row + 2 * direction, col));
            }
        }


        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col + 1));
        validMoves.append(std::tuple<MoveTypes,int,int>(Jump, row + 2 * direction, col - 1));

        // Check diagonal backward moves
        for (int moveRow = row - 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol >= 0; moveRow -= 1 * direction, --moveCol) {
            std::tie(Ptype, Pteam, Pflipped) = state.board[moveRow][moveCol];

            if(Ptype != NoPiece){
                if(Pteam != this->team){
                   validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }

        }

        for (int moveRow = row - 1 * direction, moveCol = col + 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol < 6; moveRow -= 1 * direction, ++moveCol) {
            std::tie(Ptype, Pteam, Pflipped) = state.board[moveRow][moveCol];

            if(Ptype != NoPiece){
                if(Pteam != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, moveCol));
            }

        }
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
