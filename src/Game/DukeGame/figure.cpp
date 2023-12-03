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


Figure::Figure(Team team, PieceType type, QObject *parent)
    : QObject(parent), cell(nullptr), team(team)
{
}

void Figure::setTeam(Figure::Team team)
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

Figure* Figure::createFigure(Figure::Team team, Figure::PieceType type, QObject *parent)
{
    switch (type) {
    case Figure::PieceType::Assassin:
        return new p_Assassin(team, parent);
    case Figure::PieceType::Bowman:
        return new p_Bowman(team, parent);
    case Figure::PieceType::Champion:
        return new p_Champion(team, parent);
    case Figure::PieceType::Dracoon:
        return new p_Dracoon(team, parent);
    case Figure::PieceType::Duke:
        return new p_Duke(team, parent);
    case Figure::PieceType::Footman:
        return new p_Footman(team, parent);
    case Figure::PieceType::General:
        return new p_General(team, parent);
    case Figure::PieceType::Knight:
        return new p_Knight(team, parent);
    case Figure::PieceType::Marshall:
        return new p_Marshall(team, parent);
    case Figure::PieceType::Pikeman:
        return new p_Pikeman(team, parent);
    case Figure::PieceType::Priest:
        return new p_Priest(team, parent);
    case Figure::PieceType::Seer:
        return new p_Seer(team, parent);
    case Figure::PieceType::Wizard:
        return new p_Wizard(team, parent);
    // Add cases for other piece types
    default:
        return nullptr; // Unknown piece type
    }
}
