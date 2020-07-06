#include "LocationMonitor.h"


LocationMonitor::LocationMonitor(QString givenPath){

    // Using QDir to get path

    directory = QDir(givenPath);

    watcher = new QFileSystemWatcher(this);

    // connecting watcher's directoryChanged SIGNAL
    // to locationMonitor's directoryChanged SLOT

    connect(watcher, SIGNAL(directoryChanged(const QString &)), this, SLOT(directoryChanged(const QString &)),Qt::UniqueConnection);

    // connecting watcher's fileChanged SIGNAL
    // to locationMonitor's fileChanged SLOT

    connect(watcher, SIGNAL(fileChanged(const QString &)), this, SLOT(fileChanged(const QString &)),Qt::UniqueConnection);


    // watch given location

    watcher->addPath(directory.absolutePath());

    // assign Files/Folders in current location to Set of current objects

    currentContent = getContent();

    // watch for files in above set
    // do not watch for sub-directories
    Q_FOREACH(MonitoredObject obj,currentContent){
        if(!QFileInfo(obj.path).isDir())
            watcher->addPath(obj.path);
    }

}

void LocationMonitor::directoryChanged(const QString & path){

    // create event
    Event event;

    // set of new files/folders
    QSet<MonitoredObject> newContent = getContent() - currentContent;

    //set of deleted files/folders
    QSet<MonitoredObject> deletedContent = currentContent - getContent();

    // check for renamed file/folders
    // if file exists in set of deleted and newly created file
    if(!newContent.isEmpty() && !deletedContent.isEmpty()){
        if(newContent.size() == 1 && deletedContent.size() == 1){

            // file before rename
            MonitoredObject oldObj = deletedContent.values().first();

            // file after rename
            MonitoredObject currentObj = newContent.values().first();

            // configure parameters of event type,path,operation
            event.type=currentObj.isFile;
            event.filePath = oldObj.path;
            event.eventType = EventType::Renamed;

            // print Event to console and append to logs.txt
            printChanges(event,currentObj.path);

            // apply changes in file to main set of currentContent
            currentContent-=oldObj;
            currentContent.insert(currentObj);
            if(!QFileInfo(currentObj.path).isDir())
                watcher->addPath(currentObj.path);
        }
    }
    // newly created file
    else
    if(!newContent.isEmpty()){

        // created file/folder object
        MonitoredObject currentObj = newContent.values().first();

        // configure parameters of event type,path,operation
        event.type=currentObj.isFile;
        event.filePath = currentObj.path;
        event.eventType = EventType::Created;

        // print Event to console and append to logs.txt
        printChanges(event);

        // add newly created file to currentContent Set
        currentContent.insert(currentObj);

        // watch for changes in new file
        if(!QFileInfo(currentObj.path).isDir())
            watcher->addPath(currentObj.path);
       }
    // deleted file
    else
    if(!deletedContent.isEmpty()){
        // deleted file/folder object
        MonitoredObject currentObj = deletedContent.values().first();

        // configure parameters of event type,path,operation
        event.type=currentObj.isFile;
        event.filePath = currentObj.path;
        event.eventType = EventType::Deleted;

        // print Event to console and append to logs.txt
        printChanges(event);

        //remove file from currentContent Set
        currentContent.remove(currentObj);
       }

}
// if file edited
void LocationMonitor::fileChanged(const QString & path){
    // check if file exists
    // editing a file also triggers "Delete" in some editors
    if(QFileInfo(path).exists())
        // print Event to console and append to logs.txt
        printChanges(Event(path,true,EventType::Edited));
}

//print Renamed Event to console and logs.txt
void LocationMonitor::printChanges(Event event, QString oldPath){
    // file renamed FROM xxx TO xxx
    QString info = event.toString() + " to "+oldPath;
    qDebug() << info;
    appendToLog(info);
}

// print other types of Event to console and append to logs.txt
void LocationMonitor::printChanges(Event event){
    QString info = event.toString();
    qDebug() << info;
    appendToLog(info);

}

// get Set of files/folders in current location
QSet<MonitoredObject> LocationMonitor::getContent(){

    QSet<MonitoredObject> inLocation;

    // get each file/folder's path and type from directory
    // ignore "." and ".." paths
    Q_FOREACH(QString content,directory.entryList(QStringList(),QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files)){
        QString tmpPath = directory.absolutePath()+"/"+content;
        inLocation.insert(MonitoredObject(QFileInfo(tmpPath).isFile(),tmpPath));
    }
    return inLocation;
}

// add informations about events to logs.txt
void LocationMonitor::appendToLog(QString info){
    // get current system date and time
    QDateTime dateTime = QDateTime::currentDateTime();
    // open file "logs.txt"
    QFile logFile("./logs.txt");
        if (logFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream logStream(&logFile);
            logStream <<dateTime.toString() +": "+ info+"\n";
        }

}
