/*		Object of each item in majorroads.txt
 *		Each object tells which two locations (given as indexes in locations file) are connected, and how long that road is. 
 *		Definitions included in header file because of simplicity.
 */

#ifndef __MAJORROAD_H
#define __MAJORROAD_H

//#include <iostream>
#include <string>
#include <sstream>
#include "intersectionNode.h"

using namespace std;

class majorRoad
{
	friend class intersectionNode;

  protected:
	string name, type;
	int locationIndex1, locationIndex2, finalPathLocationIndex;
	double lengthDegrees, lengthMiles;


  public:
	majorRoad(string n, string t, int L1, int L2, double lengthDegrees);
	majorRoad(string line);
	majorRoad()	{}
	~majorRoad() {}

	majorRoad * parse_line(string line);
	void print();
	string get_name();
	int get_locationIndex1();
	int get_locationIndex2();
	double get_lengthMiles();
	int get_finalPathLocationIndex();
};

#endif