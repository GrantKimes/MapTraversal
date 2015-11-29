/*		Object for values in file locations.txt.
 *		Each contains longitude and latitude of a city. majorRoads connects two values in locations.txt by index.
 *		
 */

#ifndef __LOCATION_H
#define __LOCATION_H

#include <string>
#include <sstream>
#include <iostream>
#include "intersectionNode.h"

using namespace std;

class location
{
	friend class intersectionNode;

  protected:
	double longitude, latitude, milesToNearestPlace;
	int population;
	string type, state, name;

  public:
	location(double lon, double lat, double mi, int po, string ty, string st, string na);
	location(string line);
	location() {}
	~location() {}

	location * parse_line(string line);
	string get_name() {	return name; }
	void print();
};

#endif