#include "p_priest.h"

p_Priest::p_Priest(PlayerTeam team)
    : Figure(team, Priest)
{}



Figure::MoveResult p_Priest::markAvailableJumps(GameState state) const
{
    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    QList<std::tuple<MoveTypes,int,int>> validMoves;

    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){

        // Check diagonal backward moves
        for (int moveRow = row - 1, moveCol = col - 1; moveRow >= 0 && moveCol >= 0; --moveRow, --moveCol) {
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
        for (int moveRow = row - 1, moveCol = col + 1; moveRow >= 0 && moveCol < 6; --moveRow, ++moveCol) {
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
        // Check diagonal forward moves
        for (int moveRow = row + 1, moveCol = col - 1; moveRow < 6 && moveCol >= 0; ++moveRow, --moveCol) {
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
        for (int moveRow = row + 1, moveCol = col + 1; moveRow < 6 && moveCol < 6; ++moveRow, ++moveCol) {
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
