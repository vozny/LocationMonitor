#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include <iostream>

class MainClass : public QObject
{
    Q_OBJECT

public:
    MainClass() { m_value = 0; }

    int value() const { return m_value; }

public slots:
    void setValue(const QString& str){
        std::cout<< "Modified";
    };

private:
    int m_value;
};
#endif // MAINCLASS_H
