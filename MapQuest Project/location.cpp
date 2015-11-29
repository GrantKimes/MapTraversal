#include "location.h"


location::location(double lon, double lat, double mi, int po, string ty, string st, string na)
	: longitude(lon), latitude(lat), milesToNearestPlace(mi), population(po), type(ty), state(st), name(na)
{	}

location::location(string line)
{
	name = "";
	stringstream ss;
	ss.str(line);
	ss >> longitude >> latitude >> milesToNearestPlace >> population >> type >> state;
	string temp;
	while (ss >> temp)
	{
		if (name != "")
			name += " ";
		name += temp;
	}
}

location * location::parse_line(string line)
{
	double lon, lat, mi;
	int po;
	string ty, st, na = "";

	stringstream ss;
	ss.str(line);
	ss >> lon >> lat >> mi >> po >> ty >> st;
	string temp;
	while (ss >> temp)
	{
		if (na != "")
			na += " ";
		na += temp;
	}

	return new location(lon, lat, mi, po, ty, st, na);
}

void location::print()
{
	//cout << "Location: " << name << ", " << state << ", long=" << longitude << ", lat=" << latitude << endl;
	cout << name << ", " << state << " ";
}