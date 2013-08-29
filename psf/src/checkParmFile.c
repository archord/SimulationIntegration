#include <stdio.h>
#include <string.h>
#include "stinytim.h"



char *getLine1( FILE *file, char *line )
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

	/* Remove any comments at the end of the line by placing a \0  *
	 * after the last parameter value on the line.                 */

	n = strchr( line, '#' );
	if ( n != NULL )
	{
		--n;

		/* Work backwards to the last visible character */

		while ( !isgraph(*n) )
			*n-- = '\0';
	}

	return( line );

} /* getLine */

void strupcase(char *string)
{
	while(*string != '\0')
	{
		*string = (char)toupper(*string);
		++string;
	}
}

int parseParm(char *line, PARMCONFIGFILE * parm)
{
	int flag = 1;
	static char pName[MAX_STRING];
	static char pValue[MAX_STRING];
	memset(pName, 0, MAX_STRING);
	memset(pValue, 0, MAX_STRING);
	sscanf(line, "%s %s", pName, pValue);
	strupcase(pName);
	if(strcmp(pName, "CAMERATYPE") == 0)
	{
		sscanf(pValue, "%d", &parm->cameraType);
	}else if(strcmp(pName, "PARMFILEPREFIX") == 0)
	{
		sscanf(pValue, "%s", &parm->parmFilePrefix);
	}else if(strcmp(pName, "POSITIONFILE") == 0)
	{
		sscanf(pValue, "%s", &parm->positionFile);
	}else if(strcmp(pName, "X") == 0)
	{
		sscanf(pValue, "%d", &parm->x);
	}else if(strcmp(pName, "Y") == 0)
	{
		sscanf(pValue, "%d", &parm->y);
	}else if(strcmp(pName, "BANDPASSTYPE") == 0)
	{
		sscanf(pValue, "%d", &parm->bandpassType);
	}else if(strcmp(pName, "WAVELENGTH") == 0)
	{
		sscanf(pValue, "%f", &parm->waveLength);
	}else if(strcmp(pName, "CURVEFILE") == 0)
	{
		sscanf(pValue, "%s", &parm->curveFile);
	}else if(strcmp(pName, "OBJECTSPECTRUM") == 0)
	{
		sscanf(pValue, "%d", &parm->objectSpectrum);
	}else if(strcmp(pName, "TEMPERATURE") == 0)
	{
		sscanf(pValue, "%f", &parm->temperature);
	}else if(strcmp(pName, "ALPHA") == 0)
	{
		sscanf(pValue, "%f", &parm->alpha);
	}else if(strcmp(pName, "BETA") == 0)
	{
		sscanf(pValue, "%f", &parm->beta);
	}else if(strcmp(pName, "SPECTRUMFILE") == 0)
	{
		sscanf(pValue, "%s", &parm->spectrumFile);
	}else if(strcmp(pName, "PSFSIZE") == 0)
	{
		sscanf(pValue, "%f", &parm->psfSize);
	}else if(strcmp(pName, "SUBSAMPLEDPSF") == 0)
	{
		sscanf(pValue, "%c", &parm->subsampledPSF);
	}else if(strcmp(pName, "SUBSAMPLEFACTOR") == 0)
	{
		sscanf(pValue, "%d", &parm->subsampleFactor);
	}else if(strcmp(pName, "ROOTNAME") == 0)
	{
		sscanf(pValue, "%s", &parm->rootname);
	}else{
		flag = 0;
	}
	return flag;
}


void showParm(PARMCONFIGFILE * parm)
{
	printf("cameraType=%d\n", parm->cameraType);
	printf("parmFilePrefix=%s\n", parm->parmFilePrefix);
	printf("positionFile=%s\n", parm->positionFile);
	printf("x=%d\n", parm->x);
	printf("y=%d\n", parm->y);
	printf("bandpassType=%d\n", parm->bandpassType);
	printf("waveLength=%f\n", parm->waveLength);
	printf("curveFile=%s\n", parm->curveFile);
	printf("temperature=%f\n", parm->temperature);
	printf("alpha=%f\n", parm->alpha);
	printf("beta=%f\n", parm->beta);
	printf("spectrumFile=%s\n", parm->spectrumFile);
	printf("psfSize=%f\n", parm->psfSize);
	printf("subsampledPSF=%c\n", parm->subsampledPSF);
	printf("subsampleFactor=%d\n", parm->subsampleFactor);
	printf("rootname=%s\n", parm->rootname);

}


int checkParm1(PARMCONFIGFILE *parm, char *errorMessage)
{
	if(parm->cameraType < 1 || parm->cameraType > 5 ){
		sprintf(errorMessage, "ERROR: cameraType must chose from 1 to 5, but you chose  %s!", parm->cameraType);
		return 0;
	}else if(parm->cameraType == 5){
		if(strcmp(parm->parmFilePrefix, "null") == 0 || parm->parmFilePrefix[0] == 0)
		{
			sprintf(errorMessage, "ERROR: if cameraType == 5, the parmFilePrefix cant be null or empty!");
			return 0;
		}
	}

	if( (strcmp(parm->positionFile, "null") == 0 || parm->positionFile[0] == 0) 
				&& ( parm->x == 0 || parm->y == 0) ){
		sprintf(errorMessage, "ERROR: positionFile or X&Y at least one must be valid!");
		return 0;
	}else if( strcmp(parm->positionFile, "null") != 0 && parm->positionFile[0] != 0 ){
		FILE *fp = fopen(parm->positionFile, "r");
		if(fp == NULL){
			sprintf(errorMessage, "ERROR: Could not open file %s!", parm->positionFile);
			return 0;
		}
		fclose(fp);
	}

	if(parm->bandpassType < 1 || parm->bandpassType > 3 ){
		sprintf(errorMessage, "ERROR: bandpassType must chose from 1 to 3, but you chose  %s!", parm->bandpassType);
		return 0;
	}else if( parm->bandpassType == 2 && parm->waveLength == 0){
		sprintf(errorMessage, "ERROR: if bandpassType=2, must specify waveLength!");
		return 0;
	}else if( parm->bandpassType == 3 && 
		(strcmp(parm->curveFile, "null") == 0 || parm->curveFile[0] == 0)){
		sprintf(errorMessage, "ERROR: if bandpassType=3, must specify curveFile!");
		return 0;
	}

	if(parm->bandpassType == 1 || parm->bandpassType == 3 ){
		if(parm->objectSpectrum < 1 || parm->objectSpectrum > 5 ){
			sprintf(errorMessage, "ERROR: objectSpectrum must chose from 1 to 4, but you chose  %s!", parm->objectSpectrum);
			return 0;
		}
	}

	if((parm->subsampledPSF == 'y' || parm->subsampledPSF == 'Y' )
		&& ( parm->subsampleFactor < 2 ||  parm->subsampleFactor > 10)){
		sprintf(errorMessage, "ERROR: if subsampledPSF=y, subsampleFactor must be a INTEGER from (2 - 10)!");
		return 0;
	}

	if(strcmp(parm->rootname, "null") == 0 || parm->rootname[0] == 0)
	{
		sprintf(errorMessage, "ERROR: must specify rootName!");
		return 0;
	}
		
	return 1;
}

/*return 0: the input parameter is invalid
             1: the input parameter is valid*/
             
int checkParm2(paramstruct *paraminfo, PARMCONFIGFILE *parm, char *errorMessage)
{
	float	x, y;
	int	xc, yc;
	x = parm->x;
	y = parm->y;
	xc = paraminfo->x_pixels/2;
	yc = paraminfo->y_pixels/2;

	if(strcmp(parm->positionFile, "null") == 0 || parm->positionFile[0] == 0) 
	{
		if( x < 0 || x >= paraminfo->x_pixels || y < 0 || y >= paraminfo->y_pixels){
			sprintf(errorMessage, "ERROR: X range is 0-%d, Y range is 0-%d pixels.", 
				paraminfo->x_pixels-1, paraminfo->y_pixels-1 );
			return 0;
		}else{
			paraminfo->num_positions = 1;
			paraminfo->x[0] = parm->x;
			paraminfo->y[0] = parm->y;
		}
	}else{
		Read_position_file( paraminfo, parm->positionFile, parm, errorMessage);
	}

	if(parm->bandpassType == 2){
        if(parm->waveLength < paraminfo->min_wavelength || parm->waveLength > paraminfo->max_wavelength){
		    sprintf(errorMessage, "ERROR: wavelength range is microns (%.1f-%.1f) : ",
		       paraminfo->min_wavelength, paraminfo->max_wavelength );
		    return 0;
	    }else{
		    paraminfo->wavelength[0]  = parm->waveLength;
		    paraminfo->num_waves = 1;
		    strcpy( paraminfo->spectrum_file, "(none)" );
	    }
    }else if(parm->bandpassType == 3){
        strcpy(paraminfo->bandpass_file, parm->curveFile);
    }
/*
	if ( paraminfo->num_waves > 1 )
	{
	 	if( parm->objectSpectrum == 1 && 
			(parm->temperature > 900000.0  || parm->temperature < 1.0)){
			sprintf(errorMessage, "ERROR: if objectSpectrum=1, temperature must be 1 - 900000 K!");
			return 0;
		}else if( parm->objectSpectrum == 2 && 
			parm->alpha > -0.000001 && parm->alpha < 0.000001){
			sprintf(errorMessage, "ERROR: if objectSpectrum=2, must specify alpha!");
			return 0;
		}else if( parm->objectSpectrum == 3 &&
			parm->beta > -0.000001 && parm->beta < 0.000001){
			sprintf(errorMessage, "ERROR: if objectSpectrum=3, must specify beta!");
			return 0;
		}else if( parm->objectSpectrum == 4 && 
			(strcmp(parm->spectrumFile, "null") == 0 || parm->spectrumFile[0] == 0)){
			sprintf(errorMessage, "ERROR: if objectSpectrum=4, must specify spectrumFile!");
			return 0;
		}
	}

	
	float	diam, max_size, min_size, c_wavelength;

	if ( paraminfo->num_waves == 1 )
		c_wavelength = paraminfo->wavelength[0];
	else
		c_wavelength = (paraminfo->wavelength[0] + paraminfo->wavelength[paraminfo->num_waves-1]) / 2;
 
	max_size = floor(Max_psf_diameter(paraminfo)*10.0) / 10.0;

	diam = parm->psfSize;
	min_size = (0.2 / 3.15) * paraminfo->wavelength[0];  //arcmin 

	if ( max_size <= 125.0 )
	{
		if ( diam < 3*paraminfo->det_pixel_size_arcsec_x || diam > max_size )
		{
			sprintf(errorMessage,  "Maximum computable PSF diameter = %.1f arcseconds\n "
				"Minimum recommended PSF diameter = %.2f arcseconds\n"
				 "Nominal pixel size = %.2f x %.2f arcseconds\n"
			, max_size, min_size*60.0
			, paraminfo->det_pixel_size_arcsec_x, paraminfo->det_pixel_size_arcsec_y  );
			return 0;
		}
	}
	else
	{
		if ( diam < 3*paraminfo->det_pixel_size_arcsec_x || diam > max_size )
		{
			sprintf( errorMessage, "Maximum computable PSF diameter = %.3f arcminutes\n"
				"Minimum recommended PSF diameter = %.2f arcminutes\n"
				 "Nominal pixel size = %.4f x %.4f arcminutes\n"
				, max_size/60.0 , min_size
				, paraminfo->det_pixel_size_arcsec_x/60.0, paraminfo->det_pixel_size_arcsec_y/60.0);
			return 0;
		}
	}
*/
	return 1;
}


int getParmFromConfFile(paramstruct *paraminfo, PARMCONFIGFILE *parm, char *errorMessage)
{
	int flag = 1;
	char line[MAX_STRING];
	char fileName[MAX_STRING];

	Default_dir(fileName);

	if(paraminfo->parmConfiglfile[0] == 0)
	{
		strcat( fileName, "stiny_default.conf" );
	}else{
		strcpy(fileName, paraminfo->parmConfiglfile);
	}

	FILE *fp = fopen(fileName, "r");
	if(fp != NULL)
	{
		getLine1(fp, line);
		while(line[0] != '\0')
		{
			int flag = parseParm(line, parm);
			if(flag == 0){
				sprintf(errorMessage, "unrecognised parameter \"%s\", please check config file!\n", line);
				flag = 0;
				break;
			}
			getLine1(fp, line);
		}
		fclose(fp);
	}else{
		sprintf(errorMessage, "Cant open file \"%s\"!\n", fileName);
		flag = 0;
	}

	return flag;
}


