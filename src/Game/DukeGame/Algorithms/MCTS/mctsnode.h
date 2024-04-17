#ifndef MCTSNODE_H
#define MCTSNODE_H

#include <unordered_map>
#include <vector>
#include <algorithm>

class MCTSNode
{
public:
    MCTSNode();

private:
    State state;
    MCTSNode* parent;
    Action parentAction;
    std::vector<MCTSNode*> children;

    int visits;

    std::unordered_map<int, int> results;
    std::vector<Action> untriedActions;

    std::vector<Action> untriedActions() const;

    int q();
    int n();
    MCTSNode* expand();
    bool isTerminalNode() const;
    double rollout() const;
    void backpropagate(double result);
    bool isFullyExpanded() const;
    MCTSNode* bestChild(double cParam) const;
    int rolloutPolicy(const std::vector<int>& possibleMoves) const;
    MCTSNode* treePolicy();
    MCTSNode* bestAction();


};

#endif // MCTSNODE_H
