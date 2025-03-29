#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void playRound(const QString &playerMove);
    void startGame();

private:
    int totalRounds;
    int currentRound;
    int humanWins;
    int computerWins;
    int ties;

    QLabel *resultLabel;
    QLabel *scoreLabel;
    QLabel *roundLabel;
    QComboBox *algorithmComboBox;
    QSpinBox *roundsSpinBox;
    QString getRandomMove();
    QString determineResult(const QString &playerMove, const QString &computerMove);
};

#endif
