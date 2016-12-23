#include <QPushButton>

#include "library.h"

#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H


class GameButton: public QPushButton {

    Q_OBJECT

    public:
        GameButton(const QString & text, QWidget * parent = 0, int value = 0);
        GameButton();
        ~GameButton();
        void setValue(int value);
        void setBackgroundColor();
        void markPushed();
        void markUnPushed();
        bool isPushed();
        int getValue();

    public slots:
        void increment();

    private:
        int buttonValue;
        bool pushed;
        QString textColor;
        QString backgroundColor;

};

#endif // GAMEBUTTON_H
