// figure.cpp
#include "figure.h"
#include "p_assassin.h"
#include "p_bowman.h"
#include "p_champion.h"
#include "p_dracoon.h"
#include "p_duke.h"
#include "p_footman.h"
#include "p_general.h"
#include "p_knight.h"
#include "p_longbowman.h"
#include "p_marshall.h"
#include "p_pikeman.h"
#include "p_priest.h"
#include "p_seer.h"
#include "p_wizard.h"


Figure::Figure(PlayerTeam team, PieceType type)
    : cell(nullptr), team(team), flipped(false)
{
    direction = (team == TeamA) ? 1 : -1;
}

void Figure::setTeam(PlayerTeam team)
{
    this->team = team;
}

void Figure::setCell(Cell *cell)
{
    this->cell = cell;
}

Cell *Figure::getCell() const
{
    return cell;
}

Figure* Figure::createFigure(PlayerTeam team, PieceType type)
{
    switch (type) {
    case PieceType::Assassin:
        return new p_Assassin(team);
    case PieceType::Bowman:
        return new p_Bowman(team);
    case PieceType::Champion:
        return new p_Champion(team);
    case PieceType::Dracoon:
        return new p_Dracoon(team);
    case PieceType::Duke:
        return new p_Duke(team);
    case PieceType::Footman:
        return new p_Footman(team);
    case PieceType::General:
        return new p_General(team);
    case PieceType::Knight:
        return new p_Knight(team);
    case PieceType::Longbowman:
        return new p_Longbowman(team);
    case PieceType::Marshall:
        return new p_Marshall(team);
    case PieceType::Pikeman:
        return new p_Pikeman(team);
    case PieceType::Priest:
        return new p_Priest(team);
    case PieceType::Seer:
        return new p_Seer(team);
    case PieceType::Wizard:
        return new p_Wizard(team);
    // Add cases for other piece types
    default:
        return nullptr; // Unknown piece type
    }
}


bool Figure::isValidMove(std::vector<std::vector<Cell*>>& cells, int row, int col)
{
    // Get all valid moves from markAvailableJumps
    MoveResult moves = this->markAvailableJumps(cells);

    // Check if the desired move (row, col) is present in the validMoves list
    for (const auto& move : moves.validMoves) {
        // Extract destination coordinates from the tuple
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);

        // If the desired move matches any valid move, return true
        if (row == moveRow && col == moveCol) {
            return true;
        }
    }

    // If the desired move is not found in validMoves, return false
    return false;
}



























