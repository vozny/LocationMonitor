#ifndef EVENT_H
#define EVENT_H

#include <QObject>

// enum type with event types
enum class EventType{
    Created = 0,
    Deleted = 1,
    Edited = 2,
    Renamed = 3
};

class Event{
public:
    Event();
    Event(QString path, bool type_, EventType eventType);
    QString getEventType();
    QString getType();
    QString toString();
    // Type of Event
    EventType eventType;

    // Path to the object that triggered event
    QString filePath;

    // TRUE if event refers to FILE
    // FALSE if event refers to FOLDER
    bool type = false;
};

#endif // EVENT_H
