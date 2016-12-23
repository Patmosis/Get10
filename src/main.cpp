#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle(QString::fromUtf8("Get10"));
    mainWindow.show();

    return app.exec();
}
