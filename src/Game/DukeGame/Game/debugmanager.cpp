// DebugManager.cpp
#include "DebugManager.h"

void DebugManager::printMoves(Figure::MoveResult moves, bool cmdOnly) {
    // Create a 6x6 grid of empty cells
    QString grid[6][6];
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            grid[row][col] = "[ ]"; // Initialize with empty cells
        }
    }

    // Mark the current position with 'O'
    QPair<int, int> currentPos = moves.currentPosition;
    grid[currentPos.first][currentPos.second] = "[X]";

    // Mark valid moves with 'X'
    for (const auto& move : moves.validMoves) {
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);
        // Get the move type
        MoveTypes moveType = std::get<0>(move);

        if(cmdOnly){
            if(moveType == CommandTo){
               grid[moveRow][moveCol] = "[Ct]";
            }
        }
        else{
            // Set the symbol based on the move type
            switch (moveType) {
            case MoveTypes::Move:
                grid[moveRow][moveCol] = "[M]";
                break;
            case MoveTypes::Jump:
                grid[moveRow][moveCol] = "[J]";
                break;
            case MoveTypes::Slide:
                grid[moveRow][moveCol] = "[S]";
                break;
            case MoveTypes::JumpSlide:
                grid[moveRow][moveCol] = "[JS]";
                break;
            case MoveTypes::Strike:
                grid[moveRow][moveCol] = "[St]";
                break;
            case MoveTypes::CommandFrom:
                grid[moveRow][moveCol] = "[Cf]";
                break;
            case MoveTypes::CommandTo:
                grid[moveRow][moveCol] = "[Ct]";
                break;
            default:
                // Handle unknown move type (optional)
                break;
            }
        }

    }

    // Print the grid
    qDebug() << "Recorded Moves:";
    for (int row = 0; row < 6; ++row) {
        QString rowString;
        for (int col = 0; col < 6; ++col) {
            rowString += grid[row][col] + " ";
        }
        qDebug() << rowString.trimmed(); // Trim the trailing space and print the entire row
    }
}
