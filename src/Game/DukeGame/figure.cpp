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
#include "p_marshall.h"
#include "p_pikeman.h"
#include "p_priest.h"
#include "p_seer.h"
#include "p_wizard.h"


Figure::Figure(PlayerTeam team, PieceType type, QObject *parent)
    : QObject(parent), cell(nullptr), team(team)
{
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

Figure* Figure::createFigure(PlayerTeam team, PieceType type, QObject *parent)
{
    switch (type) {
    case PieceType::Assassin:
        return new p_Assassin(team, parent);
    case PieceType::Bowman:
        return new p_Bowman(team, parent);
    case PieceType::Champion:
        return new p_Champion(team, parent);
    case PieceType::Dracoon:
        return new p_Dracoon(team, parent);
    case PieceType::Duke:
        return new p_Duke(team, parent);
    case PieceType::Footman:
        return new p_Footman(team, parent);
    case PieceType::General:
        return new p_General(team, parent);
    case PieceType::Knight:
        return new p_Knight(team, parent);
    case PieceType::Marshall:
        return new p_Marshall(team, parent);
    case PieceType::Pikeman:
        return new p_Pikeman(team, parent);
    case PieceType::Priest:
        return new p_Priest(team, parent);
    case PieceType::Seer:
        return new p_Seer(team, parent);
    case PieceType::Wizard:
        return new p_Wizard(team, parent);
    // Add cases for other piece types
    default:
        return nullptr; // Unknown piece type
    }
}
