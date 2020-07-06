#include <QCoreApplication>
#include <QFileSystemWatcher>

#include <QDebug>
#include "LocationMonitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LocationMonitor locationMonitor(argv[1]);

    return a.exec();
}


