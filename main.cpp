#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFont font;
    font.setPixelSize(14);
    a.setFont(font);

    MainWindow *window = new MainWindow();
    window->show();

    return QApplication::exec();
}
