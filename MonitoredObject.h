#ifndef MONITOREDOBJECT_H
#define MONITOREDOBJECT_H
#include <QString>
#include <QHash>

// class to store object's type and path
class MonitoredObject
{
public:
    MonitoredObject(bool,QString);

    bool operator==(const MonitoredObject &other) const;

    // TRUE if file
    // FALSE if folder
    bool isFile;
    QString path;
};

// qHash for MonitoredObject to compare it's values
inline uint qHash(const MonitoredObject &key, uint seed){
    return qHash(key.isFile, seed) ^ qHash(key.path, seed+1);
}

#endif // MONITOREDOBJECT_H
