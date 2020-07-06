#include "MonitoredObject.h"
#include <QString>


MonitoredObject::MonitoredObject(bool type,QString givenPath){
    isFile = type;
    path = givenPath;
}

bool MonitoredObject::operator==(const MonitoredObject &other) const{
    return isFile == other.isFile && path == other.path;
}
