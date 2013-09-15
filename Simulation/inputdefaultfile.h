#ifndef INPUTDEFAULTFILE_H
#define INPUTDEFAULTFILE_H

#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>

class InputDefaultFile
{
private:
    QString fileName;
    QList<QString> lines;
public:
    InputDefaultFile();
    bool readFile();
    void setFileName(QString defaultFileName);
    QString getValue(QString name);
    void replaceValue(QString name, QString value);
    bool writeFile();
};

#endif // INPUTDEFAULTFILE_H
