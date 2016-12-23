#include "mainwindow.h"

#include <iostream>
using namespace std;
#include <cmath>

MainWindow::MainWindow() {
    setFixedSize(250,280);

    lastClicked = new GameButton();

    initiate();
}

MainWindow::~MainWindow() {
    for (int i=0;i<=4;i++) {
        for (int j=0;j<=4;j++) {
            delete gameButtons[i][j];
            gameButtons[i][j] = 0;
        }
    }
    delete nbClicksLabel;
    nbClicksLabel = 0;
    delete reinitiate;
    reinitiate = 0;
    delete lastClicked;
    lastClicked = 0;
}

/**
 * Increment button value when clicked
 * @brief MainWindow::incrementButtonValue
 */
void MainWindow::incrementButtonValue() {
    // Incrementing number of clicks
    nbClicks++;
    QString nbClicksString(intToString(nbClicks).c_str());
    nbClicksLabel->setText(nbClicksString);

    // Incrementing button value
    GameButton *button = (GameButton *)sender();
    button->increment();
}

void MainWindow::markPushedAndFindConnected() {
    int a,b;

    // Incrementing number of clicks
    nbClicks++;
    QString nbClicksString(intToString(nbClicks).c_str());
    nbClicksLabel->setText(nbClicksString);

    GameButton *button = (GameButton *)sender();
    if (lastClicked == button) { //hasMarkedNeighbour
        for (int i=0;i<=4;i++) {
            for (int j=0;j<=4;j++) {
                if (gameButtons[i][j] == button) {
                    a = i;
                    b = j;
                }
            }
        }
        if (hasMarkedNeighbour(a,b)) {
            for (int i=0;i<=4;i++) {
                for (int j=0;j<=4;j++) {
                    if (gameButtons[i][j] == button) {
                        gameButtons[i][j]->setValue(gameButtons[i][j]->getValue()+1);

                    } else if(gameButtons[i][j]->isPushed()) {
                        gameButtons[i][j]->setValue(0);
                    }
                    gameButtons[i][j]->markUnPushed();
                }
            }
        } else {
            gameButtons[a][b]->markUnPushed();
        }
        lastClicked = new GameButton();
        bringBoardDown();
        if (button->getValue() == 10) {
            QMessageBox::information(this, "Congratulations!", "You managed to get 10!");
            reinitiateClick();
        }
    } else {
        for (int i=0;i<=4;i++) {
            for (int j=0;j<=4;j++) {
                if (gameButtons[i][j] == button) {
                    a = i;
                    b = j;
                } else {
                    gameButtons[i][j]->markUnPushed();
                }
            }
        }
        gameButtons[a][b]->markPushed();

        bool changed(true);
        while (changed) {
            changed = false;
            for (int i=0;i<=4;i++) {
                for (int j=0;j<=4;j++) {
                    if (hasMarkedNeighbour(i,j) && !(gameButtons[i][j]->isPushed())) {
                        gameButtons[i][j]->markPushed();
                        changed = true;
                    }
                }
            }
        }
        lastClicked = gameButtons[a][b];
    }
    if (!checkPossibilities()) {
        QMessageBox::information(this, "Game over", "There is no possibility left.");
        reinitiateClick();
    }
}

void MainWindow::reinitiateClick() {
    // Reset number of clicks
    nbClicks = 0;
    QString nbClicksString(intToString(nbClicks).c_str());
    nbClicksLabel->setText(nbClicksString);

    // Setting new value for game buttons
    for (int i=0;i<=4;i++) {
        for (int j=0;j<=4;j++) {
            int value = rand() % 5 + 1;
            gameButtons[i][j]->setValue(value);
            gameButtons[i][j]->markUnPushed();
        }
    }
}

void MainWindow::initiate() {
    // Creating game buttons
    for (int i=0;i<=4;i++) {
        for (int j=0;j<=4;j++) {
            int value = rand() % 5 + 1;
            QString valueToBeDisplayed(intToString(value).c_str());
            gameButtons[i][j] = new GameButton(valueToBeDisplayed, this, value);
            gameButtons[i][j]->setGeometry(i*50,j*50,50,50);

            //QObject::connect(gameButtons[i][j], SIGNAL(clicked()), this, SLOT(incrementButtonValue()));
            QObject::connect(gameButtons[i][j], SIGNAL(clicked()), this, SLOT(markPushedAndFindConnected()));
        }
    }

    // Dealing with number of clicks
    nbClicks = 0;
    QString valueToBeDisplayed(intToString(nbClicks).c_str());
    nbClicksLabel = new QLabel(valueToBeDisplayed, this);
    nbClicksLabel->setGeometry(70,250,50,20);

    // Rinitiating button
    reinitiate = new QPushButton("Reinitiate", this);
    reinitiate->setGeometry(140,252,80,25);
    QObject::connect(reinitiate, SIGNAL(clicked()), this, SLOT(reinitiateClick()));

}

bool MainWindow::hasMarkedNeighbour(int i, int j) {
    bool marked = false;
    if (i>0 && i<4 && j>0 && j<4) {
        if ((gameButtons[i-1][j]->isPushed() && gameButtons[i-1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i+1][j]->isPushed() && gameButtons[i+1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j-1]->isPushed() && gameButtons[i][j-1]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j+1]->isPushed() && gameButtons[i][j+1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if(i>0 && i<4 && j>0) {
        if ((gameButtons[i-1][j]->isPushed() && gameButtons[i-1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i+1][j]->isPushed() && gameButtons[i+1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j-1]->isPushed() && gameButtons[i][j-1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if (i>0 && i<4 && j<4) {
        if ((gameButtons[i-1][j]->isPushed() && gameButtons[i-1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i+1][j]->isPushed() && gameButtons[i+1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j+1]->isPushed() && gameButtons[i][j+1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if (i>0 && j>0 && j<4) {
        if ((gameButtons[i-1][j]->isPushed() && gameButtons[i-1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j-1]->isPushed() && gameButtons[i][j-1]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j+1]->isPushed() && gameButtons[i][j+1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if (i<4 && j>0 && j<4) {
        if ((gameButtons[i+1][j]->isPushed() && gameButtons[i+1][j]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j-1]->isPushed() && gameButtons[i][j-1]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[i][j+1]->isPushed() && gameButtons[i][j+1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if(i==0 && j==0) {
        if ((gameButtons[1][0]->isPushed() && gameButtons[1][0]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[0][1]->isPushed() && gameButtons[0][1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if(i==4 && j==0) {
        if ((gameButtons[3][0]->isPushed() && gameButtons[3][0]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[4][1]->isPushed() && gameButtons[4][1]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if(i==0 && j==4) {
        if ((gameButtons[1][4]->isPushed() && gameButtons[1][4]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[0][3]->isPushed() && gameButtons[0][3]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    } else if(i==4 && j==4) {
        if ((gameButtons[4][3]->isPushed() && gameButtons[4][3]->getValue()==gameButtons[i][j]->getValue()) || (gameButtons[3][4]->isPushed() && gameButtons[3][4]->getValue()==gameButtons[i][j]->getValue())) {
            marked = true;
        }
    }

    return marked;
}

void MainWindow::bringBoardDown() {

    bool changed;
    for (int i=0;i<=4;i++) {
        changed = true;
        while (changed) {
            changed = false;
            for (int j=4;j>=1;j--) {
                if (gameButtons[i][j]->getValue() == 0 && gameButtons[i][j-1]->getValue() > 0) {
                    int value = gameButtons[i][j]->getValue();
                    gameButtons[i][j]->setValue(gameButtons[i][j-1]->getValue());
                    gameButtons[i][j-1]->setValue(value);
                    changed = true;
                }
            }
        }
    }

    for (int i=0;i<=4;i++) {
        for (int j=0;j<=4;j++) {
            if (gameButtons[i][j]->getValue() == 0) {
                gameButtons[i][j]->setValue(rand() % 5 + 1);
            }
        }
    }
}

bool MainWindow::checkPossibilities() {
    for (int i=0;i<=4;i++) {
        for (int j=0;j<=4;j++) {
            for (int k=0;k<=4;k++) {
                for (int l=0;l<=4;l++) {
                    if (gameButtons[i][j]->getValue() == gameButtons[k][l]->getValue() && sqrt(pow((i-k),2)+pow((j-l),2)) == 1) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
