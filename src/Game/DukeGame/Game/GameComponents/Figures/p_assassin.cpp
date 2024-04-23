#include "p_assassin.h"


p_Assassin::p_Assassin(PlayerTeam team)
    : Figure(team, Assassin)
{}

Figure::MoveResult p_Assassin::markAvailableJumps(GameState state) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;

    QPair<int,int> currentPosition = QPair<int, int>(row, col);

    int maxRow = (direction == 1) ? 6 : 0;
    int minRow = (direction == 1) ? 0 : 6;

    if(!flipped){
        for (int moveRow = row + 1 * direction; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow); moveRow += 1 * direction) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][col];
            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row - 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol >= 0; moveRow -= 1 * direction, --moveCol) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][col];

            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row - 1 * direction, moveCol = col + 1; (direction == 1 ? moveRow >= minRow : moveRow < minRow) && moveCol < 6; moveRow -= 1 * direction, ++moveCol) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][moveCol];

            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }

        }

    }
    else{
        for (int moveRow = row - 1 * direction; (direction == 1 ? moveRow >= minRow : moveRow < minRow); moveRow -= 1 * direction) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][col];

            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, col));
            }
        }
        // Check diagonal backward moves
        for (int moveRow = row + 1 * direction, moveCol = col - 1; (direction == 1 ? moveRow < maxRow : moveRow >= maxRow) && moveCol >= 0; moveRow += 1 * direction, --moveCol) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][moveCol];

            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
        for (int moveRow = row + 1 * direction, moveCol = col + 1;(direction == 1 ? moveRow < maxRow : moveRow >= maxRow) && moveCol < 6; moveRow += 1 * direction, ++moveCol) {
            PieceType Ptype;
            PlayerTeam Pteam;
            bool Pflipped;
            std::tie(Ptype, Pteam, Pflipped) = state.board[moveRow][moveCol];

            if(Ptype != NoPiece){
                if(Pteam != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
                }
                continue;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(JumpSlide, moveRow, moveCol));
            }
        }
    }
    return{currentPosition, validMoves};
}
























