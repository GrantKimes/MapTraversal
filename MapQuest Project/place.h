/*	Place class.
 *	Object to hold data read in from named-places.txt
 */

#ifndef __PLACE_H
#define __PLACE_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


class place
{
  protected:

	int numericCode;
	string state;
	string name;
	int population;
	double area;
	double latitude;
	double longitude;
	int locationsIndex;
	double distanceToLocation;
	int namedPlacesIndex;
 
  public:

	place();
	place(int nu, string s, string na, int p, double a, double lat, double lon, int li, double dtl, int npi);
	place(string line, int currIndex);
	string get_name();
	string get_state();
	double get_lat();
	double get_long();
	int get_locationsIndex();
	void print();
};

#endif