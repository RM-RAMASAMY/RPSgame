#include "mainwindow.h"
#include <QVBoxLayout>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), totalRounds(3), currentRound(1), humanWins(0), computerWins(0), ties(0)
{
    resultLabel = new QLabel("Select your move", this);
    scoreLabel = new QLabel("Human: 0, Computer: 0, Ties: 0", this);
    roundLabel = new QLabel("Round: 1", this);
    algorithmComboBox = new QComboBox(this);
    algorithmComboBox->addItems({"Random", "Pattern"});
    roundsSpinBox = new QSpinBox(this);
    roundsSpinBox->setRange(1, 20);
    roundsSpinBox->setValue(3);

    auto *startButton = new QPushButton("Start Game", this);
    auto *rockButton = new QPushButton("Rock", this);
    auto *paperButton = new QPushButton("Paper", this);
    auto *scissorsButton = new QPushButton("Scissors", this);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(rockButton, &QPushButton::clicked, [=](){ playRound("Rock"); });
    connect(paperButton, &QPushButton::clicked, [=](){ playRound("Paper"); });
    connect(scissorsButton, &QPushButton::clicked, [=](){ playRound("Scissors"); });

    auto *layout = new QVBoxLayout;
    layout->addWidget(algorithmComboBox);
    layout->addWidget(roundsSpinBox);
    layout->addWidget(startButton);
    layout->addWidget(roundLabel);
    layout->addWidget(resultLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(rockButton);
    layout->addWidget(paperButton);
    layout->addWidget(scissorsButton);

    auto *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() = default;

void MainWindow::startGame()
{
    totalRounds = roundsSpinBox->value();
    currentRound = 1;
    humanWins = computerWins = ties = 0;
    roundLabel->setText("Round: 1");
    scoreLabel->setText("Human: 0, Computer: 0, Ties: 0");
}

void MainWindow::playRound(const QString &playerMove)
{
    QString computerMove = getRandomMove();
    QString result = determineResult(playerMove, computerMove);

    if (result == "You Win!") humanWins++;
    else if (result == "You Lose!") computerWins++;
    else ties++;

    resultLabel->setText("Computer: " + computerMove + ", Result: " + result);
    scoreLabel->setText(QString("Human: %1, Computer: %2, Ties: %3").arg(humanWins).arg(computerWins).arg(ties));
    roundLabel->setText(QString("Round: %1").arg(++currentRound));
}

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
