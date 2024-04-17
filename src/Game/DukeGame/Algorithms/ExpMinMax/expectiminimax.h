#ifndef EXPECTIMINIMAX_H
#define EXPECTIMINIMAX_H

#include "../../Game/GameConfigure.h"
#include "../../Game/movesimulator.h"
#include <random>


class Expectiminimax
{
public:

    Expectiminimax(int maxDepth, PlayerTeam team);
    MoveSimulator::finalMove chooseMove(GameConfigure* gc);

private:
    double expectiminimax(MoveSimulator::BoardState board, int depth, bool isMaximizingPlayer) const;
    double evaluateBoard(MoveSimulator::BoardState board) const;
    bool isTerminalState(MoveSimulator::BoardState board) const;

    GameConfigure* gc;
    int maxDepth;
    PlayerTeam myTeam;
    MoveSimulator* ms;
};

#endif // EXPECTIMINIMAX_H
