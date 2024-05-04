#ifndef EXPECTIMINIMAX_H
#define EXPECTIMINIMAX_H

#include "../../Game/movesimulator.h"
#include "../../Game/GameComponents/GameState.h"
#include <random>
#include <algorithm>

#include "../FinalMove.h"

class Expectiminimax
{
public:

    Expectiminimax(int maxDepth, PlayerTeam team, bool alphaBeta = false);
    ~Expectiminimax(){delete ms;};
    FinalMove chooseMove(GameState state);

private:
    double expectiminimax(GameState state, int depth, bool isMaximizingPlayer) const;
    double alphabeta(GameState state, int depth, double alpha, double beta, bool isMaximizingPlayer) const;
    double evaluateBoard(GameState state) const;
    bool isTerminalState(GameState state) const;

    GameState actualBoard;
    GameState bestDrawBoard;
    GameState bestMoveBoard;

    int maxDepth;
    PlayerTeam myTeam;
    MoveSimulator* ms;
    bool alphaBeta;
};

#endif // EXPECTIMINIMAX_H
