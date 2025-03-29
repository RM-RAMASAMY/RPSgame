#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <fstream>
#include<iostream>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void playRound(const QString &playerMove);
    void startGame();
    void readFreq();
    void writeFreq();

private:
    int totalRounds;
    int currentRound;
    int humanWins;
    int computerWins;
    int ties;

    QLabel *resultLabel;
    QLabel *scoreLabel;
    QLabel *roundLabel;
    QLabel *HumanLabel;
    QLabel *PredictedLabel;
    QLabel *CompLabel;
    QLabel *WinnerLabel;
    QComboBox *algorithmComboBox;
    QSpinBox *roundsSpinBox;
    QVector<QChar> humanMoves;
    QMap<QString, int> patternFrequency;
    QString pattern, predictedMoveChoice;
    QString getRandomMove();
    QString smartMove();
    QString determineResult(const QString &playerMove, const QString &computerMove);
};

#endif
