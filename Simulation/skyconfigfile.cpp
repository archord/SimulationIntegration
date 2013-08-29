#include "skyconfigfile.h"

SkyConfigFile::SkyConfigFile()
{
}

int SkyConfigFile::isEmpty(char *line )
{
    /* Remove any comments at the end of the line by placing a \0  *
     * after the last parameter value on the line.                 */

    char *n = strchr( line, '#' );
    if ( n != NULL )
    {
        --n;
        /* Work backwards to the last visible character */
        while ( (n+1-line) > 0  && !isgraph(*n))
            *n-- = '\0';
    }

    int len = strlen(line);
    int i;
    for(i=0; i<len; i++)
    {
        if(isgraph(line[i]))
        {
            return 0;
        }
    }
    return 1;
}


char *SkyConfigFile::getLine1( FILE *file, char *line )
{


    if ( fgets( line, MAX_STRING - 1, file ) == NULL )
    {
        line[0] = '\0';
        return line;
    }

    while ( isEmpty(line) == 1 || line[0] == '#' || line[0] == '\n' || line[0] == '\r')
    {
        if ( fgets( line, MAX_STRING - 1, file ) == NULL )
        {
            line[0] = '\0';
            return line;
        }
    }


    return( line );

} /* getLine */

void SkyConfigFile::strupcase(char *string)
{
    while(*string != '\0')
    {
        *string = (char)toupper(*string);
        ++string;
    }
}

int SkyConfigFile::parseParm(char *line)
{
    int flag = 1;
    //static QString pName;
    //static QString pValue;
    static char pName[MAX_STRING];
    static char pValue[MAX_STRING];
    memset(pName, 0, MAX_STRING);
    memset(pValue, 0, MAX_STRING);
    sscanf(line, "%s %s", pName, pValue);
    strupcase(pName);

    if(strcmp(pName, "IMAGE_NAME") == 0)
    {
        sscanf(pValue, "%s", imageName);
    }else if(strcmp(pName, "IMAGE_SIZE") == 0)
    {
        sscanf(pValue, "%d", &imageSize);
    }else if(strcmp(pName, "IMAGE_TYPE") == 0)
    {
        sscanf(pValue, "%s", imageType);
    }else if(strcmp(pName, "GRID_SIZE") == 0)
    {
        sscanf(pValue, "%d", &gridSize);
    }else if(strcmp(pName, "IMAGE_HEADER") == 0)
    {
        sscanf(pValue, "%s", imageHeader);
    }else if(strcmp(pName, "GAIN") == 0)
    {
        sscanf(pValue, "%f", &gain);
    }else if(strcmp(pName, "WELL_CAPACITY") == 0)
    {
        sscanf(pValue, "%d", &wellCapacity);
    }else if(strcmp(pName, "SATUR_LEVEL") == 0)
    {
        sscanf(pValue, "%ld", &saturLevel);
    }else if(strcmp(pName, "READOUT_NOISE") == 0)
    {
        sscanf(pValue, "%f", &readoutNoise);
    }else if(strcmp(pName, "EXPOSURE_TIME") == 0)
    {
        sscanf(pValue, "%f", &exposureTime);
    }else if(strcmp(pName, "MAG_ZEROPOINT") == 0)
    {
        sscanf(pValue, "%f", &magZeropoint);
    }else if(strcmp(pName, "PIXEL_SIZE") == 0)
    {
        sscanf(pValue, "%f", &pixelSize);
    }else if(strcmp(pName, "MICROSCAN_NSTEP") == 0)
    {
        sscanf(pValue, "%d", &microscanNstep);
    }else if(strcmp(pName, "PSF_TYPE") == 0)
    {
        sscanf(pValue, "%s", psfType);
    }else if(strcmp(pName, "PSF_NAME") == 0)
    {
        sscanf(pValue, "%s", psfName);
    }else if(strcmp(pName, "SEEING_TYPE") == 0)
    {
        sscanf(pValue, "%s", seeingType);
    }else if(strcmp(pName, "SEEING_FWHM") == 0)
    {
        sscanf(pValue, "%f", &seeingFwhm);
    }else if(strcmp(pName, "AUREOLE_RADIUS") == 0)
    {
        sscanf(pValue, "%d", &aureoleRadius);
    }else if(strcmp(pName, "AUREOLE_SB") == 0)
    {
        sscanf(pValue, "%f", &aureoleSb);
    }else if(strcmp(pName, "PSF_OVERSAMP") == 0)
    {
        sscanf(pValue, "%d", &psfOversamp);
    }else if(strcmp(pName, "PSF_MAPSIZE") == 0)
    {
        sscanf(pValue, "%d", &psfMapsize);
    }else if(strcmp(pName, "TRACKERROR_TYPE") == 0)
    {
        sscanf(pValue, "%s", trackErrorType);
    }else if(strcmp(pName, "TRACKERROR_MAJ") == 0)
    {
        sscanf(pValue, "%f", &trackErrorMaj);
    }else if(strcmp(pName, "TRACKERROR_MIN") == 0)
    {
        sscanf(pValue, "%f", &trackErrorMin);
    }else if(strcmp(pName, "TRACKERROR_ANG") == 0)
    {
        sscanf(pValue, "%f", &trackErrorAng);
    }else if(strcmp(pName, "M1_DIAMETER") == 0)
    {
        sscanf(pValue, "%f", &m1Diameter);
    }else if(strcmp(pName, "M2_DIAMETER") == 0)
    {
        sscanf(pValue, "%f", &m2Diameter);
    }else if(strcmp(pName, "ARM_COUNT") == 0)
    {
        sscanf(pValue, "%d", &armCount);
    }else if(strcmp(pName, "ARM_THICKNESS") == 0)
    {
        sscanf(pValue, "%f", &armThickness);
    }else if(strcmp(pName, "ARM_POSANGLE") == 0)
    {
        sscanf(pValue, "%f", &armPosangle);
    }else if(strcmp(pName, "DEFOC_D80") == 0)
    {
        sscanf(pValue, "%f", &defocD80);
    }else if(strcmp(pName, "SPHER_D80") == 0)
    {
        sscanf(pValue, "%f", &spherD80);
    }else if(strcmp(pName, "COMAX_D80") == 0)
    {
        sscanf(pValue, "%f", &comaxD80);
    }else if(strcmp(pName, "COMAY_D80") == 0)
    {
        sscanf(pValue, "%f", &comayD80);
    }else if(strcmp(pName, "AST00_D80") == 0)
    {
        sscanf(pValue, "%f", &ast00D80);
    }else if(strcmp(pName, "AST45_D80") == 0)
    {
        sscanf(pValue, "%f", &ast45D80);
    }else if(strcmp(pName, "TRI00_D80") == 0)
    {
        sscanf(pValue, "%f", &tri00D80);
    }else if(strcmp(pName, "TRI30_D80") == 0)
    {
        sscanf(pValue, "%f", &tri30D80);
    }else if(strcmp(pName, "QUA00_D80") == 0)
    {
        sscanf(pValue, "%f", &qua00D80);
    }else if(strcmp(pName, "QUA22_D80") == 0)
    {
        sscanf(pValue, "%f", &qua22D80);
    }else if(strcmp(pName, "WAVELENGTH") == 0)
    {
        sscanf(pValue, "%f", &waveLength);
    }else if(strcmp(pName, "BACK_MAG") == 0)
    {
        sscanf(pValue, "%f", &backMag);
    }else if(strcmp(pName, "STARCOUNT_ZP") == 0)
    {
        sscanf(pValue, "%s", starCountZp);
    }else if(strcmp(pName, "STARCOUNT_SLOPE") == 0)
    {
        sscanf(pValue, "%f", &starCountSlope);
    }else if(strcmp(pName, "MAG_LIMITS") == 0)
    {
        sscanf(pValue, "%f,%f", &magLimits[0], &magLimits[1]);
    }else if(strcmp(pName, "SEED_MOTION") == 0)
    {
        sscanf(pValue, "%d", &seedMotion);
    }else if(strcmp(pName, "SEED_STARPOS") == 0)
    {
        sscanf(pValue, "%d", &seedStarpos);
    }else if(strcmp(pName, "VERBOSE_TYPE") == 0)
    {
        sscanf(pValue, "%s", verboseType);
    }else if(strcmp(pName, "NTHREADS") == 0)
    {
        sscanf(pValue, "%d", &nthreads);
    }else{
        flag = 0;
    }
    return flag;
}

int SkyConfigFile::getParmFromConfFile(char *parmConfiglfile)
{
    if(parmConfiglfile == NULL){
        return 0;
    }

    int flag = 1;
    char line[MAX_STRING];

    FILE *fp = fopen(parmConfiglfile, "r");
    if(fp != NULL)
    {
        getLine1(fp, line);
        while(line[0] != '\0')
        {
            int flag = parseParm(line);
            if(flag == 0){
                flag = 0;
                break;
            }
            getLine1(fp, line);
        }
        fclose(fp);
    }else{
        flag = 0;
    }

    return flag;
}

int SkyConfigFile::writeConfigFile(char *path)
{
    if(path == NULL){
        return 0;
    }

    int flag = 1;

    FILE *fp = fopen(path, "w");
    if(fp != NULL)
    {
        fprintf(fp, "# Default configuration file for SkyMaker 3.3.3\n");
        fprintf(fp, "# EB 2010-04-13\n");
        fprintf(fp, "#\n");
        fprintf(fp, "\n");
        fprintf(fp, "#--------------------------------- Image -------------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "IMAGE_NAME\t\t%s\t\t", imageName);
        fprintf(fp, "# Name of the output frame\n");
        fprintf(fp, "IMAGE_SIZE\t\t%d\t\t\t", imageSize);
        fprintf(fp, "# Width,[height] of the output frame\n");
        fprintf(fp, "IMAGE_TYPE\t\t%s\t\t\t\t", imageType);
        fprintf(fp, "# PUPIL_REAL,PUPIL_IMAGINARY,PUPIL_MODULUS,\n");
        fprintf(fp, "                                # PUPIL_PHASE,PUPIL_MTF,PSF_MTF,PSF_FULLRES,\n");
        fprintf(fp, "                                # PSF_FINALRES,SKY_NONOISE,SKY,GRID\n");
        fprintf(fp, "                                # or GRID_NONOISE\n");
        fprintf(fp, "GRID_SIZE\t\t%d\t\t\t\t", gridSize);
        fprintf(fp, "# Distance between objects in GRID mode\n");
        fprintf(fp, "IMAGE_HEADER\t%s\t\t", imageHeader);
        fprintf(fp, "# File name or INTERNAL\n");
        fprintf(fp, "\n");
        fprintf(fp, "#-------------------------------- Detector -----------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "GAIN\t\t\t%.1f\t\t\t\t", gain);
        fprintf(fp, "# gain (e-/ADU)\n");
        fprintf(fp, "WELL_CAPACITY\t%d\t\t\t\t", wellCapacity);
        fprintf(fp, "# full well capacity in e- (0 = infinite)\n");
        fprintf(fp, "SATUR_LEVEL\t\t%ld\t\t\t", saturLevel);
        fprintf(fp, "# saturation level (ADU)\n");
        fprintf(fp, "READOUT_NOISE\t%.1f\t\t\t\t", readoutNoise);
        fprintf(fp, "# read-out noise (e-)\n");
        fprintf(fp, "EXPOSURE_TIME\t%.1f\t\t\t", exposureTime);
        fprintf(fp, "# total exposure time (s)\n");
        fprintf(fp, "MAG_ZEROPOINT\t%.1f\t\t\t", magZeropoint);
        fprintf(fp, "# magnitude zero-point (\"ADU per second\")\n");
        fprintf(fp, "\n");
        fprintf(fp, "#-------------------------------- Sampling -----------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "PIXEL_SIZE\t\t%.3f\t\t\t", pixelSize);
        fprintf(fp, "# pixel size in arcsec.\n");
        fprintf(fp, "MICROSCAN_NSTEP\t%d\t\t\t\t", microscanNstep);
        fprintf(fp, "# number of microscanning steps (1=no mscan)\n");
        fprintf(fp, "\n");
        fprintf(fp, "#---------------------------------- PSF --------------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "PSF_TYPE\t\t%s\t\t", psfType);
        fprintf(fp, "# INTERNAL or FILE\n");
        fprintf(fp, "PSF_NAME\t\t%s\t\t", psfName);
        fprintf(fp, "# Name of the FITS image containing the PSF\n");
        fprintf(fp, "SEEING_TYPE\t\t%s\t", seeingType);
        fprintf(fp, "# (NONE, LONG_EXPOSURE or SHORT_EXPOSURE)\n");
        fprintf(fp, "SEEING_FWHM\t\t%.1f\t\t\t\t", seeingFwhm);
        fprintf(fp, "# FWHM of seeing in arcsec (incl. motion)\n");
        fprintf(fp, "AUREOLE_RADIUS\t%d\t\t\t\t", aureoleRadius);
        fprintf(fp, "# Range covered by aureole (pix) 0=no aureole\n");
        fprintf(fp, "AUREOLE_SB\t\t%.1f\t\t\t", aureoleSb);
        fprintf(fp, "# SB (mag/arcsec2) at 1' from a 0-mag star\n");
        fprintf(fp, "PSF_OVERSAMP\t%d\t\t\t\t", psfOversamp);
        fprintf(fp, "# Oversampling factor / final resolution\n");
        fprintf(fp, "PSF_MAPSIZE\t\t%d\t\t\t", psfMapsize);
        fprintf(fp, "# PSF mask size (pixels): must be a power of 2\n");
        fprintf(fp, "TRACKERROR_TYPE\t%s\t\t\t", trackErrorType);
        fprintf(fp, "# Tracking error model: NONE, DRIFT or JITTER\n");
        fprintf(fp, "TRACKERROR_MAJ\t%.1f\t\t\t\t", trackErrorMaj);
        fprintf(fp, "# Tracking RMS error (major axis) (in arcsec)\n");
        fprintf(fp, "TRACKERROR_MIN\t%.1f\t\t\t\t", trackErrorMin);
        fprintf(fp, "# Tracking RMS error (minor axis) (in arcsec)\n");
        fprintf(fp, "TRACKERROR_ANG\t%.1f\t\t\t\t", trackErrorAng);
        fprintf(fp, "# Tracking angle (in deg, CC/horizontal)\n");
        fprintf(fp, "\n");
        fprintf(fp, "#----------------------------- Pupil features --------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "M1_DIAMETER\t\t%.1f\t\t\t\t", m1Diameter);
        fprintf(fp, "# Diameter of the primary mirror (in meters)\n");
        fprintf(fp, "M2_DIAMETER\t\t%.1f\t\t\t\t", m2Diameter);
        fprintf(fp, "# Obstruction diam. from the 2nd mirror in m.\n");
        fprintf(fp, "ARM_COUNT\t\t%d\t\t\t\t", armCount);
        fprintf(fp, "# Number of spider arms (0 = none)\n");
        fprintf(fp, "ARM_THICKNESS\t%.1f\t\t\t", armThickness);
        fprintf(fp, "# Thickness of the spider arms (in mm)\n");
        fprintf(fp, "ARM_POSANGLE \t%.1f\t\t\t\t", armPosangle);
        fprintf(fp, "# Position angle of the spider pattern / AXIS1\n");
        fprintf(fp, "DEFOC_D80\t\t%.1f\t\t\t\t", defocD80);
        fprintf(fp, "# Defocusing d80%% diameter (arcsec)\n");
        fprintf(fp, "SPHER_D80\t\t%.1f\t\t\t\t", spherD80);
        fprintf(fp, "# Spherical d80%% diameter (arcsec)\n");
        fprintf(fp, "COMAX_D80\t\t%.1f\t\t\t\t", comaxD80);
        fprintf(fp, "# Coma along X d80%% diameter (arcsec)\n");
        fprintf(fp, "COMAY_D80\t\t%.1f\t\t\t\t", comayD80);
        fprintf(fp, "# Coma along Y d80%% diameter (arcsec)\n");
        fprintf(fp, "AST00_D80\t\t%.1f\t\t\t\t", ast00D80);
        fprintf(fp, "# 0 deg. astigmatism d80%% diameter (arcsec)\n");
        fprintf(fp, "AST45_D80\t\t%.1f\t\t\t\t", ast45D80);
        fprintf(fp, "# 45 deg. astigmatism d80%% diameter (arcsec)\n");
        fprintf(fp, "TRI00_D80\t\t%.1f\t\t\t\t", tri00D80);
        fprintf(fp, "# 0 deg. triangular d80%% diameter (arcsec)\n");
        fprintf(fp, "TRI30_D80\t\t%.1f\t\t\t\t", tri30D80);
        fprintf(fp, "# 30 deg. triangular d80%% diameter (arcsec)\n");
        fprintf(fp, "QUA00_D80\t\t%.1f\t\t\t\t", qua00D80);
        fprintf(fp, "# 0 deg. quadratic d80%% diameter (arcsec)\n");
        fprintf(fp, "QUA22_D80\t\t%.1f\t\t\t\t", qua22D80);
        fprintf(fp, "# 22.5 deg. quadratic d80%% diameter (arcsec)\n");
        fprintf(fp, "\n");
        fprintf(fp, "#--------------------------------- Signal ------------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "WAVELENGTH\t\t%.1f\t\t\t\t", waveLength);
        fprintf(fp, "# average wavelength analysed (microns)\n");
        fprintf(fp, "BACK_MAG\t\t%.1f\t\t\t", backMag);
        fprintf(fp, "# background surface brightness (mag/arcsec2)\n");
        fprintf(fp, "\n");
        fprintf(fp, "#------------------------------ Stellar field --------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "STARCOUNT_ZP\t%s\t\t\t\t", starCountZp);
        fprintf(fp, "# nb of stars /deg2 brighter than MAG_LIMITS\n");
        fprintf(fp, "STARCOUNT_SLOPE\t%.1f\t\t\t\t", starCountSlope);
        fprintf(fp, "# slope of differential star counts (dexp/mag)\n");
        fprintf(fp, "MAG_LIMITS\t\t%.1f,%.1f\t\t", magLimits[0], magLimits[1]);
        fprintf(fp, "# stellar magnitude range allowed\n");
        fprintf(fp, "\n");
        fprintf(fp, "#------------------------------ Random Seeds ---------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "SEED_MOTION\t\t%d\t\t\t\t", seedMotion);
        fprintf(fp, "# rand. seed for PSF turbulent motion (0=time)\n");
        fprintf(fp, "SEED_STARPOS\t%d\t\t\t\t", seedStarpos);
        fprintf(fp, "# random seed for star positions (0=time)\n");
        fprintf(fp, "\n");
        fprintf(fp, "#----------------------------- Miscellaneous ---------------------------------\n");
        fprintf(fp, "\n");
        fprintf(fp, "VERBOSE_TYPE\t%s\t\t\t", verboseType);
        fprintf(fp, "# QUIET, NORMAL or FULL\n");
        fprintf(fp, "NTHREADS\t\t%d\t\t\t\t", nthreads);
        fprintf(fp, "# Number of simultaneous threads for\n");
        fprintf(fp, "                                # the SMP version of SkyMaker\n");

        fclose(fp);
    }else{
        flag = 0;
    }

    return flag;
}

char* SkyConfigFile::getImageName() {
    return psfName;
}

void SkyConfigFile::setImageName(char *imageName) {
    strcpy(this->imageName, imageName);
}

float SkyConfigFile::getExposureTime() {
    return exposureTime;
}

void SkyConfigFile::setExposureTime(float exposureTime) {
    this->exposureTime = exposureTime;
}

float SkyConfigFile::getM1Diameter() {
    return m1Diameter;
}

void SkyConfigFile::setM1Diameter(float m1Diameter) {
    this->m1Diameter = m1Diameter;
}

char* SkyConfigFile::getPsfName() {
    return psfName;
}

void SkyConfigFile::setPsfName(char *psfName) {
    strcpy(this->psfName, psfName);
}

float SkyConfigFile::getReadoutNoise() {
    return readoutNoise;
}

void SkyConfigFile::setReadoutNoise(float readoutNoise) {
    this->readoutNoise = readoutNoise;
}

float SkyConfigFile::getGain() {
    return gain;
}

void SkyConfigFile::setGain(float gain) {
    this->gain = gain;
}

float SkyConfigFile::getPixelSize() {
    return pixelSize;
}

void SkyConfigFile::setPixelSize(float pixelSize) {
    this->pixelSize = pixelSize;
}

int SkyConfigFile::getImageSize() {
    return imageSize;
}

void SkyConfigFile::setImageSize(int imageSize) {
    this->imageSize = imageSize;
}

float SkyConfigFile::getMagZeropoint() {
    return magZeropoint;
}

void SkyConfigFile::setMagZeropoint(float magZeropoint) {
    this->magZeropoint = magZeropoint;
}

float SkyConfigFile::getTrackErrorMaj() {
    return trackErrorMaj;
}

void SkyConfigFile::setTrackErrorMaj(float trackErrorMaj) {
    this->trackErrorMaj = trackErrorMaj;
}

float SkyConfigFile::getTrackErrorMin() {
    return trackErrorMin;
}

void SkyConfigFile::setTrackErrorMin(float trackErrorMin) {
    this->trackErrorMin = trackErrorMin;
}
