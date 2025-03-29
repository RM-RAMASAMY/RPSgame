#include "mainwindow.h"
#include <QVBoxLayout>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), resultLabel(new QLabel("Choose your move!", this))
{
    auto *rockButton = new QPushButton("Rock", this);
    auto *paperButton = new QPushButton("Paper", this);
    auto *scissorsButton = new QPushButton("Scissors", this);

    connect(rockButton, &QPushButton::clicked, this, &MainWindow::playRock);
    connect(paperButton, &QPushButton::clicked, this, &MainWindow::playPaper);
    connect(scissorsButton, &QPushButton::clicked, this, &MainWindow::playScissors);

    auto *layout = new QVBoxLayout;
    layout->addWidget(rockButton);
    layout->addWidget(paperButton);
    layout->addWidget(scissorsButton);
    layout->addWidget(resultLabel);

    auto *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

QString MainWindow::getRandomMove()
{
    const QStringList moves = {"Rock", "Paper", "Scissors"};
    int index = QRandomGenerator::global()->bounded(3);
    return moves[index];
}

QString MainWindow::determineResult(const QString &playerMove, const QString &computerMove)
{
    if (playerMove == computerMove) return "Draw!";
    if ((playerMove == "Rock" && computerMove == "Scissors") ||
        (playerMove == "Paper" && computerMove == "Rock") ||
        (playerMove == "Scissors" && computerMove == "Paper"))
        return "You Win!";
    return "You Lose!";
}

void MainWindow::playRock()
{
    QString computerMove = getRandomMove();
    resultLabel->setText("Computer: " + computerMove + ", Result: " + determineResult("Rock", computerMove));
}

void MainWindow::playPaper()
{
    QString computerMove = getRandomMove();
    resultLabel->setText("Computer: " + computerMove + ", Result: " + determineResult("Paper", computerMove));
}

void MainWindow::playScissors()
{
    QString computerMove = getRandomMove();
    resultLabel->setText("Computer: " + computerMove + ", Result: " + determineResult("Scissors", computerMove));
}
