#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardLayout(new QGridLayout)
    , currentPlayer(PlayerTeam::TeamA)
{
    ui->setupUi(this);

    setupBoard();

    setupPlayers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete boardLayout;
}

void MainWindow::setupBoard()
{
    // Set up the layout for the chessboard
    ui->centralwidget->setLayout(boardLayout);

    // Set spacing and margins to 0 to eliminate gaps
    boardLayout->setSpacing(0);
    boardLayout->setContentsMargins(0, 0, 0, 0);


    // Create cells and buttons dynamically
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            // Create a button to represent the cell visually
            QPushButton *button = new QPushButton(this);

            // Set the size policy to make the button fill the available space
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // Add the button to the layout
            boardLayout->addWidget(button, row, col);
        }
    }
}

void MainWindow::setupPlayers()
{
    // Create buttons for each player
    playerAButton = new QPushButton("Player A", this);
    playerBButton = new QPushButton("Player B", this);
    // Set vertical size policy to make the buttons fill the available vertical space
    playerAButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    playerBButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    // Add QLabel widgets to display selected piece type and player
    selectedPieceLabelPlayerA = new QLabel("Selected Piece: None", this);
    selectedPieceLabelPlayerB = new QLabel("Selected Piece: None", this);

    selectedPlayerLabel = new QLabel("Selected Player: None", this);
    selectedPlayerLabel->setText("Selected Player: Player A");

    // Add buttons to the layout
    boardLayout->addWidget(playerAButton, 0, 6, 1, 1); // Adjust column span as needed
    selectedPieceLabelPlayerA->setStyleSheet("QLabel { border: 1px solid black; background-color: #FFD700; }");

    boardLayout->addWidget(playerBButton, 5, 6, 1, 1); // Adjust column span as needed
    selectedPieceLabelPlayerB->setStyleSheet("QLabel { border: 1px solid black; background-color: #4169E1 }");

    // Add QLabel widgets to the layout
    boardLayout->addWidget(selectedPieceLabelPlayerA, 1, 6, 1, 1);
    boardLayout->addWidget(selectedPieceLabelPlayerB, 4, 6, 1, 1);

    selectedPlayerLabel->setStyleSheet("QLabel { border: 1px solid black;}" );
    boardLayout->addWidget(selectedPlayerLabel, 2, 6, 2, 1); // Span 2 rows

}

void MainWindow::setButtonText(int row, int col, PieceType type = NoPiece, PlayerTeam team = NoTeam){


    QLayoutItem* item = boardLayout->itemAtPosition(row, col);
    QPushButton* button;

    if (item && item->widget()) {
        button = qobject_cast<QPushButton*>(item->widget());
    }

    // Convert the PieceType enum to a string for display
    QString pieceTypeText = pieceTypeToString(type);

    button->setText(pieceTypeText);

    button->setFont(QFont("Arial", 12, QFont::Bold));

    // Set background color based on the player if the cell has a figure
    if (type != NoPiece) {
        if (team == PlayerTeam::TeamA) {
            // Set background color for Player A
            button->setStyleSheet("background-color: #FFD700"); // Example color: gold
        } else if (team == PlayerTeam::TeamB) {
            // Set background color for Player B
            button->setStyleSheet("background-color: #4169E1"); // Example color: royal blue
        }
    } else {
        // Clear background color if the cell doesn't have a figure
        button->setStyleSheet("");
    }
}

QPushButton *MainWindow::getGridButton(int row, int col){
    QLayoutItem* item = boardLayout->itemAtPosition(row, col);
    QPushButton* button;

    if (item && item->widget()) {
        button = qobject_cast<QPushButton*>(item->widget());
    }

    return button;

}

QString MainWindow::pieceTypeToString(PieceType pieceType){

    QString pieceTypeText;

    switch (pieceType) {
    case Assassin:
        pieceTypeText = "Assassin";
        break;
    case Bowman:
        pieceTypeText = "Bowman";
        break;
    case Champion:
        pieceTypeText = "Champion";
        break;
    case Dracoon:
        pieceTypeText = "Dracoon";
        break;
    case Duke:
        pieceTypeText = "Duke";
        break;
    case Footman:
        pieceTypeText = "Footman";
        break;
    case General:
        pieceTypeText = "General";
        break;
    case Knight:
        pieceTypeText = "Knight";
        break;
    case Marshall:
        pieceTypeText = "Marshall";
        break;
    case Pikeman:
        pieceTypeText = "Pikeman";
        break;
    case Priest:
        pieceTypeText = "Priest";
        break;
    case Seer:
        pieceTypeText = "Seer";
        break;
    case Wizard:
        pieceTypeText = "Wizard";
        break;
    case Longbowman:
        pieceTypeText = "Longbowman";
        break;
    case NoPiece:
        pieceTypeText = "";
    default:
        pieceTypeText = "U";
        break;
    }

    return pieceTypeText;
}
