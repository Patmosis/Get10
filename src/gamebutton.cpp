#include <iostream>
using namespace std;

#include "gamebutton.h"
#include "library.h"

GameButton::GameButton(const QString & text, QWidget * parent, int value): QPushButton(text, parent) {
    buttonValue = value;

    textColor = "rgb(0, 0, 0)";
    backgroundColor = "grey";

    this->setStyleSheet("color: red");
    setBackgroundColor();
    markUnPushed();
}

GameButton::GameButton() {

}

GameButton::~GameButton() {

}

/**
 * Increment button value when clicked
 * @brief MainWindow::incrementButtonValue
 */
void GameButton::increment() {
    buttonValue++;
    QString valueToBeDisplayed(intToString(buttonValue).c_str());
    this->setText(valueToBeDisplayed);
    setBackgroundColor();
}

void GameButton::setValue(int value) {
    QString valueToBeDisplayed(intToString(value).c_str());
    buttonValue = value;
    this->setText(valueToBeDisplayed);
    setBackgroundColor();
}

int GameButton::getValue() {
    return buttonValue;
}

void GameButton::setBackgroundColor() {
    switch (buttonValue) {
        case 1:
            backgroundColor = "rgb(0, 255, 0)";
            break;
        case 2:
            backgroundColor = "rgb(0, 0, 255)";
            break;
        case 3:
            backgroundColor = "rgb(255, 128, 0)";
            break;
        case 4:
            backgroundColor = "rgb(255, 0, 0)";
            break;
        case 5:
            backgroundColor = "rgb(0, 153, 73)";
            break;
        case 6:
            backgroundColor = "rgb(153, 0, 153)";
            break;
        case 7:
            backgroundColor = "rgb(255, 0, 127)";
            break;
        case 8:
            backgroundColor = "rgb(204, 0, 0)";
            break;
        case 9:
            backgroundColor = "rgb(255, 255, 0)";
            break;
        case 10:
            backgroundColor = "black";
            break;
        default:
            backgroundColor = "grey";
    }

    this->setStyleSheet("font: bold; font-size: 20px; background-color: "+backgroundColor+";color: "+textColor);
}

void GameButton::markPushed() {
    pushed = true;
    textColor = "rgb(255, 255, 255)";
    this->setStyleSheet("font: bold; font-size: 20px; background-color: "+backgroundColor+";color: "+textColor);
}

void GameButton::markUnPushed() {
    pushed = false;
    textColor = "rgb(0, 0, 0)";
    this->setStyleSheet("font: bold; font-size: 20px; background-color: "+backgroundColor+";color: "+textColor);
}

bool GameButton::isPushed() {
    return pushed;
}
