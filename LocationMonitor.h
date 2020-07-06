#ifndef LOCATIONMONITOR_H
#define LOCATIONMONITOR_H

#include "Logger.h"
#include "Event.h"
#include "MonitoredObject.h"

#include <QFileSystemWatcher>
#include <QObject>
#include <QSet>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QDataStream>
#include <QFile>
#include <QDataStream>
#include <QDateTime>

//main class, watches for all events in given location
class LocationMonitor : public QObject{

    Q_OBJECT

public:
    LocationMonitor(QString);

private:
    // set of current objects in given location
    QSet<MonitoredObject> currentContent;

    // given directory stored as QDir
    QDir directory;

    // get all objects in current location;
    QSet<MonitoredObject> getContent();

    // file system watcher
    QFileSystemWatcher * watcher;

    // add information to logs.txt
    void appendToLog(QString);

    //print changes to console (renamed)
    void printChanges(Event,QString);

    //print changes to console (others)
    void printChanges(Event);

    // slots to communicate with QFileSystemWatcher's directoryChanged
    // and fileChanged singals
private slots:
  void directoryChanged(const QString & path);
  void fileChanged(const QString & path);

};

#endif //LOCATIONMONITOR_H
