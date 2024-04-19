#ifndef MCTSNODE_H
#define MCTSNODE_H

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../../Game/figure.h"
#include "../../Game/movesimulator.h"
#include "Action.h"

class MCTSNode
{
public:
    MCTSNode(MoveSimulator::BoardState state, Action parentAction, MCTSNode* parent);
    MCTSNode* bestAction();
    Action parentAction;
private:

    MoveSimulator::BoardState state;
    MCTSNode* parent;
    std::vector<MCTSNode*> children;

    int visits;

    std::unordered_map<int, int> results;
    std::vector<Action> untriedactions;

    std::vector<Action> untriedActions();

    int q();
    int n()const;
    MCTSNode* expand();
    bool isTerminalNode() const;
    double rollout() const;
    void backpropagate(double result);
    bool isFullyExpanded() const;
    MCTSNode* bestChild(double cParam) const;
    Action rolloutPolicy(const std::vector<Action>& possibleMoves) const;
    MCTSNode* treePolicy();


    MoveSimulator* ms;

};

#endif // MCTSNODE_H
