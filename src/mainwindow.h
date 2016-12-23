#include <QWidget>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QMessageBox>

#include "gamebutton.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow: public QWidget {

    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();
        void initiate();

    public slots:
        void incrementButtonValue();
        void markPushedAndFindConnected();
        void reinitiateClick();
        bool hasMarkedNeighbour(int i, int j);
        void bringBoardDown();
        bool checkPossibilities();

    private:
        int buttonValues[5][5];
        GameButton* gameButtons[5][5];
        QLabel* nbClicksLabel;
        int nbClicks;
        QPushButton* reinitiate;
        GameButton* lastClicked;

};

#endif // MAINWINDOW_H
