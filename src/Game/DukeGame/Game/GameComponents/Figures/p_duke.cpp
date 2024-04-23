#include "p_duke.h"

p_Duke::p_Duke(PlayerTeam team)
    : Figure(team, Duke)
{}


Figure::MoveResult p_Duke::markAvailableJumps(GameState state) const
{
    QList<std::tuple<MoveTypes,int,int>> validMoves;


    QPair<int,int> currentPosition = QPair<int, int>(row, col);
    if(!flipped){
        for (int moveCol = col - 1; moveCol >= 0; --moveCol) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[row][moveCol];
            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }

        }
        for (int moveCol = col + 1; moveCol < 6; ++moveCol) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[row][moveCol];
            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, row, moveCol));
            }

        }
    }
    else{
        for (int moveRow = row - 1; moveRow >= 0; --moveRow) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][col];
            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
        for (int moveRow = row + 1; moveRow < 6; ++moveRow) {
            PieceType type;
            PlayerTeam team;
            bool Pflipped;
            std::tie(type, team, Pflipped) = state.board[moveRow][col];
            if(type != NoPiece){
                if(team != this->team){
                    validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
                }
                break;
            }
            else{
                validMoves.append(std::tuple<MoveTypes,int,int>(Slide, moveRow, col));
            }

        }
    }
    return{currentPosition, validMoves};
}

QList<QPair<int, int>> p_Duke::getPlacableCellsForNewPiece(GameState state){
    QList<QPair<int, int>> result;
    if(team == TeamA){
        if(row == -1 || col == -1){
            result.append(QPair<int, int>(0, 2));
            result.append(QPair<int, int>(0, 3));
            return result;
        }
        if(state.playerABag.empty()){
            result.clear();
            return result;
        }
    }
    else{
        if(row == -1 || col == -1){
            result.append(QPair<int, int>(5, 2));
            result.append(QPair<int, int>(5, 3));
            return result;
        }
        if(state.playerBBag.empty()){
            result.clear();
            return result;
        }
    }

    result.append(QPair<int, int>(row, col + 1));
    result.append(QPair<int, int>(row, col - 1));
    result.append(QPair<int, int>(row + 1, col));
    result.append(QPair<int, int>(row - 1, col));

    for (int i = result.size() - 1; i >= 0; --i) {
        const auto& move = result[i];
        int targetRow = std::get<0>(move);
        int targetCol = std::get<1>(move);

        PieceType type;
        PlayerTeam Pteam;
        bool Pflipped;


        // Check if the target cell is within the board bounds [0, 6)
        if (targetRow >= 0 && targetRow < 6 && targetCol >= 0 && targetCol < 6) {
            std::tie(type, Pteam, Pflipped) = state.board[targetRow][targetCol];
            // Check if the target cell has a figure
            if (type != NoPiece) {
                result.removeAt(i);
            }
        } else {
            // If the target cell is outside the board, remove the move
            result.removeAt(i);
        }
    }

    return result;
}

























