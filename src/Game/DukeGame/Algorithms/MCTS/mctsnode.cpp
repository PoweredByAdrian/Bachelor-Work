#include "mctsnode.h"
#include <limits>
#include <random>
#include <qdebug.h>

MCTSNode::MCTSNode(MoveSimulator::BoardState state,Action parentAction, MCTSNode* parent = nullptr )
    : state(state), parent(parent), parentAction(parentAction)  {

    this->children.clear();
    this->visits = 0;
    results[1] = 0;
    results[-1] = 0;
    this->ms = new MoveSimulator();
    untriedactions = untriedActions();

}

std::vector<Action> MCTSNode::untriedActions() {

    // Iterate through each row
    for (size_t i = 0; i < state.simBoard.size(); ++i) {
        // Iterate through each column
        for (size_t j = 0; j < state.simBoard[i].size(); ++j) {
            const CellInfo& cellInfo = state.simBoard[i][j];

            // Set figure details
            if (cellInfo.hasFigure) {
                if(cellInfo.owner == state.currentTeam){
                    ms->setState(state);
                    ms->rollBackBoard();
                    Figure::MoveResult moves = ms->simulateAndFilterMoves(nullptr, i, j);

                   Action act;
                    for (const auto& move : moves.validMoves) {
                        int moveRow = std::get<1>(move);
                        int moveCol = std::get<2>(move);
                        // Get the move type
                        MoveTypes moveType = std::get<0>(move);

                        if(moveType == CommandTo || moveType == CommandFrom){
                            continue;
                        }

                        act.currentPosition = moves.currentPosition;
                        act.nextPosition = std::pair(moveRow, moveCol);
                        act.moveType = moveType;

                        this->untriedactions.push_back(act);

                    }
                }
            }
        }
    }

    if(!ms->drawPieceCheck(state.currentTeam).empty()){
        QList<QPair<int, int>>draws =  ms->drawPieceCheck(state.currentTeam);
        //TODO draws
    }


    return this->untriedactions;
}

int MCTSNode::q() {
    int wins = this->results[1];
    int loses = this->results[-1];
    return wins - loses;
}

int MCTSNode::n()const {
    return this->visits;
}

MCTSNode* MCTSNode::expand(){
    // Pop an action from untried_actions
    Action action = untriedactions.back();
    untriedactions.pop_back();

    // Get the next state after applying the action
    MoveSimulator::BoardState nextState = this->ms->simulateMove(action.currentPosition.first, action.currentPosition.second, state.simBoard, std::tuple(action.moveType, action.nextPosition.first, action.nextPosition.second));

    // Create a new child node with the next state
    MCTSNode* child_node = new MCTSNode(nextState, action, this);

    // Add the child node to the list of children
    children.push_back(child_node);

    return child_node;
}

bool MCTSNode::isTerminalNode() const {



    return this->ms->is_game_over(state);
}
double MCTSNode::rollout() const {
    MoveSimulator::BoardState current_rollout_state = state;

    while (!this->ms->is_game_over(current_rollout_state)) {

        std::vector<Action> possible_moves;

        // Iterate through each row
        for (size_t i = 0; i < current_rollout_state.simBoard.size(); ++i) {
            // Iterate through each column
            for (size_t j = 0; j < current_rollout_state.simBoard[i].size(); ++j) {
                const CellInfo& cellInfo = current_rollout_state.simBoard[i][j];

                // Set figure details
                if (cellInfo.hasFigure) {
                    if(cellInfo.owner == current_rollout_state.currentTeam){

                        ms->setState(current_rollout_state);
                        ms->rollBackBoard();
                        Figure::MoveResult moves = ms->simulateAndFilterMoves(nullptr, i, j);

                        Action act;
                        for (const auto& move : moves.validMoves) {
                            int moveRow = std::get<1>(move);
                            int moveCol = std::get<2>(move);
                            // Get the move type
                            MoveTypes moveType = std::get<0>(move);

                            if(moveType == CommandTo || moveType == CommandFrom){
                                continue;
                            }
                            Action act;

                            act.currentPosition = moves.currentPosition;
                            act.nextPosition = std::pair(moveRow, moveCol);
                            act.moveType = moveType;

                            possible_moves.push_back(act);

                        }
                    }
                }
            }
        }


        // Use your rollout policy to select an action
        Action action = rolloutPolicy(possible_moves);

        qDebug() << "";
        qDebug() << "";
        qDebug() << "";
        qDebug() << "MCTS";


        current_rollout_state = ms->simulateMove(action.currentPosition.first, action.currentPosition.second, current_rollout_state.simBoard, std::tuple(action.moveType, action.nextPosition.first, action.nextPosition.second));

    }

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the distribution for integers in the range [-1, 1]
    std::uniform_int_distribution<int> dist(-1, 1);

    // Generate a random number
    int randomValue = dist(gen);

    // Return the result of the game
    //TODO return current_rollout_state.game_result();
    return randomValue;
}

void MCTSNode::backpropagate(double result) {
    this->visits += 1;
    this->results[result] += 1;

    if (parent) {
        parent->backpropagate(result);
    }
}

bool MCTSNode::isFullyExpanded() const {
    return untriedactions.empty();
}

MCTSNode* MCTSNode::bestChild(double cParam = 0.1) const {
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

Action MCTSNode::rolloutPolicy(const std::vector<Action>& possibleMoves) const {
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
