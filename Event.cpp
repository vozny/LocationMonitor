#include "Event.h"

Event::Event(){

}

Event::Event(QString path, bool type, EventType eventType){
    this->filePath = path;
    this->type = type;
    this->eventType = eventType;
}

// get Event as string
QString Event::toString(){
    return getType()+" "+filePath+" "+getEventType();
}

// get file/folder type as string
QString Event::getType(){
    if(this->type)
        return "File";
    return "Folder";
}

// get event type as string
QString Event::getEventType(){

    switch (this->eventType) {
    case EventType::Created:
        return "Created";
    case EventType::Deleted:
        return "Deleted";
    case EventType::Edited:
        return "Edited";
    case EventType::Renamed:
        return "Renamed";
    default:
        return NULL;
    }
}
