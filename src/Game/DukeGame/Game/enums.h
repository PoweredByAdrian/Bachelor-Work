#ifndef ENUMS_H
#define ENUMS_H

enum PlayerTeam {
    TeamA,
    TeamB,

    NoTeam
};

enum PieceType {
    Assassin,
    Bowman,
    Champion,
    Dracoon,
    Duke,
    Footman,
    General,
    Knight,
    Marshall,
    Pikeman,
    Priest,
    Seer,
    Wizard,
    Longbowman,

    NoPiece
};

enum MoveTypes{
    Move,
    Jump,
    Slide,
    JumpSlide,
    Strike,
    Command,
    CommandFrom,
    CommandTo
};

#endif // ENUMS_H