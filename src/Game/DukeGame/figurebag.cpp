#include "figurebag.h"
#include <QRandomGenerator>

figureBag::figureBag(PlayerTeam playerteam)
{
    team = playerteam;
    initialize();
    dukeDelivered = false;
}
void figureBag::initialize() {

    Figure* F_knight = Figure::createFigure(team, Knight);
    pieces.append(F_knight);
    Figure* F_seer = Figure::createFigure(team, Seer);
    pieces.append(F_seer);
    Figure* F_champion = Figure::createFigure(team, Champion);
    pieces.append(F_champion);
    Figure* F_footman1 = Figure::createFigure(team, Footman);
    pieces.append(F_footman1);
    Figure* F_footman2 = Figure::createFigure(team, Footman);
    pieces.append(F_footman2);
    Figure* F_footman3 = Figure::createFigure(team, Footman);
    pieces.append(F_footman3);
    Figure* F_wizard = Figure::createFigure(team, Wizard);
    pieces.append(F_wizard);
    Figure* F_general = Figure::createFigure(team, General);
    pieces.append(F_general);
    Figure* F_marshall = Figure::createFigure(team, Marshall);
    pieces.append(F_marshall);
    Figure* F_assassin = Figure::createFigure(team, Assassin);
    pieces.append(F_assassin);
    Figure* F_pikeman1 = Figure::createFigure(team, Pikeman);
    pieces.append(F_pikeman1);
    Figure* F_pikeman2 = Figure::createFigure(team, Pikeman);
    pieces.append(F_pikeman2);
    Figure* F_pikeman3 = Figure::createFigure(team, Pikeman);
    pieces.append(F_pikeman3);
    Figure* F_priest = Figure::createFigure(team, Priest);
    pieces.append(F_priest);
    Figure* F_bowman = Figure::createFigure(team, Bowman);
    pieces.append(F_bowman);
    Figure* F_dracoon = Figure::createFigure(team, Dracoon);
    pieces.append(F_dracoon);
    Figure* F_longbowman = Figure::createFigure(team, Longbowman);
    pieces.append(F_longbowman);


}
Figure* figureBag::takeRandomPiece(){

    if(!dukeDelivered){
        Figure* F_Duke = Figure::createFigure(team, Duke);
        dukeDelivered = true;
        return F_Duke;
    }


    if(!(isEmpty())){
        int randomIndex = QRandomGenerator::global()->bounded(pieces.size() - 1);
        return pieces.takeAt(randomIndex); // Take and remove the piece from the bag
    }
    else
    {
        return nullptr; // Bag is empty
    }
}

bool figureBag::isEmpty() const {
    return pieces.empty();
}
