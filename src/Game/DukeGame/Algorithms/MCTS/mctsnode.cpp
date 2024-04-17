#include "mctsnode.h"
#include <limits>

MCTSNode::MCTSNode(State state, MCTSNode* parent = nullptr, Action parentAction = nullptr)
    : state(state), parent(parent), parentAction(parentAction)  {

    this->children.clear();
    this->visits = 0;
    results[1] = 0;
    results[-1] = 0;
    untriedActions = untriedActions();
}

std::vector<Action> MCTSNode::untriedActions() const {

    this->untriedActions = state.getLegalActions();


    return this->untriedActions;
}


int MCTSNode::q() {
    int wins = this->results[1];
    int loses = this->results[-1];
    return wins - loses;
}

int MCTSNode::n(){
    return this->visits;
}

MCTSNode* MCTSNode::expand(){
    // Pop an action from untried_actions
    int action = untriedActions.back();
    untriedActions.pop_back();

    // Get the next state after applying the action
    GameState nextState = state.move(action);

    // Create a new child node with the next state
    MCTSNode* child_node = new MCTSNode(nextState, this, action);

    // Add the child node to the list of children
    children.push_back(child_node);

    return child_node;
}

bool MCTSNode::isTerminalNode() const {
    return state.is_game_over();
}

double MCTSNode::rollout() const {
    GameState current_rollout_state = state;

    while (!current_rollout_state.is_game_over()) {
        std::vector<Action> possible_moves = current_rollout_state.get_legal_actions();

        // Use your rollout policy to select an action
        Action action = rollout_policy(possible_moves);

        current_rollout_state = current_rollout_state.move(action);
    }

    // Return the result of the game
    return current_rollout_state.game_result();
}

void MCTSNode::backpropagate(double result) {
    this->visits += 1;
    this->results[result] += 1;

    if (parent) {
        parent->backpropagate(result);
    }
}

bool MCTSNode::isFullyExpanded() const {
    return untriedActions.empty();
}

MCTSNode* MCTSNode::bestChild(double cParam) const {
    double maxWeight = -std::numeric_limits<double>::infinity();
    MCTSNode* bestChild = nullptr;

    for (const auto& child : children) {
        double weight = (child->q() / child->n()) + cParam * std::sqrt((2 * std::log(n()) / child->n()));
        if (weight > maxWeight) {
            maxWeight = weight;
            bestChild = child;
        }
    }
    return bestChild;
}

int MCTSNode::rolloutPolicy(const std::vector<int>& possibleMoves) const {
    // Generate a random index within the range of possible moves
    int randomIndex = std::rand() % possibleMoves.size();
    // Return the randomly selected move
    return possibleMoves[randomIndex];
}

MCTSNode* MCTSNode::treePolicy() {
    MCTSNode* currentNode = this;
    while (!currentNode->isTerminalNode()) {
        if (!currentNode->isFullyExpanded()) {
            return currentNode->expand();
        } else {
            currentNode = currentNode->bestChild();
        }
    }
    return currentNode;
}

MCTSNode* MCTSNode::bestAction() {
    const int simulationNo = 100;
    for (int i = 0; i < simulationNo; ++i) {
        MCTSNode* v = treePolicy();
        double reward = v->rollout();
        v->backpropagate(reward);
    }
    return bestChild(0.0);
}



// def get_legal_actions(self):
//     '''
//     Modify according to your game or
//     needs. Constructs a list of all
//     possible actions from current state.
//     Returns a list.
//     '''
// def is_game_over(self):
//     '''
//     Modify according to your game or
//     needs. It is the game over condition
//         and depends on your game. Returns
//             true or false
//     '''
// def game_result(self):
//     '''
//     Modify according to your game or
//     needs. Returns 1 or 0 or -1 depending
//     on your state corresponding to win,
//      tie or a loss.
//     '''
// def move(self,action):
//     '''
//     Modify according to your game or
//     needs. Changes the state of your
//     board with a new value. For a normal
//     Tic Tac Toe game, it can be a 3 by 3
//   array with all the elements of array
//   being 0 initially. 0 means the board
//   position is empty. If you place x in
//   row 2 column 3, then it would be some
//   thing like board[2][3] = 1, where 1
//   represents that x is placed. Returns
//   the new state after making a move.
//     '''
// std::vector<Action> GameState::getLegalActions() const {
//     // Modify according to your game logic to construct a list of legal actions
//     std::vector<Action> legalActions;
//     // Add legal actions to the vector
//     return legalActions;
// }

// bool GameState::isGameOver() const {
//     // Modify according to your game logic to check if the game is over
//     // Return true if the game is over, false otherwise
// }

// int GameState::gameResult() const {
//     // Modify according to your game logic to determine the game result
//     // Return 1 for win, 0 for tie, and -1 for loss
// }

// GameState GameState::move(const Action& action) const {
//     // Modify according to your game logic to make a move and return the new state
//     GameState newState = *this;
//     // Make the move and update the state
//     return newState;
// }
