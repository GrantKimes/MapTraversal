#include "MapTraversal.h"

void MapTraversal::traverse_graph()
{
	// Find two cities. Calculate path between them.

	cout << "Starting city: ";
	int locIndex1 = get_locationsIndex();
	startNode = V[locIndex1];

	cout << "Destination city: ";
	int locIndex2 = get_locationsIndex();
	endNode = V[locIndex2];

	cout << "Calculating path from " << startNode->get_name() << ", " << startNode->get_state();
	cout << " to " << endNode->get_name() << ", " << endNode->get_state() << " ..." << endl << endl;

	find_node_path();		// Search through nodes and give distance information. 

	trace_back_path();		// Fills member pathBack. Doesn't get altered later when called as a parameter.
	print_pathBack(pathBack);

	draw_tile();			// Draw map tile, pathBack, and cities.
	draw_pathBack(pathBack);
	draw_city_points();
}

void MapTraversal::find_node_path()
{
	// Go through graph from starting node, adding neighbors to queue and updating distanceFromStart.

	startNode->set_distanceFromStart(0);
	startNode->set_degreesToEndNode(endNode);		// DegreesToEndNode is the ordering for priority queue.
	nodesToVisit.push(startNode);

	while (! nodesToVisit.empty())
	{
		intersectionNode * curr = nodesToVisit.top();		
		nodesToVisit.pop();

		visit(curr);
		if (curr == endNode)						// Find a way to not stop searching when end is found. This leads to choosing the first match, not most effective.
			break;
	}
}

void MapTraversal::visit(intersectionNode * curr)
{
	// Given a current node, add all it's neighboring nodes to the queue. 
	// Update the added nodes' distanceFromStart. 

	if (curr->is_visited())		// This node's neighbors have already been added to queue.
		return;

	vector<intersectionNode *> neighbors = curr->get_neighbor_nodes(V);
	for (int i = 0; i < neighbors.size(); i++)
	{
		neighbors[i]->set_degreesToEndNode(endNode);	// Priority queue nodesToVisit requires comparison to endNode degree distance.
		nodesToVisit.push(neighbors[i]);
	}

	curr->now_visited();
}

void MapTraversal::trace_back_path()
{
	// From end node, look for neighboring nodes that are part of the shortest path. Return the roads in order. 

	intersectionNode * currNode = endNode;
	majorRoad * road = NULL;
	while (true)
	{
		if (currNode == startNode)		// Found the starting point.
			break;

		currNode = currNode->find_road_back(V, road);
		pathBack.push(road);
	}
}

void MapTraversal::print_pathBack(stack<majorRoad *> pathBack)
{
	// Print list of directions of roads to get to destination. 

	majorRoad * currRoad;
	string currRoadName;
	double currLengthMiles;
	int currLocationIndex;

	while (! pathBack.empty())
	{
		currRoad = pathBack.top();
		pathBack.pop();

		currRoadName = currRoad->get_name();
		currLengthMiles = currRoad->get_lengthMiles();
		currLocationIndex = currRoad->get_finalPathLocationIndex();

		// While next road name matches, add to current road distance so it doesn't print same road multiple times.
		while (! pathBack.empty() && currRoadName == pathBack.top()->get_name())
		{
			currRoad = pathBack.top();
			pathBack.pop();
			currLengthMiles += currRoad->get_lengthMiles();
			currLocationIndex = currRoad->get_finalPathLocationIndex();
		}

		cout << "Take " << currRoadName << " for " << setprecision(2) << currLengthMiles << " miles towards ";
		int i = currRoad->get_finalPathLocationIndex();
		cout << V[i]->get_name() << endl;
	}
}

void MapTraversal::draw_tile()
{
	// Given coordinates of cities, find fitting coverage tile and draw it.

	double longA = startNode->get_longitude();
	double latA = startNode->get_latitude();
	double longB = endNode->get_longitude();
	double latB = endNode->get_latitude();

	make_coverageFile(latA, longA, latB, longB);
	draw_map_tile();
}

void MapTraversal::draw_city_points()
{
	// Draw coordinates of inputted cities and write names.

	double startNodeX = get_pixelX_of_longitude(longA);
	double startNodeY = get_pixelY_of_latitude(latA);
	double endNodeX = get_pixelX_of_longitude(longB);
	double endNodeY = get_pixelY_of_latitude(latB);

	// Draw points at startNode and endNode on map.
	set_pen_color(color::black);
	set_pen_width(10);
	draw_point(startNodeX, startNodeY);
	draw_point(endNodeX, endNodeY);
	set_pen_color(color::red);
	set_pen_width(6);
	draw_point(startNodeX, startNodeY);
	draw_point(endNodeX, endNodeY);

	// Write city names under points.
	set_font("Arial");					
	set_pen_color(color::white);
	set_font_size(20);
	set_font_style(style::bold);
	move_to(startNodeX, startNodeY + 15);
	string startNodeName = startNode->get_name();
	write_string(startNodeName, direction::center);
	move_to(endNodeX, endNodeY + 15);
	string endNodeName = endNode->get_name();
	write_string(endNodeName, direction::center);
}

void MapTraversal::draw_pathBack(stack<majorRoad *> pathBack)
{
	// Iterate through pathBack stack and draw each road.

	majorRoad * currRoad = NULL;

	set_pen_color(color::black);
	set_pen_width(3);

	while (! pathBack.empty())
	{
		currRoad = pathBack.top();
		pathBack.pop();

		double longA = V[currRoad->get_locationIndex1()]->get_longitude();
		double latA = V[currRoad->get_locationIndex1()]->get_latitude();
		double longB = V[currRoad->get_locationIndex2()]->get_longitude();
		double latB = V[currRoad->get_locationIndex2()]->get_latitude();

		double Ax = get_pixelX_of_longitude(longA);
		double Ay = get_pixelY_of_latitude(latA);
		double Bx = get_pixelX_of_longitude(longB);
		double By = get_pixelY_of_latitude(latB);

		move_to(Ax, Ay);
		draw_to(Bx, By);
	}
}