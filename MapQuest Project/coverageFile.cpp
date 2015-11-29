#include "coverageFile.h"

coverageFile::coverageFile(double lat1, double long1, double lat2, double long2)
{
	// Constructor for coverageFile. Sets values of inputted points, finds binary coverage file, gets metadata of that file.

	filename = "NO VALUES YET";
	latA = lat1;
	longA = long1;
	latB = lat2;
	longB = long2;

	search_coverage();					// Find best fitting elevation file.

	char temp[64] = "Elevation Files/";	// Add directory path.
	strcat(temp, filename.c_str());
	filename = temp;

	get_file_metadata();				// Read first line of metadata values.
}

void coverageFile::search_coverage()	
{
	// Given two points, find the best fitting map tile (coverageFile) from "coverage.txt". 
	// Sets this coverageFile values of: latMin, latMax, longMin, longMax, filename.

	ifstream fin("coverage.txt"); 
	double currLatMax, currLatMin, currLongMin, currLongMax;
	string currFilename;

	if (!in_range(latA, latB, 0, 50) || !in_range(longA, longB, -130, -50))
	{
		cerr << "Input values outside of data range, try again. " << endl;
		valid = false;
		return;
	}

	while(!fin.fail())
	{
		// Read in a line from "coverage.txt", this is the current file being investigated.
		fin >> currLatMax >> currLatMin >> currLongMin >> currLongMax >> currFilename;
		if (fin.fail())
			break;

		// Check if the inputted latitude and longitude values are within current file boundaries. If they are, current file is a fit.
		if (in_range(latA, latB, currLatMin, currLatMax) && in_range(longA, longB, currLongMin, currLongMax))	
		{ 
			// If smallest does not exist yet, current file is now the best fit.
			if (filename == "NO VALUES YET")
			{
				latMin = currLatMin;
				latMax = currLatMax;
				longMin = currLongMin;
				longMax = currLongMax;
				filename = currFilename;
			}
			// If current file is a better fit than previous fit (smaller map tile), that is now the best fit. 
			else if ((currLatMax - currLatMin) < (latMax - latMin) && (currLongMax - currLongMin) < (longMax - longMin))
			{ 
				latMin = currLatMin;
				latMax = currLatMax;
				longMin = currLongMin;
				longMax = currLongMax;
				filename = currFilename;
			}
		}
	}
	fin.close();
	valid = true;
}

void coverageFile::get_file_metadata()
{
	// Read in metadata from given binary coverage file. Example of filename being read: "usaW100N25D5.dat").
	// Sets this coverageFile values of: rows, columns, bytesPerPixel, secondsPerPixel, leftLongSeconds, topLatSeconds, minelevation, maxelevation, specialVal. 

	if (! valid)
		return;

	ifstream fin(filename, ios::in | ios::binary);
	if (fin.fail())
	{
		cerr << "Error reading elevation file in get_file_metadata(). " << endl;
		return;
	}

	for (int i = 0; i < 18; i++)	// Reading metadata at the beginning of the file. 18 pieces of data, alternating between strings and ints.
	{
		string s = "";
		while (true)				// Get each letter, one at a time. End of that string when a space is encountered. 
		{
			char letter[1];
			fin.read(letter, 1);
			if (fin.fail())
			{
				cout << "failed " << endl;
				break;
			}
			if (letter[0] == ' ')
				break;
			s += letter[0];
		}

		int length = s.length();
		int x = 0;
		if (i % 2 != 0)		// When the string in question is a numerical value to be read, convert to a double.
		{
			for (int j = 0; j < length; j++)	// Go through the string one character at a time.
			{
				if (s[length-j-1] == '-')		// If there is a negative sign at the front, negate the number.
					x *= -1;
				else
				{
					int a = s[length-j-1] - '0';	// Convert char from ascii to its corresponding int value.
					x += a * pow(10.0, j);			// Multiply the current int by its corresponding power of 10, and add to x.
				}
			}
		}

		// Every other time through the loop, a numerical metadata values is being read.
		if (i == 1)				 
			rows = x;
		if (i == 3)
			columns = x;
		if (i == 5)
			bytesPerPixel = x;
		if (i == 7)
			secondsPerPixel = x;
		if (i == 9)
			leftLongSeconds = x;
		if (i == 11)
			topLatSeconds = x;
		if (i == 13)
			minElevation = x;
		if (i == 15)
			maxElevation = x;
		if (i == 17)
			specialVal = x;
	}
	fin.close();
	
}

bool coverageFile::in_range(double X, double Y, double min, double max)	
{
	// Checks if X and Y are both in range of max and min.

	if (X >= min && X <= max && Y >= min && Y <= max)
		return true;
	else 
		return false;
}

void coverageFile::make_coverageFile(double lat1, double long1, double lat2, double long2)
{
	// Same as constructor for coverageFile. Sets values of inputted points, finds binary coverage file, gets metadata of that file.

	filename = "NO VALUES YET";
	latA = lat1;
	longA = long1;
	latB = lat2;
	longB = long2;

	search_coverage();					// Find best fitting elevation file.

	char temp[64] = "Elevation Files/";	// Add directory path.
	strcat(temp, filename.c_str());
	filename = temp;

	get_file_metadata();				// Read first line of metadata values.
}

void coverageFile::draw_map_tile()		
{
	// Reads binary file of elevation values and draws each pixel. Darker color for higher values.

	if (! valid)
		return;

	make_window(columns-1, rows-1);

	ifstream fin(filename, ios::in | ios::binary);
	if (fin.fail())
			cerr << "Error reading in file in draw_map_tile()." << endl;
	fin.seekg(columns * bytesPerPixel, ios::beg);		// Seek to the end of the first line of metadata values.

	double max = maxElevation;
	double min = minElevation;
	int water = specialVal;

	short int * oneRow = new short int[columns];
	double g;
	int x;

	for (int i = 0; i < rows; i++)
	{
		// Read in a row at a time from elevation file. 
		fin.read( (char *) oneRow, columns * bytesPerPixel);
		
		for (int j = 0; j < columns; j++)
		{
			// x is the elevation of the current point. Color according to height. 
			x = oneRow[j];
			g = .8 - (.7 * (x / max));		// g is the gradient of green to be drawn for elevation x.

			if (x >= 0)
				set_pen_color(0.0, g, 0.0);				// Color for land.
			else if (x == water)
				set_pen_color(0.0, 0.4, 0.8);			// Color for water.
			else if (x < 0 && x != water)
				set_pen_color(0.5*(x/min), g, 0.0);		// Color for land with elevation less than sea level.

			if (x == 176)								// Great lakes are not input as water values, so this elevation is drawn as blue. As a result, other land of this elevation will have blue pixels.
				set_pen_color(0.0, 0.4, 0.8);

			draw_point(j, i);
		}
		
	}
	delete [] oneRow;
	fin.close();
}

double coverageFile::get_pixelX_of_longitude(double longitude)
{
	return -(longMin - longitude) / (longMax - longMin) * columns;
}

double coverageFile::get_pixelY_of_latitude(double latitude)
{
	return (latMax - latitude) / (latMax - latMin) * rows;
}