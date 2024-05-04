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
    for (int row = 1; row <= 6; ++row) {
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
    playerAButton = new QPushButton("Player A\nUnder Guard: No", this);
    playerBButton = new QPushButton("Player B\nUnder Guard: No", this);
    // Set vertical size policy to make the buttons fill the available vertical space
    playerAButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    playerBButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    // Add QLabel widgets to display selected piece type and player
    selectedPieceLabelPlayerA = new QLabel("Selected Piece: None", this);
    selectedPieceLabelPlayerB = new QLabel("Selected Piece: None", this);

    selectedPlayerLabel = new QLabel("Selected Player: None", this);
    selectedPlayerLabel->setText("Selected Player: Player A");

    // Add buttons to the layout
    boardLayout->addWidget(playerAButton, 1, 6, 1, 1); // Adjust column span as needed
    selectedPieceLabelPlayerA->setStyleSheet("QLabel { border: 1px solid black; background-color: #FFD700; }");

    boardLayout->addWidget(playerBButton, 6, 6, 1, 1); // Adjust column span as needed
    selectedPieceLabelPlayerB->setStyleSheet("QLabel { border: 1px solid black; background-color: #4169E1 }");

    // Add QLabel widgets to the layout
    boardLayout->addWidget(selectedPieceLabelPlayerA, 2, 6, 1, 1);
    boardLayout->addWidget(selectedPieceLabelPlayerB, 5, 6, 1, 1);

    selectedPlayerLabel->setStyleSheet("QLabel { border: 1px solid black;}" );
    boardLayout->addWidget(selectedPlayerLabel, 3, 6, 2, 1); // Span 2 rows


    playerAPiecesLabel = new QLabel("Pieces in Bag:", this);
    playerBPiecesLabel = new QLabel("Pieces in Bag:", this);


    // Set style sheet to add borders to labels
    QString styleSheet = "QLabel { border: 1px solid black; padding: 5px; }";
    playerAPiecesLabel->setStyleSheet(styleSheet);
    playerBPiecesLabel->setStyleSheet(styleSheet);

    boardLayout->addWidget(playerAPiecesLabel, 0, 0, 1, 7);
    boardLayout->addWidget(playerBPiecesLabel, 7, 0, 1, 7);



}

void MainWindow::setButtonText(int row, int col, PieceType type = NoPiece, PlayerTeam team = NoTeam, bool flipped = false){


    QLayoutItem* item = boardLayout->itemAtPosition(row+1, col);
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
            if (flipped) {
                button->setStyleSheet("background-color: #FFD700; text-decoration: underline;");
            }
        } else if (team == PlayerTeam::TeamB) {
            // Set background color for Player B
            button->setStyleSheet("background-color: #4169E1"); // Example color: royal blue
            if (flipped) {
                button->setStyleSheet("background-color: #4169E1; text-decoration: underline;");
            }
        }
    } else {
        // Clear background color if the cell doesn't have a figure
        button->setStyleSheet("");
    }
}

void MainWindow::updateUI(GameState gameState) {
    // Update the board layout based on the GameState
    for (size_t i = 0; i < gameState.board.size(); ++i) {
        for (size_t j = 0; j < gameState.board[i].size(); ++j) {
            PieceType type = std::get<0>(gameState.board[i][j]);
            PlayerTeam team = std::get<1>(gameState.board[i][j]);
            bool flipped = std::get<2>(gameState.board[i][j]);

            // Update the button text and appearance
            setButtonText(i, j, type, team, flipped);
        }
    }

    // Update current player indicator
    switchPlayerAndResetLabels(gameState.currentPlayer);

    if(gameState.playerA_UnderGuard){
        playerAButton->setText("Player A\nUnder Guard: Yes");
    }
    else{
        playerAButton->setText("Player A\nUnder Guard: No");
    }
    if(gameState.playerB_UnderGuard){
        playerBButton->setText("Player B\nUnder Guard: Yes");
    }
    else{
        playerBButton->setText("Player B\nUnder Guard: No");
    }

    if(gameState.status != InProgress){
        if(gameState.status == A_Win){
            selectedPlayerLabel->setText("A Winner");
        }
        else if(gameState.status == B_Win){
            selectedPlayerLabel->setText("B Winner");
        }
    }

    // Update player bags
    updatePlayerBag(PlayerTeam::TeamA, gameState.playerABag);
    updatePlayerBag(PlayerTeam::TeamB, gameState.playerBBag);

}

void MainWindow::updatePlayerBag(PlayerTeam team, const std::vector<PieceType>& bag) {
    // Get the corresponding QLabel widget for the player's bag
    QLabel* bagLabel;
    if (team == PlayerTeam::TeamA) {
        bagLabel = playerAPiecesLabel;
    } else if (team == PlayerTeam::TeamB) {
        bagLabel = playerBPiecesLabel;
    } else {
        // Handle invalid team
        return;
    }

    // Construct a string representing the pieces in the bag
    QString bagText = "Pieces in Bag: ";
    for (const auto& piece : bag) {
        // Convert the PieceType enum to a string and append it to the bagText
        bagText += pieceTypeToString(piece);
        bagText += ", ";
    }

    // Remove the trailing comma and space
    if (!bag.empty()) {
        bagText.chop(2); // Remove the last two characters (comma and space)
    }

    // Update the bag label with the constructed string
    bagLabel->setText(bagText);




}

QPushButton *MainWindow::getGridButton(int row, int col){
    QLayoutItem* item = boardLayout->itemAtPosition(row+1, col);
    QPushButton* button;

    if (item && item->widget()) {
        button = qobject_cast<QPushButton*>(item->widget());
    }

    return button;

}



void MainWindow::switchPlayerAndResetLabels(PlayerTeam currTeam) {
    // Switch the player label
    currentPlayer = currTeam;
    QString currentPlayerLabel = (currentPlayer == TeamA) ? "Selected Player: Player A" : "Selected Player: Player B";

    // Reset both piece labels to "None"
    selectedPieceLabelPlayerA->setText("Selected Piece: None");
    selectedPieceLabelPlayerB->setText("Selected Piece: None");

    // Update the player label
    selectedPlayerLabel->setText(currentPlayerLabel);
}

void MainWindow::updateSelectedPieceLabel(PieceType pieceType) {
    // Determine which piece label to update based on the player
    QLabel *selectedPieceLabel = (currentPlayer == TeamA) ? selectedPieceLabelPlayerA : selectedPieceLabelPlayerB;

    QString pieceTypeString = pieceTypeToString(pieceType);
    pieceTypeString = (pieceTypeString.isEmpty()) ? "None" : pieceTypeString;
    // Update the selected piece label with the piece type
    selectedPieceLabel->setText("Selected Piece: " + pieceTypeString);
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
    default:
        pieceTypeText = "";
        break;
    }

    return pieceTypeText;
}
