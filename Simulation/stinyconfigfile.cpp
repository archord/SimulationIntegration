
#include "stinyconfigfile.h"

StinyConfigFile::StinyConfigFile()
{
}

int StinyConfigFile::isEmpty(char *line )
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


char *StinyConfigFile::getLine1( FILE *file, char *line )
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

/*
char *StinyConfigFile::getLine1( FILE *file, char *line )
{
    char    *n;

    if ( fgets( line, MAX_STRING - 1, file ) == NULL )
    {
        line[0] = '\0';
        return line;
    }

    while ( line[0] == '#' || line[0] == '\n' || line[0] == '\r')
    {
        if ( fgets( line, MAX_STRING - 1, file ) == NULL )
        {
            line[0] = '\0';
            return line;
        }
    }


    n = strchr( line, '#' );
    if ( n != NULL )
    {
        --n;

        while ( !isgraph(*n) )
            *n-- = '\0';
    }

    return( line );

}*/

void StinyConfigFile::strupcase(char *string)
{
    while(*string != '\0')
    {
        *string = (char)toupper(*string);
        ++string;
    }
}

int StinyConfigFile::parseParm(char *line)
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

    if(strcmp(pName, "CAMERATYPE") == 0)
    {
        sscanf(pValue, "%d", &cameraType);
    }else if(strcmp(pName, "PARMFILEPREFIX") == 0)
    {
        sscanf(pValue, "%s", parmFilePrefix);
    }else if(strcmp(pName, "POSITIONFILE") == 0)
    {
        sscanf(pValue, "%s", positionFile);
    }else if(strcmp(pName, "X") == 0)
    {
        sscanf(pValue, "%d", &x);
    }else if(strcmp(pName, "Y") == 0)
    {
        sscanf(pValue, "%d", &y);
    }else if(strcmp(pName, "BANDPASSTYPE") == 0)
    {
        sscanf(pValue, "%d", &bandpassType);
    }else if(strcmp(pName, "WAVELENGTH") == 0)
    {
        sscanf(pValue, "%f", &waveLength);
    }else if(strcmp(pName, "CURVEFILE") == 0)
    {
        sscanf(pValue, "%s", curveFile);
    }else if(strcmp(pName, "OBJECTSPECTRUM") == 0)
    {
        sscanf(pValue, "%d", &objectSpectrum);
    }else if(strcmp(pName, "TEMPERATURE") == 0)
    {
        sscanf(pValue, "%f", &temperature);
    }else if(strcmp(pName, "ALPHA") == 0)
    {
        sscanf(pValue, "%f", &alpha);
    }else if(strcmp(pName, "BETA") == 0)
    {
        sscanf(pValue, "%f", &beta);
    }else if(strcmp(pName, "SPECTRUMFILE") == 0)
    {
        sscanf(pValue, "%s", spectrumFile);
    }else if(strcmp(pName, "PSFSIZE") == 0)
    {
        sscanf(pValue, "%f", &psfSize);
    }else if(strcmp(pName, "SUBSAMPLEDPSF") == 0)
    {
        sscanf(pValue, "%c", &subsampledPSF);
    }else if(strcmp(pName, "SUBSAMPLEFACTOR") == 0)
    {
        sscanf(pValue, "%d", &subsampleFactor);
    }else if(strcmp(pName, "ROOTNAME") == 0)
    {
        sscanf(pValue, "%s", rootname);
    }else{
        flag = 0;
    }
    return flag;
}

int StinyConfigFile::getParmFromConfFile(char *parmConfiglfile)
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

void StinyConfigFile::setRootName(char *rootName)
{
    strcpy(this->rootname, rootName);
}

int StinyConfigFile::writeConfigFile(char *path)
{
    if(path == NULL){
        return 0;
    }

    int flag = 1;

    FILE *fp = fopen(path, "w");
    if(fp != NULL)
    {
        fprintf(fp, "\n");
        fprintf(fp, "#1\n");
        fprintf(fp, "#IRAC camera type:\n");
        fprintf(fp, "#1) Channel 1 (3.5 microns), if chose 1,2,3,4, don't need specify the cameraName\n");
        fprintf(fp, "#2) Channel 2 (4.5 microns)\n");
        fprintf(fp, "#3) Channel 3 (6.3 microns)\n");
        fprintf(fp, "#4) Channel 4 (8.0 microns)\n");
        fprintf(fp, "#5) user define camera, if chose 5, must specify the camera parameter file prefix\n");
        fprintf(fp, "cameraType\t%d\t\t\t", cameraType);
        fprintf(fp, "#must chose from 1,2,3,4,5\n");
        fprintf(fp, "parmFilePrefix\t%s\t", parmFilePrefix);
        fprintf(fp, "#camera parameter file prefix, the value is \"null\" or \"fileName\"\n");
        fprintf(fp, "\n");

        fprintf(fp, "#2\n");
        fprintf(fp, "#1) position list file name, if \"positionFile\" is specified, the value of X & Y will be ignore\n");
        fprintf(fp, "#2) X & Y position on detector in integer pixels\n");
        fprintf(fp, "positionFile\t%s\t", positionFile);
        fprintf(fp, "# if don't want to use this,the value of positionFile must be null\n");
        fprintf(fp, "X\t%d\t\t\t\t\t", x);
        fprintf(fp, "#256*256\n");
        fprintf(fp, "Y\t%d\t\t\t\t\t", y);
        fprintf(fp, "#\n");
        fprintf(fp, "\n");

        fprintf(fp, "#3\n");
        fprintf(fp, "#bandpass type, the value is 1,2,3\n");
        fprintf(fp, "#1) Use default throughput curve, if chose 1, the wavelength and curveFile will be ignored\n");
        fprintf(fp, "#2) Specify a single wavelength,  if chose 2, the wavelength must be specified\n");
        fprintf(fp, "#3) Use a user-supplied throughput curve, if chose 3, the curveFile must be specified\n");
        fprintf(fp, "bandpassType\t%d\t\t", bandpassType);
        fprintf(fp, "#must chose from 1,2,3\n");
        fprintf(fp, "#IRAC1 2.5 ~ 4.5, IRAC2 3.5 ~ 5.5, IRAC3 4.5 ~ 7.0, IRAC4 6.0 ~ 10.0 \n");
        fprintf(fp, "waveLength\t%.1f\t\t\t", waveLength);
        fprintf(fp, "#valid when bandpassType equals 2\n");
        fprintf(fp, "curveFile\t%s\t\t", curveFile);
        fprintf(fp, "#file name, valid when bandpassType equals 3\n");
        fprintf(fp, "\n");

        fprintf(fp, "#4\n");
        fprintf(fp, "#object spectrum if the procedure #3 chose 1 or 3, should specify one of the following\n");
        fprintf(fp, "#1)Blackbody,                          if select 1: temperature (Kelvin)\n");
        fprintf(fp, "#2)Power law : F(nu) = nu^i,           if select 2: spectral index (alpha)\n");
        fprintf(fp, "#3)Power law : F(lambda) = lambda^i,   if select 3: spectral index (beta)\n");
        fprintf(fp, "#4)User-provided spectrum,             if select 4: name of spectrum file\n");
        fprintf(fp, "objectSpectrum\t%d\t\t", objectSpectrum);
        fprintf(fp, "#must chose from 1,2,3,4\n");
        fprintf(fp, "temperature\t%.1f\t\t", temperature);
        fprintf(fp, "#1.0 ~ 900000.0\n");
        fprintf(fp, "alpha\t%.1f\n", alpha);
        fprintf(fp, "beta\t%.1f\n", beta);
        fprintf(fp, "spectrumFile\t%s\n", spectrumFile);
        fprintf(fp, "\n");

        fprintf(fp, "#5\n");
        fprintf(fp, "#psf size\n");
        fprintf(fp, "psfSize\t%.1f\t\t\t\t", psfSize);
        fprintf(fp, "#\n");
        fprintf(fp, "\n");

        fprintf(fp, "#6\n");
        fprintf(fp, "#Do you want to generate an subsampled PSF? (Y/N) : \n");
        fprintf(fp, "#if select y, Enter an INTEGER subsampling factor (2-10) : for example 4\n");
        fprintf(fp, "#if select n, skip this process\n");
        fprintf(fp, "subsampledPSF\t%c\n", subsampledPSF);
        fprintf(fp, "subsampleFactor\t%d\t\t", subsampleFactor);
        fprintf(fp, "#2 ~ 10\n");

        fprintf(fp, "\n");
        fprintf(fp, "#7\n");
        fprintf(fp, "#Enter rootname of output image file(s) :\n");
        fprintf(fp, "rootName\t%s\t\t", rootname);
        fprintf(fp, "#fileName\n");
        fprintf(fp, "\n");

        fclose(fp);
    }else{
        flag = 0;
    }

    return flag;
}
