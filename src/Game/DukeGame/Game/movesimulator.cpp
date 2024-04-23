#include "movesimulator.h"
#include "qdebug.h"

MoveSimulator::MoveSimulator()
{
    this->simulations = 0;
}

void MoveSimulator::updateBoard(GameState state){
    this->boardState = state;
    this->defaultBoardState = state;



}

void MoveSimulator::resetCounter(){
    this->simulations = 0;
}

//TODO This need also check if current team is under GUARD and if yes, then filter moves
Figure::MoveResult MoveSimulator::simulateAndFilterMoves(int row, int col){

    PieceType type;
    PlayerTeam Pteam;
    bool flipped;
    std::tie(type, Pteam, flipped) = this->boardState.board[row][col];

    Figure* figure = Figure::createFigure(Pteam, type);
    if(flipped){
        figure->flip();
    }
    figure->setCoord(row, col);

    Figure::MoveResult moves = figure->markAvailableJumps(this->boardState);

    bool hasCommand = false;

    PlayerTeam team = figure->getTeam();
    // Mark valid moves with 'X'
    for (int i = moves.validMoves.size() - 1; i >= 0; --i) {
        const auto& move = moves.validMoves[i];
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);
        // Get the move type
        MoveTypes moveType = std::get<0>(move);

        if(moveType == CommandTo){
            hasCommand = true;
            continue;
        }
        else if(moveType == CommandFrom){
            hasCommand = true;
            for (const auto& commmove : moves.validMoves) {
                int commmoveRow = std::get<1>(commmove);
                int commmoveCol = std::get<2>(commmove);
                // Get the move type
                MoveTypes commmoveType = std::get<0>(commmove);

                if(commmoveType == CommandTo){
                    this->simulateMove(moves.currentPosition.first, moves.currentPosition.second, moveRow, moveCol, moveType, commmoveRow, commmoveCol);
                }
                else{
                    continue;
                }
                if(selfGuard(team)){
                    moves.validMoves.removeAt(i);
                    rollBackBoard();
                    break;
                }
                else{
                  rollBackBoard();
                }
            }
        }
        else{
            this->simulateMove(moves.currentPosition.first, moves.currentPosition.second, moveRow, moveCol, moveType);
            if(selfGuard(team)){
                qDebug() << moves.currentPosition.first << ":" << moves.currentPosition.second << "..." << moveRow << ":" << moveCol;
                if(moves.validMoves.size() == 1){
                    moves.validMoves.clear();
                }
                else{
                    moves.validMoves.removeAt(i);
                }

            }
        }

        rollBackBoard();
    }
    if(hasCommand){
        bool noComm = false;
        for (const auto& commmove : moves.validMoves) {
            if(std::get<0>(commmove) == CommandFrom){
                break;
            }
            noComm = true;
        }
        if(noComm){
            for (const auto& removeCommand : moves.validMoves) {
                if(CommandTo == std::get<0>(removeCommand)){
                    if(moves.validMoves.length() == 1){
                        moves.validMoves.clear();
                    }
                    else{
                        moves.validMoves.removeAll(removeCommand);
                    }
                }
            }
        }
    }

    if((Pteam == TeamA && boardState.firstTurnA < 3) || (Pteam == TeamB && boardState.firstTurnB < 3)){
        moves.validMoves.clear();
    }

    //printBoard();
    return moves;
}

QList<QPair<int, int>> MoveSimulator::drawPieceCheck(PlayerTeam currentPlayer){

    Figure* duke;

    if(currentPlayer == TeamA){
        duke = Figure::createFigure(currentPlayer, Duke);
        duke->setCoord(this->boardState.dukeCoordA.first, this->boardState.dukeCoordA.second);
    }
    else if(currentPlayer == TeamB){
        duke = Figure::createFigure(currentPlayer, Duke);
        duke->setCoord(this->boardState.dukeCoordB.first, this->boardState.dukeCoordB.second);
    }

    QList<QPair<int, int>> cells = duke->getPlacableCellsForNewPiece(this->boardState);

    // Copy each row
    if(cells.isEmpty()){
        return cells;
    }
    if(currentPlayer == TeamA && (this->boardState.dukeCoordA.first == -1 || this->boardState.dukeCoordA.second == -1)){
        return cells;
    }
    if(currentPlayer == TeamB && (this->boardState.dukeCoordB.first == -1 || this->boardState.dukeCoordB.second == -1)){
        return cells;
    }
    for (const auto& cell : cells) {
        this->placeFigure(cell.first, cell.second, currentPlayer, Footman, false);
        if(selfGuard(currentPlayer)){
            if(cells.length() == 1){
                cells.clear();
            }
            else{
                cells.removeAll(cell);
            }
        }
        rollBackBoard();
    }
    return cells;
}

bool MoveSimulator::selfGuard(PlayerTeam currentPlayer){

    //qDebug() << "SelfGuard board Representation:\n";
    //printBoard();

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {

            PieceType type;
            PlayerTeam Pteam;
            bool flipped;
            std::tie(type, Pteam, flipped) = this->boardState.board[row][col];


            if(type != NoPiece){
                if(Pteam != currentPlayer){
                    Figure* f;
                    f = Figure::createFigure(Pteam, type);
                    if(flipped){
                        f->flip();
                    }
                    f->setCoord(row, col);

                    if(currentPlayer == TeamA){
                        if(f->isValidMove(this->boardState, this->boardState.dukeCoordA.first, this->boardState.dukeCoordA.second)){
                            qDebug() << row << ", "<< col <<"selfGuard!";
                            return true;
                        }
                    }
                    else if(currentPlayer == TeamB){
                        if(f->isValidMove(this->boardState, this->boardState.dukeCoordB.first, this->boardState.dukeCoordB.second)){
                            qDebug() << row << ", "<< col <<"selfGuard!";
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Function to simulate placing a figure in a cell
void MoveSimulator::placeFigure(int row, int col, PlayerTeam owner, PieceType figureType, bool isFlipped){

    this->boardState.board[row][col] = std::make_tuple(figureType, owner, isFlipped);
    if(figureType == Duke){
        if(owner == TeamA){
            this->boardState.dukeCoordA = std::make_pair(row, col);
        }
        else{
            this->boardState.dukeCoordB = std::make_pair(row, col);
        }
    }
}

// Function to simulate removing a figure from a cell
void MoveSimulator::removeFigure(int row, int col) {

    placeFigure(row, col, NoTeam, NoPiece, false);
}

//TODO Check if move is valid
void MoveSimulator::simulateMove(int fromX, int fromY, int toX, int toY, MoveTypes type, /* coord for command */int commandX, int commandY){
    PieceType Ptype;
    PlayerTeam Pteam;
    bool flipped;
    std::tie(Ptype, Pteam, flipped) = this->boardState.board[fromX][fromY];

    if(type != CommandFrom){

        removeFigure(fromX, fromY);
        placeFigure(toX, toY, Pteam, Ptype, !flipped);

        if(Ptype == Duke){
            if(Pteam == TeamA){
                this->boardState.dukeCoordA = std::make_pair(toX, toY);
            }
            else if(Pteam == TeamB){
                this->boardState.dukeCoordB = std::make_pair(toX, toY);
            }
        }
    }
    else{
        placeFigure(fromX, fromY, Pteam, Ptype, !flipped);

        std::tie(Ptype, Pteam, flipped) = this->boardState.board[toX][toY];

        removeFigure(toX, toY);
        placeFigure(commandX, commandY, Pteam, Ptype, flipped);

        if(Ptype == Duke){
            if(Pteam == TeamA){
                this->boardState.dukeCoordA = std::make_pair(toX, toY);
            }
            else if(Pteam == TeamB){
                this->boardState.dukeCoordB = std::make_pair(toX, toY);
            }
        }
    }

    if(this->boardState.currentPlayer == TeamA){
        this->boardState.currentPlayer = TeamB;
    }else{
        this->boardState.currentPlayer = TeamA;
    }
}

//TODO Check if its valid
void MoveSimulator::simulateDraw(int row, int col, PlayerTeam team){




    bool drawFootman = false;
    bool drawDuke = false;
    if(team == TeamA){
        if(boardState.firstTurnA < 3 && boardState.firstTurnA >= 1){
            drawFootman = true;
        }
        else if(boardState.firstTurnA == 0){
            drawDuke = true;
        }
    }
    else{
        if(boardState.firstTurnB < 3 && boardState.firstTurnB >= 1){
            drawFootman = true;
        }
        else if(boardState.firstTurnB == 0){
            drawDuke = true;
        }
    }


    PieceType randomPiece;
    if(!drawFootman && !drawDuke){
        // Seed the random number generator
        srand(time(nullptr));

        // Generate a random index within the range of the vector
        int randomIndex;

        if(boardState.currentPlayer == TeamA){
            randomIndex = rand() % boardState.playerABag.size();

            // Retrieve the element at the random index
            randomPiece = boardState.playerABag[randomIndex];

            // Erase the element from the vector
            boardState.playerABag.erase(boardState.playerABag.begin() + randomIndex);
        }
        else{
            randomIndex = rand() % boardState.playerBBag.size();
            // Retrieve the element at the random index
            randomPiece = boardState.playerBBag[randomIndex];

            // Erase the element from the vector
            boardState.playerBBag.erase(boardState.playerBBag.begin() + randomIndex);
        }
    }

    if(drawFootman){
        randomPiece = Footman;
    }
    if(drawDuke){
        randomPiece = Duke;
    }

    this->placeFigure(row, col, team, randomPiece, false);

    if(boardState.currentPlayer == TeamA){
        if(drawFootman || drawDuke){
            boardState.firstTurnA+=1;
            if(boardState.firstTurnA == 3){
                drawFootman = false;
            }
        }
    }
    else{
        if(drawFootman || drawDuke){
            boardState.firstTurnB+=1;
            if(boardState.firstTurnB == 3){
                drawFootman = false;
            }
        }
    }


    if(drawDuke == false && drawFootman == false){
        if(boardState.currentPlayer == TeamA){
            boardState.currentPlayer = TeamB;
        }
        else{
            boardState.currentPlayer = TeamA;
        }
    }

}

void MoveSimulator::rollBackBoard(){

    this->boardState = this->defaultBoardState;
}

bool MoveSimulator::endGameCheck(GameState state, bool startTurn){

    if(state.firstTurnA < 3 || state.firstTurnB < 3){
        return false;
    }

    this->updateBoard(state);

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {

            PieceType type;
            PlayerTeam Pteam;
            bool flipped;
            std::tie(type, Pteam, flipped) = this->boardState.board[row][col];

            if(type != NoPiece){

                if(!startTurn){
                    if(Pteam != state.currentPlayer){
                        if(!this->simulateAndFilterMoves(row, col).validMoves.empty()){
                            return false;
                        }
                    }
                }
                else{
                    if(Pteam == state.currentPlayer){
                        if(!this->simulateAndFilterMoves(row, col).validMoves.empty()){
                            return false;
                        }
                    }
                }
            }
        }
    }

    qDebug() << "END GAME";
    return true;
}



//TODO FIX printing
void MoveSimulator::printBoard() {
    this->simulations++;
    qDebug() << "Default board Representation:" << this->simulations << "\n";
    // Create a 6x6 grid of empty cells
    std::string grid[6][6];
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            // Use '-' for empty cells
            grid[row][col] = "[ ]";
        }
    }

    PieceType Ptype;
    PlayerTeam Pteam;
    bool Pflipped;

    // Populate grid based on figures on the board
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {

            std::tie(Ptype, Pteam, Pflipped) = this->boardState.board[row][col];


            if (Ptype != NoPiece) {

                char symbol;
                switch (Ptype) {
                case Assassin:
                    symbol = Pteam == TeamA ? 'A' : 'a';
                    break;
                case Bowman:
                    symbol = Pteam == TeamA ? 'B' : 'b';
                    break;
                case Champion:
                    symbol = Pteam == TeamA ? 'C' : 'c';
                    break;
                case Dracoon:
                    symbol = Pteam == TeamA ? 'D' : 'd';
                    break;
                case Duke:
                    symbol = Pteam == TeamA ? 'D' : 'd';
                    break;
                case Footman:
                    symbol = Pteam == TeamA ? 'F' : 'f';
                    break;
                case General:
                    symbol = Pteam == TeamA ? 'G' : 'g';
                    break;
                case Knight:
                    symbol = Pteam == TeamA ? 'K' : 'k';
                    break;
                case Marshall:
                    symbol = Pteam == TeamA ? 'M' : 'm';
                    break;
                case Pikeman:
                    symbol = Pteam == TeamA ? 'P' : 'p';
                    break;
                case Priest:
                    symbol = Pteam == TeamA ? 'R' : 'r';
                    break;
                case Seer:
                    symbol = Pteam == TeamA ? 'S' : 's';
                    break;
                case Wizard:
                    symbol = Pteam == TeamA ? 'W' : 'w';
                    break;
                case Longbowman:
                    symbol = Pteam == TeamA ? 'L' : 'l';
                    break;
                default:
                    symbol = '?'; // Handle unknown type
                    break;

                }
                grid[row][col] = "[";
                grid[row][col] += std::string(1, symbol); // Add figure symbol
                grid[row][col] += "]"; // Close bracket
            }
        }

    }


    // Print the grid
    qDebug() << "##############################################################################################\n";
    for (int row = 0; row < 6; ++row) {
        QString rowString;
        for (int col = 0; col < 6; ++col) {
            rowString += grid[row][col] + " ";
        }
        qDebug() << rowString.trimmed();
    }
    qDebug() << "##############################################################################################\n";

}



