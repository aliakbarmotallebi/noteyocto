#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    app.setStyle("fusion");
    window.show();
    return app.exec();
}
