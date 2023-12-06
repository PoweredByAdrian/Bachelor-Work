#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardLayout(new QGridLayout)
    , selectedFigure(nullptr)
    ,  currentPlayer(PlayerTeam::TeamA)
{
    ui->setupUi(this);
    gc = new GameConfigure();



    connectionManager = new ConnectionManager(this);
    setupBoard();

    connect(connectionManager, &ConnectionManager::cellClicked, this, &MainWindow::handleCellClick);
    connect(connectionManager, &ConnectionManager::playerButtonClicked, this, &MainWindow::handlePlayerButtonClick);
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

            Cell* cell = gc->getCell(row, col);
            cell->setButton(button);

            // Set the size policy to make the button fill the available space
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            // Add the button to the layout
            boardLayout->addWidget(button, row, col);


            //////////////////////////////////////////////////////////
            //TODO need checkup all below

            // Connect the cell button using ConnectionManager
            connectionManager->connectCellButton(cell, button);
            connect(cell, &Cell::figureStateChanged, this, &MainWindow::handleCellFigureStateChanged);
            setButtonText(cell, button);
            //////////////////////////////////////////////////////////////
        }
    }
}

void MainWindow::setupPlayers()
{
    // Create buttons for each player
    QPushButton *playerAButton = new QPushButton("Player A", this);
    QPushButton *playerBButton = new QPushButton("Player B", this);
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

    // Create figure bags for each player
    figureBag *bagPlayerA = gc->getBagPlayerA();
    figureBag *bagPlayerB = gc->getBagPlayerB();



    //////////////////////////////////////////////////////////
    //TODO need checkup all below
    connectionManager->connectPlayerButton(playerAButton, bagPlayerA, "Player A");
    connectionManager->connectPlayerButton(playerBButton, bagPlayerB, "Player B");
}

void MainWindow::handlePlayerButtonClick(figureBag *bag, QPushButton *clickedButton)
{
    // Implement logic to handle player button clicks
    // For now, let's print a message to the console
    if (clickedButton) {
        qDebug() << "Clicked on Player Button: " << clickedButton->text();

        // Get the player from the button text
        QString playerName = clickedButton->text();

        // Check if the button corresponds to the current player's turn
        if ((currentPlayer == PlayerTeam::TeamA && playerName == "Player A") ||
            (currentPlayer == PlayerTeam::TeamB && playerName == "Player B")) {
            // For now, let's assume you have a function getRandomPieceTypeForPlayer
            Figure* randomPieceType = bag->takeRandomPiece();
            if (randomPieceType == nullptr){
                qDebug() << "NULL";
            }
            selectedFigure = randomPieceType;

            if(currentPlayer == PlayerTeam::TeamA && playerName == "Player A"){
                selectedPieceLabelPlayerA->setText("Selected Piece: " + pieceTypeToString(randomPieceType->type()));
            }
            else{
                selectedPieceLabelPlayerA->setText("Selected Piece: " + pieceTypeToString(randomPieceType->type()));
            }
        }
    }
}

void MainWindow::handleCellClick(int row, int col)
{
    Cell *clickedCell = gc->getCell(row, col);
    PieceType pieceType;

    // Check whose turn it is
    if (currentPlayer == PlayerTeam::TeamA) {
        // Handle moving pieces for PlayerA
        if (!selectedFigure) {
            // If selectedFigure is empty, set it to the figure in the clicked cell (if any)
            if (clickedCell->hasFigure() && clickedCell->getFigure()->getTeam() == PlayerTeam::TeamA) {
                selectedFigure = clickedCell->getFigure();
                pieceType = selectedFigure->type();
                clickedCell->setFigure(nullptr);
                // Update the selected piece label
                selectedPieceLabelPlayerA->setText("Selected Piece: " + pieceTypeToString(pieceType));
            }
        } else {
            // Move the selected figure to the clicked cell
            if (!clickedCell->hasFigure()) {
                clickedCell->setFigure(selectedFigure);
                selectedFigure = nullptr;
                // After moving, switch to the other player's turn
                currentPlayer = PlayerTeam::TeamB;
                selectedPlayerLabel->setText("Selected Player: Player B");
            }
        }
    } else {  // Current player is PlayerB
        // Handle moving pieces for PlayerB
        if (!selectedFigure) {
            // If selectedFigure is empty, set it to the figure in the clicked cell (if any)
            if (clickedCell->hasFigure() && clickedCell->getFigure()->getTeam() == PlayerTeam::TeamB) {
                selectedFigure = clickedCell->getFigure();
                pieceType = selectedFigure->type();
                clickedCell->setFigure(nullptr);
                // Update the selected piece label
                selectedPieceLabelPlayerB->setText("Selected Piece: " + pieceTypeToString(pieceType));
            }
        } else {
            // Move the selected figure to the clicked cell
            if (!clickedCell->hasFigure()) {
                clickedCell->setFigure(selectedFigure);
                selectedFigure = nullptr;
                // After moving, switch to the other player's turn
                currentPlayer = PlayerTeam::TeamA;
                selectedPlayerLabel->setText("Selected Player: Player A");
            }
        }
    }
}

void MainWindow::handleCellFigureStateChanged()
{
    Cell *changedCell = qobject_cast<Cell*>(sender()); // Get the cell that emitted the signal

    // Find the corresponding button for the changed cell
    QPushButton *button = changedCell->getButton();

    setButtonText(changedCell, button);
}

void MainWindow::setButtonText(Cell* cell, QPushButton* button){
    // Set text and font properties
    // Set text and font properties
    if (cell->hasFigure()) {
        PieceType pieceType = cell->getFigureType();

        // Convert the PieceType enum to a string for display
        QString pieceTypeText = pieceTypeToString(pieceType);

        button->setText(pieceTypeText);
    } else {
        button->setText("");
    }
    button->setFont(QFont("Arial", 12, QFont::Bold));

    // Set background color based on the player if the cell has a figure
    if (cell->hasFigure()) {
        Figure* figure = cell->getFigure();
        if (figure->getTeam() == PlayerTeam::TeamA) {
            // Set background color for Player A
            button->setStyleSheet("background-color: #FFD700"); // Example color: gold
        } else if (figure->getTeam() == PlayerTeam::TeamB) {
            // Set background color for Player B
            button->setStyleSheet("background-color: #4169E1"); // Example color: royal blue
        }
    } else {
        // Clear background color if the cell doesn't have a figure
        button->setStyleSheet("");
    }
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
    default:
        pieceTypeText = "U";
        break;
    }

    return pieceTypeText;
}
