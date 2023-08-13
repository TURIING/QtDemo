#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    //#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //#endif
    //qputenv("QT_SCALE_FACTOR", "1.25");
    QApplication a(argc, argv);

    QFont font;
    font.setPixelSize(14);
    a.setFont(font);

    MainWindow *window = new MainWindow();
    window->show();

    return QApplication::exec();
}
