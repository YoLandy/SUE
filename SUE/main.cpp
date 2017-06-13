#include <QApplication>
#include <QWidget>
#include "mainwindow.h"
#include "mmapGpio.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mainwindow *window = new mainwindow(0);

    window->show();
    return app.exec();
}
