#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardLayout(new QGridLayout)
    , selectedFigure(nullptr)
{
    ui->setupUi(this);
    connectionManager = new ConnectionManager(this);
    setupBoard();

    connect(connectionManager, &ConnectionManager::cellClicked, this, &MainWindow::handleCellClick);
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

            Cell *cell = new Cell(this, row, col, button);
            cells[row][col] = cell;


            // Set the size policy to make the button fill the available space
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            // Set a border style to create a grid-like appearance
            button->setStyleSheet("border: 1px solid black;");

            // Add the button to the layout
            boardLayout->addWidget(button, row, col);

            // Connect the cell button using ConnectionManager
            connectionManager->connectCellButton(cell, button);

            connect(cell, &Cell::figureStateChanged, this, &MainWindow::handleCellFigureStateChanged);



            //##############################################################################
            // Place initial figures on the sides
            if (row == 0 && col == 0) {
                Figure *dukeA = Figure::createFigure(TeamA, Duke, this);
                cell->setFigure(dukeA);
            }
            // Place initial figures on the sides
            if (row == 5 && col == 5) {
                Figure *dukeB = Figure::createFigure(TeamA, Duke, this)  ;
                cell->setFigure(dukeB);
            }

            setButtonText(cell, button);


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

    // Create figure bags for each player
    figureBag *bagPlayerA = new figureBag(TeamA);
    figureBag *bagPlayerB = new figureBag(TeamB);

    // Add QLabel widgets to display selected piece type and player
    selectedPieceLabel = new QLabel("Selected Piece: None", this);
    selectedPlayerLabel = new QLabel("Selected Player: None", this);

    // Connect button clicks to corresponding slots
    connect(playerAButton, &QPushButton::clicked, this, [=]() {
        handlePlayerButtonClick(bagPlayerA, "Player A");
    });
    connect(playerBButton, &QPushButton::clicked, this, [=]() {
        handlePlayerButtonClick(bagPlayerB, "Player B");
    });

    // Add buttons to the layout
    boardLayout->addWidget(playerAButton, 0, 6, 1, 1); // Adjust column span as needed
    boardLayout->addWidget(playerBButton, 5, 6, 1, 1); // Adjust column span as needed



    // Add QLabel widgets to the layout
    boardLayout->addWidget(selectedPieceLabel, 1, 6, 1, 1);
    boardLayout->addWidget(selectedPlayerLabel, 4, 6, 1, 1);
}

void MainWindow::handlePlayerButtonClick(figureBag *bag, const QString &playerName)
{
    // Implement logic to handle player button clicks
    // For now, let's print a message to the console
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton) {
        qDebug() << "Clicked on Player Button: " << clickedButton->text();

        // Get the player from the button text
        QString playerName = clickedButton->text();
        if (selectedPlayerLabel) {
            selectedPlayerLabel->setText("Selected Player: " + playerName);
        } else {
            qDebug() << "Error: selectedPlayerLabel is null.";
        }


        // For now, let's assume you have a function getRandomPieceTypeForPlayer
        Figure* randomPieceType = bag->takeRandomPiece();
        if (randomPieceType == nullptr){
            qDebug() << "NULL";
        }
        selectedFigure = randomPieceType;
        selectedPieceLabel->setText("Selected Piece: " + pieceTypeToString(randomPieceType->type()));
    }
}

void MainWindow::handleCellClick(int row, int col)
{
    Cell *clickedCell = cells[row][col];
    PieceType pieceType;

    if (!selectedFigure) {
        // If selectedFigure is empty, set it to the figure in the clicked cell (if any)
        if (clickedCell->hasFigure()) {
            selectedFigure = clickedCell->getFigure();
            pieceType = selectedFigure->type();
            clickedCell->setFigure(nullptr);
            // Update the selected piece label
            selectedPieceLabel->setText("Selected Piece: " + pieceTypeToString(pieceType));
        }
    } else {
        // Move the selected figure to the clicked cell
        if (!clickedCell->hasFigure()) {
            clickedCell->setFigure(selectedFigure);
            selectedFigure = nullptr;
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
