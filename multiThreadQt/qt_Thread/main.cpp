#include "mainwindow.h"

#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<MainWindow> mw = std::make_unique<MainWindow>();
    mw->show();

    return a.exec();
}
