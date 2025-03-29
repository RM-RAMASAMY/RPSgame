#include "mainwindow.h"
#include <QVBoxLayout>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), totalRounds(20), currentRound(1), humanWins(0), computerWins(0), ties(0)
{
    readFreq();
    resultLabel = new QLabel("Select your move", this);
    scoreLabel = new QLabel("Human: 0, Computer: 0, Ties: 0", this);
    roundLabel = new QLabel("Round: 1", this);
    HumanLabel = new QLabel("Human Chooses: - ", this);
    PredictedLabel = new QLabel("Predicted Human Choice: - ", this);
    CompLabel = new QLabel("Computer Chooses: - ", this);
    WinnerLabel = new QLabel("Winner: - ", this);
    algorithmComboBox = new QComboBox(this);
    algorithmComboBox->addItems({"Random", "SMART"});
    roundsSpinBox = new QSpinBox(this);
    roundsSpinBox->setRange(1, 20);
    roundsSpinBox->setValue(20);

    auto *startButton = new QPushButton("Start Game", this);
    auto *resetButton = new QPushButton("Reset Game", this);
    auto *rockButton = new QPushButton("Rock", this);
    auto *paperButton = new QPushButton("Paper", this);
    auto *scissorsButton = new QPushButton("Scissors", this);

    // connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    
    connect(startButton, &QPushButton::clicked, [=](){ 
        startGame();
        rockButton->setEnabled(true);
        paperButton->setEnabled(true);
        scissorsButton->setEnabled(true);
    });
    connect(resetButton, &QPushButton::clicked, [=](){ 
        algorithmComboBox->setEnabled(true);
        algorithmComboBox->setCurrentIndex(0);
        roundsSpinBox->setEnabled(true);
        roundsSpinBox->setValue(20);
        startButton->setEnabled(true);
        totalRounds = roundsSpinBox->value();
        currentRound = 1;
        humanWins = computerWins = ties = 0;
        roundLabel->setText("Round: 1");
        scoreLabel->setText("Human: 0, Computer: 0, Ties: 0");
        resultLabel->setText("game has reset.\nchoose algorithm and rounds.\nclick 'start game' button to start again.");
        HumanLabel->setText("Human Chooses: - ");
        PredictedLabel->setText("Predicted Human Choice: - ");
        CompLabel->setText("Therefore, the Computer Chooses: - ");
        WinnerLabel->setText("Winner: - ");
        resultLabel->setAlignment(Qt::AlignCenter);
        rockButton->setEnabled(false);
        paperButton->setEnabled(false);
        scissorsButton->setEnabled(false);

    });
    connect(rockButton, &QPushButton::clicked, [=](){ 
        playRound("Rock"); 
        if (currentRound > 1) {
            startButton->setEnabled(false);
        }
    });
    connect(paperButton, &QPushButton::clicked, [=](){ 
        playRound("Paper"); 
        if (currentRound > 1) {
            startButton->setEnabled(false);
        }
    });
    connect(scissorsButton, &QPushButton::clicked, [=](){ 
        playRound("Scissors"); 
        if (currentRound > 1) {
            startButton->setEnabled(false);
        }
    });

    auto *layout = new QVBoxLayout;
    auto *settingsLayout = new QHBoxLayout;
    auto *HumanInteractionLayout = new QHBoxLayout;

    settingsLayout->addWidget(new QLabel("Algorithm:", this));
    settingsLayout->addWidget(algorithmComboBox);
    settingsLayout->addWidget(new QLabel("Rounds:", this));
    settingsLayout->addWidget(roundsSpinBox);
    settingsLayout->addWidget(startButton);
    settingsLayout->addWidget(resetButton);

    
    HumanInteractionLayout->addWidget(rockButton);
    HumanInteractionLayout->addWidget(paperButton);
    HumanInteractionLayout->addWidget(scissorsButton);

    layout->addLayout(settingsLayout);
    
    layout->addWidget(roundLabel, 0, Qt::AlignCenter);

    
    layout->addWidget(new QLabel(" ", this), 0, Qt::AlignCenter);
    layout->addWidget(resultLabel, 0, Qt::AlignCenter);
    
    layout->addWidget(new QLabel(" ", this), 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("Human:", this), 0, Qt::AlignCenter);
    layout->addLayout(HumanInteractionLayout);
    layout->addWidget(HumanLabel, 0, Qt::AlignCenter); 
    
    layout->addWidget(new QLabel(" ", this), 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("Computer:", this), 0, Qt::AlignCenter);
    layout->addWidget(PredictedLabel, 0, Qt::AlignCenter);  
    layout->addWidget(CompLabel, 0, Qt::AlignCenter);

    layout->addWidget(new QLabel(" ", this), 0, Qt::AlignCenter);
    layout->addWidget(WinnerLabel, 0, Qt::AlignCenter); 

    layout->addWidget(new QLabel(" ", this), 0, Qt::AlignCenter);
    layout->addWidget(new QLabel("Statistics:", this), 0, Qt::AlignCenter);
    layout->addWidget(scoreLabel, 0, Qt::AlignCenter);

    auto *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() = default;

void MainWindow::readFreq()
{
    std::ifstream file("frequencies.txt"); // Open the file
    if (!file.is_open()) {
        qDebug() << "Failed to open frequencies.txt";
        return;
    }

    std::string key; // Use std::string to read from the file
    int value;

    // Read key-value pairs from the file
    while (file >> key >> value) {
        // Convert std::string to QString and store in the map
        patternFrequency[QString::fromStdString(key)] = value;
    }

    file.close(); // Close the file
    std::cout << "Reading file frequencies.txt: " << patternFrequency.size() << " records." << std::endl;
}

void MainWindow::writeFreq()
{
    // Write the frequency map to a file
    std::ofstream file("frequencies.txt");
for (const QString &key : patternFrequency.keys()) {
    file << key.toStdString() << " " << patternFrequency[key] << std::endl;
}
    file.close();
    std::cout << "Writing frequency file frequency.txt: " << patternFrequency.size() << " records." << std::endl;
}

void MainWindow::startGame()
{
    totalRounds = roundsSpinBox->value();
    currentRound = 1;
    humanWins = computerWins = ties = 0;
    roundLabel->setText("Round: 1");
    scoreLabel->setText("Human: 0, Computer: 0, Ties: 0");
    HumanLabel->setText("Human Chooses: - ");
    PredictedLabel->setText("Predicted Human Choice: - ");
    CompLabel->setText("Computer Chooses: - ");
    WinnerLabel->setText("Winner: - ");
    algorithmComboBox->setEnabled(false);
    roundsSpinBox->setEnabled(false);
}

void MainWindow::playRound(const QString &playerMove)
{
    if (currentRound > totalRounds) {
        resultLabel->setText("Game Over!");
        writeFreq(); // Write the frequency map to a file
        return;
    }

    QString computerMove = algorithmComboBox->currentText() == "SMART" ? smartMove() : getRandomMove();
    QString result = determineResult(playerMove, computerMove);

    humanMoves.append(playerMove[0]);

    // Update the pattern frequency map
    if (humanMoves.size() >= 5) {
        pattern = QString(humanMoves.mid(humanMoves.size() - 5).toVector());
        patternFrequency[pattern]++;
        humanMoves.pop_front(); // Remove the oldest move to keep the last 4 moves
        pattern.chop(1); // Remove the first character to keep the last 4 moves
    }

    if (result == "You Win!") humanWins++;
    else if (result == "You Lose!") computerWins++;
    else ties++;

    HumanLabel->setText("Human Chooses: " + playerMove);
    PredictedLabel->setText("Predicted Human Choice: " + QString(algorithmComboBox->currentText() == "SMART" ? predictedMoveChoice : "Random"));
    CompLabel->setText("Computer Chooses: " + computerMove);
    WinnerLabel->setText("Winner: " + QString(result == "You Win!" ? "Human" : (result == "You Lose!" ? "Computer" : "Draw")));

    scoreLabel->setText(QString("Human: %1, Computer: %2, Ties: %3").arg(humanWins).arg(computerWins).arg(ties));
    roundLabel->setText(QString("Round: %1").arg(++currentRound));
}

QString MainWindow::getRandomMove()
{
    const QStringList moves = {"Rock", "Paper", "Scissors"};
    int index = QRandomGenerator::global()->bounded(3);
    return moves[index];
}

QString MainWindow::smartMove()
{
    // Ensure we have at least 4 moves to analyze
    if (humanMoves.size() < 4) {
        return getRandomMove(); // Fallback to random move if insufficient data
    }

    // Extract the last 4 moves as a pattern
    // QString pattern = humanMoves.mid(humanMoves.size() - 4).join("");

    // Predict the next move based on the most frequent pattern
    QString predictedMove;
    int maxFrequency = 0;

    for (const QString &key : patternFrequency.keys()) {
        if (key.startsWith(pattern) && patternFrequency[key] > maxFrequency) {
            maxFrequency = patternFrequency[key];
            predictedMove = key.right(1); // The predicted next move
        }
    }

    // If no prediction is possible, fallback to random move
    if (predictedMove.isEmpty()) {
        return getRandomMove();
    }

    // Counter the predicted move
    if (predictedMove == "R") {
        predictedMoveChoice = "Rock";
        return "Paper";
    } else if (predictedMove == "P") {
        predictedMoveChoice = "Paper";
        return "Scissors"; 
    } else if (predictedMove == "S") {
        predictedMoveChoice = "Scissors";
        return "Rock";
    }

    return getRandomMove(); // Fallback in case of unexpected input
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
