#include "place.h"

place::place()	{}

place::place(int nu, string s, string na, int p, double a, double lat, double lon, int li, double dtl, int npi):
    numericCode(nu), state(s), name(na), population(p), area(a), latitude(lat),
    longitude(lon), locationsIndex(li), distanceToLocation(dtl), namedPlacesIndex(npi)
{     }
	
string place::get_name()
{	return name;	}

string place::get_state()
{	return state;	}

double place::get_lat()
{	return latitude;	}

double place::get_long()
{	return longitude;	}

int place::get_locationsIndex()
{	return locationsIndex;	}

void place::print()
{
	cout << name << ", " << state << ": locationsIndex=" << locationsIndex << ", namedPlacesIndex=" << namedPlacesIndex << endl;
}

place::place(string line, int currIndex)
{
	stringstream ss(line);

	char temp[64];			// Read into the same buffer for each, null terminating after each read. 

	ss.read(temp, 8);		// Buffer for numericCode. Columns 1-8.
	numericCode = atoi(temp);
	
	ss.read(temp, 2);		// Buffer for state. Columns 9-10.
	temp[2] = 0;
	state = temp;

	ss.read(temp, 49);		// Buffer for place name. Columns 11-59.
	temp[49] = 0;
	stringstream nameStream(temp);	// String stream to read in multiple-word city names.
	nameStream >> name;
	string S;
	while (nameStream >> S)
		name += " " + S;

	ss.read(temp, 7);		// Buffer for population. Columns 60-66.
	temp[7] = 0;
	population = atoi(temp);

	ss.read(temp, 14);		// Buffer for area. Columns 67-80.
	temp[14] = 0;
	area = atof(temp);

	ss.read(temp, 10);		// Buffer for latitude. Columns 81-90.
	temp[10] = 0;
	latitude = atof(temp);

	ss.read(temp, 11);		// Buffer for longitude. Columns 91-101.
	temp[11] = 0;
	longitude = atof(temp);
	
	ss.read(temp, 5);		// Buffer for locationsIndex. Columns 102-106.
	temp[5] = 0;
	locationsIndex = atoi(temp);

	ss.read(temp, 8);		// Buffer for distance. Columns 107-114.
	temp[8] = 0;
	distanceToLocation = atof(temp);

	namedPlacesIndex = currIndex;
}

