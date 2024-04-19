#include "movesimulator.h"
#include "qdebug.h"

MoveSimulator::MoveSimulator()
{
    board.resize(6, std::vector<CellInfo>(6, CellInfo(false, NoTeam, NoPiece, false)));
    this->gc = nullptr;
}

void MoveSimulator::updateBoard(GameConfigure* gameconfig){
    this->gc = gameconfig;

    printBoard();

    // Clear the existing board
    board.clear();

    // Copy each row
    for (const auto& row : gc->getCells()) {
        std::vector<CellInfo> newRow;

        // Copy each element in the row
        for (const auto* cell : row) {
            if(cell->hasFigure()){
                CellInfo cellInfo(cell->hasFigure(), cell->getFigure()->getTeam(), cell->getFigureType(), cell->getFigure()->isFlipped());
                newRow.push_back(cellInfo);
            }else{
                CellInfo cellInfo(cell->hasFigure(), NoTeam, NoPiece, false);
                newRow.push_back(cellInfo);
            }
        }

        // Add the row to the board
        board.push_back(newRow);
    }
    dukeA.first = gc->getPlayerDuke(TeamA)->getRow();
    dukeA.second = gc->getPlayerDuke(TeamA)->getCol();

    dukeB.first = gc->getPlayerDuke(TeamB)->getRow();
    dukeB.second = gc->getPlayerDuke(TeamB)->getCol();

}
Figure::MoveResult MoveSimulator::simulateAndFilterMoves(Figure* figure, int row, int col){

    if(row != -1 && col != -1){
        figure = gc->getCell(row, col)->getFigure();
    }

    Figure::MoveResult moves = figure->markAvailableJumps(gc->getCells());

    PlayerTeam team = figure->getTeam();
    // Mark valid moves with 'X'
    for (const auto& move : moves.validMoves) {
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);
        // Get the move type
        MoveTypes moveType = std::get<0>(move);

        if(moveType == CommandTo){
            continue;
        }
        else if(moveType == CommandFrom){
            for (const auto& commmove : moves.validMoves) {
                int commmoveRow = std::get<1>(commmove);
                int commmoveCol = std::get<2>(commmove);
                // Get the move type
                MoveTypes commmoveType = std::get<0>(commmove);

                if(commmoveType == CommandTo){
                    this->simulateMove(moves.currentPosition.first, moves.currentPosition.second, moveRow, moveCol, moveType, commmoveRow, commmoveCol);
                }
                if(selfGuard(team)){
                    moves.validMoves.removeAll(commmove);
                }
                rollBackBoard();
            }
        }
        else{
            this->simulateMove(moves.currentPosition.first, moves.currentPosition.second, moveRow, moveCol, moveType);
        }
        if(selfGuard(team)){
            if(moves.validMoves.length() == 1){
                moves.validMoves.clear();
            }
            else{
                moves.validMoves.removeAll(move);
            }

        }
        rollBackBoard();
    }
    printBoard();
    return moves;
}
QList<QPair<int, int>> MoveSimulator::drawPieceCheck(PlayerTeam currentPlayer){
    QList<QPair<int, int>> cells = this->gc->getPlacableCellsForNewPiece(currentPlayer);
    // Copy each row
    if(cells.isEmpty()){
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
    qDebug() << "SELFGUARD BOARD";
    printBoard();
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            Cell* c = gc->getCell(row, col);
            if(c->hasFigure()){
                Figure* f = c->getFigure();
                if(f->getTeam() != currentPlayer){
                    Cell* dukecell = gc->getPlayerDuke(currentPlayer);
                    if(f->isValidMove(gc->getCells(), dukecell->getRow(), dukecell->getCol())){
                        qDebug() << row << ", "<< col <<"selfGuard!";
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Function to simulate placing a figure in a cell
void MoveSimulator::placeFigure(int row, int col, PlayerTeam owner, PieceType figureType, bool isFlipped){
    Figure* figure = Figure::createFigure(owner, figureType);
    gc->getCell(row, col)->setFigure(figure);
    gc->getCell(row, col)->getFigure()->setCell(gc->getCell(row, col));
    if(isFlipped){
        gc->getCell(row, col)->getFigure()->flip();
    }
}
// Function to simulate removing a figure from a cell
void MoveSimulator::removeFigure(int row, int col) {
    // Update the CellInfo for the specified cell
    gc->getCell(row, col)->setFigure(nullptr);
}
void MoveSimulator::simulateMove(int fromX, int fromY, int toX, int toY, MoveTypes type, /* coord for command */int commandX, int commandY){
    if(type != CommandFrom){
        Figure* f = gc->getCell(fromX, fromY)->getFigure();
        placeFigure(toX, toY, f->getTeam(), f->type(), !f->isFlipped());
        this->removeFigure(fromX, fromY);

        if(f->isDuke()){
            f->getTeam() == TeamA ? gc->updateDukeA(gc->getCell(toX, toY)) : gc->updateDukeB(gc->getCell(toX, toY));
        }
    }
    else{
        gc->getCell(fromX, fromY)->getFigure()->flip();
        Figure* f = gc->getCell(toX, toY)->getFigure();
        placeFigure(commandX, commandY, f->getTeam(), f->type(), f->isFlipped());
        this->removeFigure(toX, toY);
        if(f->isDuke()){
            f->getTeam() == TeamA ? gc->updateDukeA(gc->getCell(commandX, commandY)) : gc->updateDukeB(gc->getCell(commandX, commandY));
        }
    }
}
void MoveSimulator::rollBackBoard(GameConfigure* gconf){



    if(gconf != nullptr){
        this->gc = gconf;
    }
    else if(this->gc == nullptr){
        this->gc = new GameConfigure();
        gc->setupBoard();
    }

    // Iterate through each row
    for (size_t i = 0; i < board.size(); ++i) {
        // Iterate through each column
        for (size_t j = 0; j < board[i].size(); ++j) {
            const CellInfo& cellInfo = board[i][j];

            Cell* originalCell = gc->getCell(i, j);

            // Set figure details
            if (cellInfo.hasFigure) {
                Figure* figure = Figure::createFigure(cellInfo.owner, cellInfo.figureType);
                if(cellInfo.isFlipped){
                    figure->flip();
                }
                originalCell->setFigure(figure);
                originalCell->getFigure()->setCell(originalCell);
            }
            else{
                if(originalCell->hasFigure()){
                    originalCell->getFigure()->setCell(nullptr);
                }
                originalCell->setFigure(nullptr);
            }

        }
    }
    gc->updateDukeA(gc->getCell(dukeA.first, dukeA.second));
    gc->updateDukeB(gc->getCell(dukeB.first, dukeB.second));
}




void MoveSimulator::printBoard() {
    // Create a 6x6 grid of empty cells
    std::string grid[6][6];
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            // Use '-' for empty cells
            grid[row][col] = "[ ]";
        }
    }


    // Populate grid based on figures on the board
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gc->getCell(row, col)->hasFigure()) {
                // Access figure information
                const Figure* figure = gc->getCell(row, col)->getFigure();
                PieceType type = figure->type();
                PlayerTeam team = figure->getTeam();
                // Set symbol based on figure type and team
                char symbol;
                switch (type) {
                case Duke:
                    symbol = team == TeamA ? 'D' : 'd';
                    break;
                case Footman:
                    symbol = team == TeamA ? 'F' : 'f';
                    break;
                // ... (add similar cases for other figure types)
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
    qDebug() << "Board Representation:\n";
    for (int row = 0; row < 6; ++row) {
        QString rowString;
        for (int col = 0; col < 6; ++col) {
            rowString += grid[row][col] + " ";
        }
        qDebug() << rowString.trimmed();
    }
}


bool MoveSimulator::endGameCheck(GameConfigure* gconfig, PlayerTeam team){

    this->updateBoard(gconfig);

    // Populate grid based on figures on the board
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gc->getCell(row, col)->hasFigure() && (gc->getCell(row, col)->getFigure()->getTeam() == team)) {
                Figure::MoveResult moves = simulateAndFilterMoves(gc->getCell(row, col)->getFigure());
                if(moves.validMoves.isEmpty()){
                    continue;
                }
                else{
                    rollBackBoard();
                    return false;
                }
            }
        }

    }
    rollBackBoard();
    return true;
}

bool MoveSimulator::is_game_over(BoardState state){
    GameConfigure* configure = new GameConfigure();

    this->board = state.simBoard;
    this->dukeA = state.dukeA;
    this->dukeB = state.dukeB;
    this->rollBackBoard(nullptr);


    // Populate grid based on figures on the board
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gc->getCell(row, col)->hasFigure() && (gc->getCell(row, col)->getFigure()->getTeam() == state.currentTeam)) {
                Figure::MoveResult moves = simulateAndFilterMoves(gc->getCell(row, col)->getFigure());
                if(moves.validMoves.isEmpty()){
                    continue;
                }
                else{
                    rollBackBoard();
                    return false;
                }
            }
        }

    }
    rollBackBoard();
    return true;
}


MoveSimulator::BoardState MoveSimulator::loadBoard(GameConfigure* gameconfig){
    this->gc = gameconfig;

    printBoard();
    std::vector<std::vector<CellInfo>> simBoard;

    // Clear the existing board
    simBoard.clear();

    // Copy each row
    for (const auto& row : gc->getCells()) {
        std::vector<CellInfo> newRow;

        // Copy each element in the row
        for (const auto* cell : row) {
            if(cell->hasFigure()){
                CellInfo cellInfo(cell->hasFigure(), cell->getFigure()->getTeam(), cell->getFigureType(), cell->getFigure()->isFlipped());
                newRow.push_back(cellInfo);
            }else{
                CellInfo cellInfo(cell->hasFigure(), NoTeam, NoPiece, false);
                newRow.push_back(cellInfo);
            }
        }

        // Add the row to the board
        simBoard.push_back(newRow);
    }
    std::pair<int, int> simDukeA;
    std::pair<int, int> simDukeB;
    simDukeA.first = gc->getPlayerDuke(TeamA)->getRow();
    simDukeA.second = gc->getPlayerDuke(TeamA)->getCol();

    simDukeB.first = gc->getPlayerDuke(TeamB)->getRow();
    simDukeB.second = gc->getPlayerDuke(TeamB)->getCol();

    return MoveSimulator::BoardState{simBoard, simDukeA, simDukeB};

}

MoveSimulator::BoardState MoveSimulator::simulateMove(int row, int col, std::vector<std::vector<CellInfo>> board, std::tuple<MoveTypes, int, int> move){
    MoveTypes type = std::get<0>(move);
    PlayerTeam team;
    if(type != CommandFrom){
        Figure* f = gc->getCell(row, col)->getFigure();
        placeFigure(std::get<1>(move), std::get<2>(move), f->getTeam(), f->type(), !f->isFlipped());
        this->removeFigure(row, row);
        team = f->getTeam();
        if(f->isDuke()){
            f->getTeam() == TeamA ? gc->updateDukeA(gc->getCell(std::get<1>(move), std::get<2>(move))) : gc->updateDukeB(gc->getCell(std::get<1>(move), std::get<2>(move)));
        }
    }
    else{
        //TODO Command
    }

    MoveSimulator::BoardState simBoard;
    simBoard = loadBoard(this->gc);
    simBoard.currentTeam = team == TeamA ? TeamB : TeamA;
    this->printBoard();
    this->rollBackBoard();
    return simBoard;

}


