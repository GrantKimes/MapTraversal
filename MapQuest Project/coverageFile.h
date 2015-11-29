/*	Coverage file class. 
 *	This is used to read in data from coverage.txt and contains necessary components to draw a map tile:
 *	.dat filename, file metadata, user inputted latitudes and longitudes.
 *
 *	TODO: make better elevation coloring.
 */

#ifndef __COVERAGEFILE_H
#define __COVERAGEFILE_H

#include "library.h"

struct coverageFile		// Contains metadata about binary map coverage file. 
{
  protected:
	double latMin, latMax, longMin, longMax;
	string filename;
	int rows, columns, bytesPerPixel, secondsPerPixel, leftLongSeconds, topLatSeconds, minElevation, maxElevation, specialVal;
	double latA, longA, latB, longB;
	bool valid;

	void search_coverage();
	void get_file_metadata();
	bool in_range(double X, double Y, double min, double max);
	void make_coverageFile(double lat1, double long1, double lat2, double long2);
	double get_pixelX_of_longitude(double longitude);
	double get_pixelY_of_latitude(double latitude);

  public:

	coverageFile() {}
	coverageFile(double lat1, double long1, double lat2, double long2);
	void draw_map_tile();

};

#endif