#include "expectiminimax.h"

Expectiminimax::Expectiminimax(int maxDepth, PlayerTeam team)
    : maxDepth(maxDepth), myTeam(team)

{
    this->ms = new MoveSimulator();
}

MoveSimulator::finalMove Expectiminimax::chooseMove(GameConfigure* gc) {

    this->gc = gc;
    // Find the move with the highest score or the best expected score after drawing
    ms->updateBoard(gc);
    std::vector<std::vector<CellInfo>> board = ms->getBoard();
    // Initialize variables
    int bestMove = -1;
    bool drawFromBag = false;
    double  bestMoveScore = -INFINITY;
    double bestDrawScore = -INFINITY;

    std::pair<int, int> drawPair;

    MoveSimulator::finalMove result;

    std::pair<int, int> firstPair;
    std::pair<int, int> secondPair;
    std::pair<int, int> thirdPair;

    // Check if drawing is allowed and beneficial
    QList<QPair<int, int>> drawCells = ms->drawPieceCheck(myTeam);

    if (!drawCells.empty()) {
        for (const auto& cell : drawCells) {
            ;
            int x = cell.first;
            int y = cell.second;

            // Place the piece on the cell and evaluate the board
            MoveSimulator::BoardState newConfig /* TODO simulate place cell on board= ms->placePieceOnCell(x, y, myTeam)*/;
            double drawScore = evaluateBoard(newConfig);

            if (drawScore > bestDrawScore) {
                bestDrawScore = drawScore;
                drawPair = std::make_pair(x, y);
            }
        }

    }

    // Consider moving our pieces
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            // Only consider cells with our pieces
            if (gc->getCell(row, col)->hasFigure() && gc->getCell(row, col)->getFigure()->getTeam() == myTeam) {
                Figure::MoveResult moves = ms->simulateAndFilterMoves(gc->getCell(row, col)->getFigure());

                for (const auto& move : moves.validMoves) {
                    MoveSimulator::BoardState nb = ms->loadBoard(gc);
                    MoveSimulator::BoardState newBoard = ms->simulateMove(row, col, nb.simBoard, move);
                    double score = expectiminimax(newBoard, this->maxDepth - 1, false); // Opponent's turn
                    if (score > bestMoveScore) {
                        bestMoveScore = score;
                        firstPair = std::make_pair(row, col);
                        secondPair = std::make_pair(std::get<1>(move), std::get<2>(move));
                        //TODO command
                        thirdPair = std::make_pair(-1, -1);
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

    // Return the chosen move or drawing decision
    return result;
}

double Expectiminimax::expectiminimax(MoveSimulator::BoardState board, int depth, bool isMaximizingPlayer) const {
    // Base case: Terminal state or depth reached
    //TODO isTerminal
    if (depth == 0 || isTerminalState(board)) {
        return evaluateBoard(board);
    }

    // Maximizing player turn
    if (isMaximizingPlayer) {
        double bestScore = -INFINITY;
        double bestDrawScore = -INFINITY;

        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(myTeam);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                ;
                int x = cell.first;
                int y = cell.second;

                // Place the piece on the cell and evaluate the board
                MoveSimulator::BoardState newConfig /* TODO simulate place cell on board= ms->placePieceOnCell(x, y, myTeam)*/;
                double drawScore = evaluateBoard(newConfig);

                if (drawScore > bestDrawScore) {
                    bestDrawScore = drawScore;
                }
            }

        }

        // Consider moving our pieces
        for (int row = 0; row < 6; ++row) {
            for (int col = 0; col < 6; ++col) {
                // Only consider cells with our pieces
                if (gc->getCell(row, col)->hasFigure() && gc->getCell(row, col)->getFigure()->getTeam() == myTeam) {
                    Figure::MoveResult moves = ms->simulateAndFilterMoves(gc->getCell(row, col)->getFigure());

                    for (const auto& move : moves.validMoves) {
                        MoveSimulator::BoardState newBoard = ms->simulateMove(row, col, board.simBoard, move);
                        double  score = expectiminimax(newBoard, this->maxDepth - 1, false); // Opponent's turn
                        if (score > bestScore) {
                            bestScore = score;
                        }
                    }
                }
            }
        }
        if (bestDrawScore > bestScore)
        {
            return bestDrawScore;
        }
        return bestScore;
    }

    // Minimizing player turn (similar logic with min instead of max)
    else {
        double bestScore = INFINITY;
        double bestDrawScore = INFINITY;
        // Check if drawing is allowed and beneficial
        QList<QPair<int, int>> drawCells = ms->drawPieceCheck(myTeam);

        if (!drawCells.empty()) {
            for (const auto& cell : drawCells) {
                ;
                int x = cell.first;
                int y = cell.second;

                // Place the piece on the cell and evaluate the board
                MoveSimulator::BoardState newConfig /* TODO simulate place cell on board= ms->placePieceOnCell(x, y, myTeam)*/;
                double drawScore = evaluateBoard(newConfig);

                if (drawScore < bestDrawScore) {
                    bestDrawScore = drawScore;
                }
            }

        }
        for (int row = 0; row < 6; ++row) {
            for (int col = 0; col < 6; ++col) {
                // Only consider cells with our pieces
                if (gc->getCell(row, col)->hasFigure() && gc->getCell(row, col)->getFigure()->getTeam() != myTeam) {
                    Figure::MoveResult moves = ms->simulateAndFilterMoves(gc->getCell(row, col)->getFigure());

                    for (const auto& move : moves.validMoves) {
                        MoveSimulator::BoardState newBoard = ms->simulateMove(row, col, board.simBoard, move);
                        int score = expectiminimax(newBoard, this->maxDepth - 1, true); // Opponent's turn
                        if (score < bestScore) {
                            bestScore = score;
                        }
                    }
                }
            }
        }
        if (bestDrawScore < bestScore)
        {
            return bestDrawScore;
        }
        return bestScore;
    }
}

double Expectiminimax::evaluateBoard(MoveSimulator::BoardState board) const {
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

bool Expectiminimax::isTerminalState(MoveSimulator::BoardState board) const {
    return false;
}
