#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void playRock();
    void playPaper();
    void playScissors();

private:
    QLabel *resultLabel;
    QString getRandomMove();
    QString determineResult(const QString &playerMove, const QString &computerMove);
};

#endif
