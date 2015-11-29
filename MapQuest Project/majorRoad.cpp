#include "majorRoad.h"

majorRoad::majorRoad(string n, string t, int L1, int L2, double ld)
	: name(n), type(t), locationIndex1(L1), locationIndex2(L2), lengthDegrees(ld), finalPathLocationIndex(0)
{	
	lengthMiles = lengthDegrees * 69;	// Conversion from length given in longitude degrees to length in miles.
}

majorRoad::majorRoad(string line)
{
	stringstream ss;
	ss.str(line);
	ss >> name >> type >> locationIndex1 >> locationIndex2 >> lengthDegrees;
	lengthMiles = lengthDegrees * 69;
}

majorRoad * majorRoad::parse_line(string line)
{
	string na, ty;
	int L1, L2;
	double ld;

	stringstream ss;
	ss.str(line);
	ss >> na >> ty >> L1 >> L2 >> ld;
	return new majorRoad(na, ty, L1, L2, ld);
}

void majorRoad::print()
{
	cout << "Major road: " << name << ", connecting locations_Vector[" << locationIndex1 << "] and locations_Vector[" << locationIndex2 << "]. " << lengthMiles << " miles. " << endl;
}

string majorRoad::get_name()
{	return name;	}

int majorRoad::get_locationIndex1()
{	return locationIndex1;	}

int majorRoad::get_locationIndex2()
{	return locationIndex2;	}

double majorRoad::get_lengthMiles()
{	return lengthMiles;		}

int majorRoad::get_finalPathLocationIndex()
{	return finalPathLocationIndex;	}
