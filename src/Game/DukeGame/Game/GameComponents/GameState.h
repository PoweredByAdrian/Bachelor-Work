#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <vector>

#include "../enums.h"

// Struct to represent the game
struct GameState {
    std::vector<std::vector<std::tuple<PieceType, PlayerTeam, bool>>> board;  // 2D array to show the placement of figures and their flipped state
    PlayerTeam currentPlayer;
    std::vector<PieceType> playerABag;  // List of pieces in bag for player A (with their flipped state)
    std::vector<PieceType> playerBBag;  // List of pieces in bag for player B (with their flipped state)
    bool playerA_UnderGuard;
    bool playerB_UnderGuard;
    std::pair<int, int> dukeCoordA;
    std::pair<int, int> dukeCoordB;

    int firstTurnA;
    int firstTurnB;
};


#endif // GAMESTATE_H
