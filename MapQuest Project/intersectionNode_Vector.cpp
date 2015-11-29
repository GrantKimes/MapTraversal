#include "intersectionNode_Vector.h"

intersectionNode_Vector::intersectionNode_Vector()
{
	cout << "Initializing intersectionNode_Vector" << endl;
	read_locations_file();							// Reads locations.txt and fills vector with all locations at corresponding indexes.
	read_major_roads_file();						// Reads majorroads.txt and adds to each intersectionNode the roads that each location is connected to.
}

intersectionNode_Vector::~intersectionNode_Vector()
{
	// Iterate through vector and delete each allocated node.
	delete startNode;
	delete endNode;
}

void intersectionNode_Vector::read_locations_file()
{
	ifstream fin("locations.txt");
	if (fin.fail())
		cerr << "Failed to read locations.txt" << endl;

	string line;
	for (int i = 0; true; i++)
	{
		getline(fin, line);
		if (fin.fail())
			break;

		location * L = new location(line);			// Make new location from line of locations.txt.
		V.push_back(new intersectionNode(L, i));	// Make new intersectionNode with that location, and add it to the vector.
	}
}

void intersectionNode_Vector::read_major_roads_file()
{
	ifstream fin("majorroads.txt");
	if (fin.fail())
		cerr << "Failed to read majorroads.txt" << endl;

	string line;
	
	while (true)
	{
		getline(fin, line);
		if (fin.fail())
			break;

		majorRoad * M = new majorRoad(line);		// Make majorRoad object from input line.
		int locIndex1 = M->get_locationIndex1();	// Get indexes in intersectionNode vector that this road connects.
		int locIndex2 = M->get_locationIndex2();

		V[locIndex1]->add_road(M);					// Add this road to each connected intersectionNode's list of roads. 
		V[locIndex2]->add_road(M);
	}
}

void intersectionNode_Vector::print_location(int locationIndex)
{
	V[locationIndex]->print();
}