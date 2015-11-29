#include "intersectionNode.h"

intersectionNode::intersectionNode(location * L, int i)
{
	currLocation = L;
	index = i;
	visited = 0;
	distanceFromStart = -1;
}

void intersectionNode::add_road(majorRoad * M)
{
	connectingRoads.push_back(M);
}

void intersectionNode::print()
{
	currLocation -> print();
	cout << "(" << index << "): Distance from start node: " << distanceFromStart;
}

void intersectionNode::now_visited()
{	visited = 1;	}

bool intersectionNode::is_visited()
{	return visited;	}

void intersectionNode::set_distanceFromStart(double D)
{	distanceFromStart = D;	}

double intersectionNode::get_distanceFromStart()
{	return distanceFromStart;	}

void intersectionNode::set_degreesToEndNode(intersectionNode * endNode)
{
	double longDiff = get_longitude() - endNode->get_longitude();
	double latDiff = get_latitude() - endNode->get_latitude();
	double result = sqrt( pow(longDiff, 2) + pow(latDiff, 2) );
	degreesToEndNode = result;
}

double intersectionNode::get_degreesToEndNode()
{	return degreesToEndNode;	}

string intersectionNode::get_name()
{	return currLocation->get_name();	}

string intersectionNode::get_state()
{	return currLocation->state;	}

double intersectionNode::get_longitude()
{	return currLocation->longitude;	}

double intersectionNode::get_latitude()
{	return currLocation->latitude;	}

vector<intersectionNode *> intersectionNode::get_neighbor_nodes(vector<intersectionNode *> intVec)
{
	vector <intersectionNode *> neighbors;
	for (unsigned int i = 0; i < connectingRoads.size(); i++)
	{
		// Iterate through connectingRoads and add neighbor locations to neighbors vector.
		intersectionNode * nextLocation;
		int index1 = connectingRoads[i]->get_locationIndex1();
		int index2 = connectingRoads[i]->get_locationIndex2();
		if (index == index1)
			nextLocation = intVec[index2];
		else if (index == index2)
			nextLocation = intVec[index1];

		// If new node's distance through currently visited node is shorter than existing distance, update to that distance.
		double currDistance = this->distanceFromStart + connectingRoads[i]->get_lengthMiles();
		if (currDistance < nextLocation->get_distanceFromStart() || nextLocation->is_visited() == false)
			nextLocation->set_distanceFromStart(currDistance);

		// If neighbor is not yet visited, add to vector.
		if (nextLocation->is_visited() == false)
			neighbors.push_back(nextLocation);
	}
	return neighbors;
}

bool compare_doubles(double A, double B)
{
	double X = abs(A - B);
	if (X < .0001)
		return true;
	else
		return false;
}

intersectionNode * intersectionNode::find_road_back(vector<intersectionNode *> intVec, majorRoad *& roadBack)
{
	// Iterate through connecting roads. For each connected location node, check if that is the correct path.

	intersectionNode * nextLocation;
	for (unsigned int i = 0; i < connectingRoads.size(); i++)
	{
		roadBack = connectingRoads[i];
		int index1 = roadBack->get_locationIndex1();
		int index2 = roadBack->get_locationIndex2();

		// Next location is whichever location connected by this road is not the current location.
		if (index == index1)
			nextLocation = intVec[index2];
		else if (index == index2)
			nextLocation = intVec[index1];

		// If the road to the next location node is the shortest path, take it.
		if (compare_doubles( nextLocation->get_distanceFromStart(), distanceFromStart - roadBack->get_lengthMiles() ))
		{
			roadBack->finalPathLocationIndex = nextLocation->index;		// roadBack is the road from curr->nextLocation.
			return nextLocation;
		}
	}
	cerr << "Error: Did not find road back. " << endl;
	return NULL;
}