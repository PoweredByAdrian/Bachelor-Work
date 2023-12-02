#include "figurebag.h"
#include <QRandomGenerator>

figureBag::figureBag()
{}

void figureBag::setPieces(QList<Figure*> pieces){
    this->pieces = pieces;
}

Figure* figureBag::takeRandomPiece(){
    if(!pieces.empty()){
        int randomIndex = QRandomGenerator::global()->bounded(pieces.size());
        return pieces.takeAt(randomIndex); // Take and remove the piece from the bag
    }
    else
    {
        return nullptr; // Bag is empty
    }
}
