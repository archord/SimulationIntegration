#ifndef SKYCONFIGFILE_H
#define SKYCONFIGFILE_H

#include <QtWidgets>

#define MAX_STRING 255
#define PATH_LENGTH 255
#define STRING_LENGTH 32

class SkyConfigFile
{
private:
    char  imageName[PATH_LENGTH];
    int   imageSize;
    char  imageType[STRING_LENGTH];

    int   gridSize;
    char  imageHeader[STRING_LENGTH];

    float gain;
    int   wellCapacity;
    long  saturLevel;
    float readoutNoise;
    float exposureTime;
    float magZeropoint;

    float pixelSize;
    int   microscanNstep;

    char  psfType[STRING_LENGTH];
    char  psfName[PATH_LENGTH];
    char  seeingType[STRING_LENGTH];
    float seeingFwhm;
    int   aureoleRadius;
    float aureoleSb;
    int   psfOversamp;
    int   psfMapsize;
    char  trackErrorType[STRING_LENGTH];
    float trackErrorMaj;
    float trackErrorMin;
    float trackErrorAng;

    float m1Diameter;
    float m2Diameter;
    int   armCount;
    float armThickness;
    float armPosangle;
    float defocD80;
    float spherD80;
    float comaxD80;
    float comayD80;
    float ast00D80;
    float ast45D80;
    float tri00D80;
    float tri30D80;
    float qua00D80;
    float qua22D80;

    float waveLength;
    float backMag;

    char  starCountZp[STRING_LENGTH];
    float starCountSlope;
    float magLimits[2];

    int   seedMotion;
    int   seedStarpos;

    char  verboseType[STRING_LENGTH];
    int   nthreads;




public:
    SkyConfigFile();

    int getParmFromConfFile(char *parmConfiglfile);
    int writeConfigFile(char *path);
    char *getLine1(FILE *file, char *line );
    void strupcase(char *string);
    int parseParm(char *line);
    int isEmpty(char *line );

    char* getImageName();
    float getExposureTime();
    float getM1Diameter();
    char  *getPsfName();
    float getReadoutNoise();
    float getGain();
    float getPixelSize();
    int   getImageSize();
    float getMagZeropoint();
    float getTrackErrorMaj();
    float getTrackErrorMin();

    void setImageName(char *imageName);
    void setExposureTime(float exposureTime);
    void setM1Diameter(float m1Diameter);
    void setPsfName(char *psfName);
    void setReadoutNoise(float readoutNoise);
    void setGain(float gain);
    void setPixelSize(float pixelSize);
    void setImageSize(int   imageSize);
    void setMagZeropoint(float magZeropoint);
    void setTrackErrorMaj(float trackErrorMaj);
    void setTrackErrorMin(float trackErrorMin);
};

#endif // SKYCONFIGFILE_H
