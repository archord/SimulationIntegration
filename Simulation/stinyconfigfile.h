#ifndef STINYCONFIGFILE_H
#define STINYCONFIGFILE_H

#include <QtWidgets>

#define MAX_STRING      255

class StinyConfigFile
{
private:
    int cameraType;
    char parmFilePrefix[MAX_STRING];
    char positionFile[MAX_STRING];
    int x;
    int y;
    int bandpassType;
    float waveLength;
    char  curveFile[MAX_STRING];
    int objectSpectrum;
    float temperature;
    float alpha;
    float beta;
    char spectrumFile[MAX_STRING];
    float psfSize;
    char subsampledPSF;
    int subsampleFactor;
    char rootname[MAX_STRING];
/*
    int cameraType;
    QString parmFilePrefix;
    QString positionFile;
    int x;
    int y;
    int bandpassType;
    float waveLength;
    QString  curveFile;
    int objectSpectrum;
    float temperature;
    float alpha;
    float beta;
    QString spectrumFile;
    float psfSize;
    char subsampledPSF;
    int subsampleFactor;
    QString rootname;*/

public:
    StinyConfigFile();
    char *getLine1(FILE *file, char *line );
    void strupcase(char *string);
    int parseParm(char *line);
    int getParmFromConfFile(char *parmConfiglfile);
    void setRootName(char *rootName);
    int writeConfigFile(char *path);
    int isEmpty(char *line );
};

#endif // STINYCONFIGFILE_H
