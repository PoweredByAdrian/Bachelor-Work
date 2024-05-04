#include "expectiminimax.h"


Expectiminimax::Expectiminimax(int maxDepth, PlayerTeam team, bool alphaBeta)
    : maxDepth(maxDepth), myTeam(team), alphaBeta(alphaBeta)

{
    this->ms = new MoveSimulator();
}

FinalMove Expectiminimax::chooseMove(GameState state) {

    // Find the move with the highest score or the best expected score after drawing
    ms->updateBoard(state);
    ms->resetCounter();
    // Initialize variables
    int bestMove = -1;
    bool drawFromBag = false;
    double alpha = -INFINITY;
    double beta = INFINITY;
    double  bestMoveScore = -INFINITY;
    double bestDrawScore = -INFINITY;

    std::pair<int, int> drawPair;

    FinalMove result;

    std::pair<int, int> firstPair;
    std::pair<int, int> secondPair;
    std::pair<int, int> thirdPair;

    // Check if drawing is allowed and beneficial
    QList<QPair<int, int>> drawCells = ms->drawPieceCheck(myTeam);

    if (!drawCells.empty()) {
        for (const auto& cell : drawCells) {

            actualBoard = state;
            ms->updateBoard(state);
            //DEBUG
            //ms->printBoard();

            int x = cell.first;
            int y = cell.second;

            ms->simulateDraw(x, y, actualBoard.currentPlayer);

            actualBoard = ms->getBoard();
            //DEBUG
            //ms->printBoard();

            double drawScore;
            if(actualBoard.currentPlayer == state.currentPlayer){
                if(this->alphaBeta){
                    drawScore = alphabeta(actualBoard, this->maxDepth - 1, alpha, beta, true);
                }
                else{
                   drawScore = expectiminimax(actualBoard, this->maxDepth - 1, true);
                }


            }
            else{

                if(this->alphaBeta){
                    drawScore = alphabeta(actualBoard, this->maxDepth - 1, alpha, beta, false);
                }
                else{
                   drawScore = expectiminimax(actualBoard, this->maxDepth - 1, false);
                }

            }

            if (drawScore > bestDrawScore) {
                bestDrawScore = drawScore;
                drawPair = std::make_pair(x, y);
                this->bestDrawBoard = actualBoard;
            }

            alpha = std::max(alpha, bestDrawScore);
        }

    }

    if((state.currentPlayer == TeamA && state.firstTurnA >=3)||(state.currentPlayer == TeamB && state.firstTurnB >=3)){
        // Consider moving our pieces
        for (int row = 0; row < 6; ++row) {
            for (int col = 0; col < 6; ++col) {

                actualBoard = state;
                ms->updateBoard(state);
                //DEBUG
                //ms->printBoard();
                PieceType Ptype;
                PlayerTeam Pteam;
                bool Pflipped;
                std::tie(Ptype, Pteam, Pflipped) = state.board[row][col];

                // Only consider cells with our pieces
                if (Ptype != NoPiece && Pteam == myTeam) {
                    Figure::MoveResult moves = ms->simulateAndFilterMoves(row, col);

                    for (const auto& move : moves.validMoves) {

                        MoveTypes moveType = std::get<0>(move);
                        int targetRow = std::get<1>(move);
                        int targetCol = std::get<2>(move);

                        if(moveType != CommandTo && moveType != CommandFrom){
                            ms->simulateMove(row, col, targetRow, targetCol, moveType);
                        }



                        this->actualBoard = ms->getBoard();
                        //DEBUG
                        //ms->printBoard();

                        double score;
                        if(this->alphaBeta){
                            score = alphabeta(actualBoard, this->maxDepth - 1, alpha, beta, false);
                        }
                        else{
                            score = expectiminimax(actualBoard, this->maxDepth - 1, false); // Opponent's turn
                        }




                        if (score > bestMoveScore) {
                            bestMoveScore = score;
                            firstPair = std::make_pair(row, col);
                            secondPair = std::make_pair(std::get<1>(move), std::get<2>(move));

                            thirdPair = std::make_pair(-1, -1);
                            this->bestMoveBoard = actualBoard;
                        }

                        alpha = std::max(alpha, bestMoveScore);
                    }
                }
            }
        }
    }


    // Choose the best option: move or draw
    if (bestDrawScore > bestMoveScore) {
        std::pair<int, int> nullPair = std::make_pair(-1, -1);
        result.firstCoord = drawPair;
        result.secondCoord = nullPair;
        result.thirdCoord = nullPair;


    }
    else{
        result.firstCoord = firstPair;
        result.secondCoord = secondPair;
        result.thirdCoord = thirdPair;


    }

    qDebug() << "Number of simulations: " << this->ms->getCounter();
    // Return the chosen move or drawing decision
    return result;
}

double Expectiminimax::expectiminimax(GameState state, int depth, bool isMaximizingPlayer) const {
    // Base case: Terminal state or depth reached

    GameState expectiBoard;

    ms->updateBoard(state);

    if (depth == 0) {
        return evaluateBoard(state);
    }
    //Current player lost
    if(isTerminalState(state)){
        if(isMaximizingPlayer){
            return -INFINITY;
        }
        else{
            return INFINITY;
        }
    }

    // Maximizing player turn
    if (isMaximizingPlayer) {
        // Initialize variables
        int bestMove = -1;
        bool drawFromBag = false;
        double  bestMoveScore = -INFINITY;
        double bestDrawScore = -INFINITY;


        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(state.currentPlayer);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                expectiBoard = state;
                ms->updateBoard(state);
                //DEBUG
                //ms->printBoard();
                int x = cell.first;
                int y = cell.second;


                ms->simulateDraw(x, y, expectiBoard.currentPlayer);

                expectiBoard = ms->getBoard();
                //DEBUG
                //ms->printBoard();



                double drawScore;
                if(expectiBoard.currentPlayer == state.currentPlayer){
                    drawScore = expectiminimax(expectiBoard, depth - 1, true);
                }
                else{
                    drawScore = expectiminimax(expectiBoard, depth - 1, false);
                }

                if (drawScore > bestDrawScore) {
                    bestDrawScore = drawScore;
                }
            }
        }

        if((state.currentPlayer == TeamA && state.firstTurnA >=3)||(state.currentPlayer == TeamB && state.firstTurnB >=3)){
            // Consider moving our pieces
            for (int row = 0; row < 6; ++row) {
                for (int col = 0; col < 6; ++col) {

                    expectiBoard = state;
                    ms->updateBoard(state);
                    //DEBUG
                    //ms->printBoard();
                    PieceType Ptype;
                    PlayerTeam Pteam;
                    bool Pflipped;
                    std::tie(Ptype, Pteam, Pflipped) = state.board[row][col];



                    if (Ptype != NoPiece && Pteam == state.currentPlayer) {
                        Figure::MoveResult moves = ms->simulateAndFilterMoves(row, col);

                        for (const auto& move : moves.validMoves) {

                            MoveTypes moveType = std::get<0>(move);
                            int targetRow = std::get<1>(move);
                            int targetCol = std::get<2>(move);

                            if(moveType != CommandTo && moveType != CommandFrom){
                                ms->simulateMove(row, col, targetRow, targetCol, moveType);
                            }



                            expectiBoard = ms->getBoard();
                            //DEBUG
                            //ms->printBoard();

                            double score = expectiminimax(expectiBoard, depth - 1, false); // Opponent's turn
                            if (score > bestMoveScore) {
                                bestMoveScore = score;
                            }
                        }
                    }
                }
            }
        }
        if (bestDrawScore > bestMoveScore)
        {
            return bestDrawScore;
        }
        return bestMoveScore;
    }

    // Minimizing player turn (similar logic with min instead of max)
    else {
        // Initialize variables
        int bestMove = -1;
        bool drawFromBag = false;
        double  bestMoveScore = INFINITY;
        double bestDrawScore = INFINITY;

        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(state.currentPlayer);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                expectiBoard = state;
                ms->updateBoard(state);
                //DEBUG
                //ms->printBoard();
                int x = cell.first;
                int y = cell.second;


                ms->simulateDraw(x, y, expectiBoard.currentPlayer);

                expectiBoard = ms->getBoard();
                //DEBUG
                //ms->printBoard();


                double drawScore;
                if(expectiBoard.currentPlayer == state.currentPlayer){
                    drawScore = expectiminimax(expectiBoard, depth - 1, false);
                }
                else{
                    drawScore = expectiminimax(expectiBoard, depth - 1, true);
                }

                if (drawScore > bestDrawScore) {
                    bestDrawScore = drawScore;
                }
            }
        }
        if((state.currentPlayer == TeamA && state.firstTurnA >=3)||(state.currentPlayer == TeamB && state.firstTurnB >=3)){
            for (int row = 0; row < 6; ++row) {
                for (int col = 0; col < 6; ++col) {

                    expectiBoard = state;
                    ms->updateBoard(state);
                    //DEBUG
                    //ms->printBoard();
                    PieceType Ptype;
                    PlayerTeam Pteam;
                    bool Pflipped;
                    std::tie(Ptype, Pteam, Pflipped) = state.board[row][col];



                    if (Ptype != NoPiece && Pteam == state.currentPlayer) {
                        Figure::MoveResult moves = ms->simulateAndFilterMoves(row, col);

                        for (const auto& move : moves.validMoves) {

                            MoveTypes moveType = std::get<0>(move);
                            int targetRow = std::get<1>(move);
                            int targetCol = std::get<2>(move);

                            if(moveType != CommandTo && moveType != CommandFrom){
                                ms->simulateMove(row, col, targetRow, targetCol, moveType);
                            }



                            expectiBoard = ms->getBoard();
                            //DEBUG
                            //ms->printBoard();


                            double score = expectiminimax(expectiBoard, depth - 1, true); // Opponent's turn
                            if (score < bestMoveScore) {
                                bestMoveScore = score;
                            }
                        }
                    }
                }
            }
        }
        if (bestDrawScore < bestMoveScore)
        {
            return bestDrawScore;
        }
        return bestMoveScore;
    }
}

double Expectiminimax::alphabeta(GameState state, int depth, double alpha, double beta, bool isMaximizingPlayer) const {
    // Base case: Terminal state or depth reached

    GameState expectiBoard;

    ms->updateBoard(state);

    if (depth == 0) {
        return evaluateBoard(state);
    }
    //Current player lost
    if(isTerminalState(state)){
        if(isMaximizingPlayer){
            return -INFINITY;
        }
        else{
            return INFINITY;
        }
    }

    // Maximizing player turn
    if (isMaximizingPlayer) {
        // Initialize variables
        int bestMove = -1;
        bool drawFromBag = false;
        double  bestMoveScore = -INFINITY;
        double bestDrawScore = -INFINITY;

        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(state.currentPlayer);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                expectiBoard = state;
                ms->updateBoard(state);
                //DEBUG
                //ms->printBoard();
                int x = cell.first;
                int y = cell.second;


                ms->simulateDraw(x, y, expectiBoard.currentPlayer);

                expectiBoard = ms->getBoard();
                //DEBUG
                //ms->printBoard();




                if(expectiBoard.currentPlayer == state.currentPlayer){


                        bestDrawScore = std::max(bestDrawScore, alphabeta(actualBoard, depth - 1, alpha, beta, true));
                        alpha = std::max(alpha, bestDrawScore);
                        if (beta <= alpha) {
                            break; // Beta cut-off
                        }




                }
                else{


                        bestDrawScore = std::max(bestDrawScore, alphabeta(actualBoard, depth - 1, alpha, beta, false));
                        alpha = std::max(alpha, bestDrawScore);
                        if (beta <= alpha) {
                            break; // Beta cut-off
                        }




                }


            }
        }

        if((state.currentPlayer == TeamA && state.firstTurnA >=3)||(state.currentPlayer == TeamB && state.firstTurnB >=3)){
            // Consider moving our pieces
            for (int row = 0; row < 6; ++row) {
                for (int col = 0; col < 6; ++col) {

                    expectiBoard = state;
                    ms->updateBoard(state);
                    //DEBUG
                    //ms->printBoard();
                    PieceType Ptype;
                    PlayerTeam Pteam;
                    bool Pflipped;
                    std::tie(Ptype, Pteam, Pflipped) = state.board[row][col];



                    if (Ptype != NoPiece && Pteam == state.currentPlayer) {
                        Figure::MoveResult moves = ms->simulateAndFilterMoves(row, col);

                        for (const auto& move : moves.validMoves) {

                            MoveTypes moveType = std::get<0>(move);
                            int targetRow = std::get<1>(move);
                            int targetCol = std::get<2>(move);

                            if(moveType != CommandTo && moveType != CommandFrom){
                                ms->simulateMove(row, col, targetRow, targetCol, moveType);
                            }



                            expectiBoard = ms->getBoard();
                            //DEBUG
                            //ms->printBoard();

                                bestMoveScore = std::max(bestMoveScore, alphabeta(actualBoard, depth - 1, alpha, beta, false));
                                alpha = std::max(alpha, bestMoveScore);
                                if (beta <= alpha) {
                                    break; // Beta cut-off
                                }


                        }
                    }
                }
            }
        }
        if (bestDrawScore > bestMoveScore)
        {
            return bestDrawScore;
        }
        return bestMoveScore;
    }

    // Minimizing player turn (similar logic with min instead of max)
    else {
        // Initialize variables
        int bestMove = -1;
        bool drawFromBag = false;
        double  bestMoveScore = INFINITY;
        double bestDrawScore = INFINITY;

        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(state.currentPlayer);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                expectiBoard = state;
                ms->updateBoard(state);
                //DEBUG
                //ms->printBoard();
                int x = cell.first;
                int y = cell.second;


                ms->simulateDraw(x, y, expectiBoard.currentPlayer);

                expectiBoard = ms->getBoard();
                //DEBUG
                //ms->printBoard();


                double drawScore;
                if(expectiBoard.currentPlayer == state.currentPlayer){


                        bestDrawScore = std::min(bestDrawScore, alphabeta(actualBoard, depth - 1, alpha, beta, false));
                        beta = std::min(beta, bestDrawScore);
                        if (beta <= alpha) {
                            break; // Alpha  cut-off
                        }


                }
                else{

                        bestDrawScore = std::min(bestDrawScore, alphabeta(actualBoard, depth - 1, alpha, beta, true));
                        beta = std::min(beta, bestDrawScore);
                        if (beta <= alpha) {
                            break; // Alpha  cut-off
                        }




                }



            }
        }
        if((state.currentPlayer == TeamA && state.firstTurnA >=3)||(state.currentPlayer == TeamB && state.firstTurnB >=3)){
            for (int row = 0; row < 6; ++row) {
                for (int col = 0; col < 6; ++col) {

                    expectiBoard = state;
                    ms->updateBoard(state);
                    //DEBUG
                    //ms->printBoard();
                    PieceType Ptype;
                    PlayerTeam Pteam;
                    bool Pflipped;
                    std::tie(Ptype, Pteam, Pflipped) = state.board[row][col];



                    if (Ptype != NoPiece && Pteam == state.currentPlayer) {
                        Figure::MoveResult moves = ms->simulateAndFilterMoves(row, col);

                        for (const auto& move : moves.validMoves) {

                            MoveTypes moveType = std::get<0>(move);
                            int targetRow = std::get<1>(move);
                            int targetCol = std::get<2>(move);

                            if(moveType != CommandTo && moveType != CommandFrom){
                                ms->simulateMove(row, col, targetRow, targetCol, moveType);
                            }



                            expectiBoard = ms->getBoard();
                            //DEBUG
                            //ms->printBoard();

                                bestMoveScore = std::min(bestMoveScore, alphabeta(actualBoard, depth - 1, alpha, beta, false));
                                beta = std::min(beta, bestMoveScore);
                                if (beta <= alpha) {
                                    break; // Alpha  cut-off
                                }







                        }
                    }
                }
            }
        }
        if (bestDrawScore < bestMoveScore)
        {
            return bestDrawScore;
        }
        return bestMoveScore;
    }
}

double Expectiminimax::evaluateBoard(GameState state) const {
    // Define weights for each piece type
    const double dukeWeight = 300.0;
    const double footmanWeight = 30.0;
    const double assassinWeight = 100.0;
    const double bowmannWeight = 50.0;
    const double championWeight = 100.0;
    const double dracoonWeight = 50.0;
    const double generalWeight = 100.0;
    const double knightWeight = 50.0;
    const double marshallWeight = 115.0;
    const double pikemanWeight = 40.0;
    const double priestWeight = 100.0;
    const double seerWeight = 70.0;
    const double longbowmanWeight = 100.0;
    const double wizardWeight = 100.0;
    // Add weights for other piece types as needed

    double score = 0.0;

    // Loop through the board and count pieces
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            PieceType type;
            PlayerTeam team;
            bool flipped;
            std::tie(type, team, flipped) = state.board[row][col];

            int multi = 1;
            if(flipped){
                multi = 2;
            }
            // Add score based on piece type
            switch (type) {
            case Duke:

                if(team == this->myTeam){
                   score += dukeWeight;
                }
                else{
                    score -= 2 * dukeWeight;
                }

                break;
            case Footman:
                if(team == this->myTeam){
                    score += footmanWeight;
                }
                else{
                    score -= 2 * footmanWeight;
                }
                break;
            case Assassin:
                if(team == this->myTeam){
                    score += assassinWeight;
                }
                else{
                    score -= 2 * assassinWeight;
                }
                break;
            case Bowman:
                if(team == this->myTeam){
                    score += bowmannWeight;
                }
                else{
                    score -= 2 * bowmannWeight;
                }
                break;
            case Champion:
                if(team == this->myTeam){
                    score += championWeight;
                }
                else{
                    score -= 2 * championWeight;
                }
                break;
            case Dracoon:
                if(team == this->myTeam){
                    score += dracoonWeight;
                }
                else{
                    score -= 2 * dracoonWeight;
                }
                break;
            case General:
                if(team == this->myTeam){
                    score += generalWeight * multi;
                }
                else{
                    score -= 2 * generalWeight * multi;
                }
                break;
            case Knight:
                if(team == this->myTeam){
                    score += knightWeight * multi;
                }
                else{
                    score -= 2 * knightWeight * multi;
                }
                break;
            case Marshall:
                if(team == this->myTeam){
                    score += marshallWeight * multi;
                }
                else{
                    score -= 2 * marshallWeight * multi;
                }
                break;
            case Pikeman:
                if(team == this->myTeam){
                    score += pikemanWeight;
                }
                else{
                    score -= 2 * pikemanWeight;
                }
                break;
            case Priest:
                if(team == this->myTeam){
                    score += priestWeight;
                }
                else{
                    score -= 2 * priestWeight;
                }
                break;
            case Seer:
                if(team == this->myTeam){
                    score += seerWeight;
                }
                else{
                    score -= 2 * seerWeight;
                }
                break;
            case Longbowman:
                if(team == this->myTeam){
                    score += longbowmanWeight;
                }
                else{
                    score -= 2 * longbowmanWeight;
                }
                break;
            case Wizard:
                if(team == this->myTeam){
                    score += wizardWeight;
                }
                else{
                    score -= 2 * wizardWeight;
                }
                break;
            // Add cases for other piece types
            default:
                break;
            }
        }
    }

    if(this->myTeam == TeamA){
        score += state.playerABag.size() * 10;
        score -= state.playerBBag.size() * 10;
    }
    else if(this->myTeam == TeamB){
        score += state.playerBBag.size() * 10;
        score -= state.playerABag.size() * 10;
    }

    if(state.playerA_UnderGuard && this->myTeam == TeamA){
        score -= 500;
    }
    else if(state.playerB_UnderGuard && this->myTeam == TeamB){
        score -= 500;
    }else if(state.playerB_UnderGuard && this->myTeam == TeamA){
        score += 1000;
    }
    else if(state.playerA_UnderGuard && this->myTeam == TeamB){
        score += 1000;
    }

    return score;
}

bool Expectiminimax::isTerminalState(GameState state) const {
    return ms->endGameCheck(state, true);

}
