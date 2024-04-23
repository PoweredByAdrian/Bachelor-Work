#include "expectiminimax.h"

Expectiminimax::Expectiminimax(int maxDepth, PlayerTeam team)
    : maxDepth(maxDepth), myTeam(team)

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
            ms->printBoard();

            double drawScore;
            if(actualBoard.currentPlayer == state.currentPlayer){
                drawScore = expectiminimax(actualBoard, this->maxDepth - 1, true);
            }
            else{           
                drawScore = expectiminimax(actualBoard, this->maxDepth - 1, false);
            }

            if (drawScore > bestDrawScore) {
                bestDrawScore = drawScore;
                drawPair = std::make_pair(x, y);
                this->bestDrawBoard = actualBoard;
            }
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
                        //TODO finish command


                        this->actualBoard = ms->getBoard();
                        //DEBUG
                        ms->printBoard();

                        double score = expectiminimax(actualBoard, this->maxDepth - 1, false); // Opponent's turn
                        if (score > bestMoveScore) {
                            bestMoveScore = score;
                            firstPair = std::make_pair(row, col);
                            secondPair = std::make_pair(std::get<1>(move), std::get<2>(move));
                            //TODO command
                            thirdPair = std::make_pair(-1, -1);
                            this->bestMoveBoard = actualBoard;
                        }
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

        //TODO Print bestDrawBoard
    }
    else{
        result.firstCoord = firstPair;
        result.secondCoord = secondPair;
        result.thirdCoord = thirdPair;

        //TOTO Print bestMoveBoard
    }

    // Return the chosen move or drawing decision
    return result;
}

double Expectiminimax::expectiminimax(GameState state, int depth, bool isMaximizingPlayer) const {
    // Base case: Terminal state or depth reached

    GameState expectiBoard;

    ms->updateBoard(state);
    //TODO isTerminal
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
                ms->printBoard();



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
                            //TODO finish command


                            expectiBoard = ms->getBoard();
                            //DEBUG
                            ms->printBoard();

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
                ms->printBoard();


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
                            //TODO finish command


                            expectiBoard = ms->getBoard();
                            //DEBUG
                            ms->printBoard();


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

double Expectiminimax::evaluateBoard(GameState state) const {
    // Initialize score
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range for the random double
    double min = -1000.0;
    double max = 1000.0;
    std::uniform_real_distribution<double> dis(min, max);

    // Generate a random double
    double score = dis(gen);
    //#################################################################################




    return score;
}

bool Expectiminimax::isTerminalState(GameState state) const {
    return ms->endGameCheck(state);

}
