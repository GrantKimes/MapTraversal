/*	
 *	Object to contain a location, as well as all the connecting roads to that location.
 *	Accessed at its index in intersectionNode_Vector. 
 *	Contains data about miles from start node, and proximity to end node. 
 */

#ifndef __INTERSECTIONNODE_H
#define __INTERSECTIONNODE_H

#include <vector>
#include <iostream>
#include "location.h"
#include "majorRoad.h"

using namespace std;

class location;
class majorRoad;

class intersectionNode
{
  protected:
	location * currLocation;
	vector<majorRoad *> connectingRoads;
	int index;
	bool visited;
	double distanceFromStart;
	double degreesToEndNode;

  public:
	intersectionNode(location * L, int i);
	void add_road(majorRoad * M);
	void now_visited();
	bool is_visited();
	void print();
	void set_distanceFromStart(double D);
	double get_distanceFromStart();
	void set_degreesToEndNode(intersectionNode * endNode);
	double get_degreesToEndNode();
	string get_name();
	string get_state();
	double get_longitude();
	double get_latitude();
	vector<intersectionNode *> get_neighbor_nodes(vector<intersectionNode *> intVec);
	intersectionNode * find_road_back(vector<intersectionNode *> intVec, majorRoad *& roadBack);
};

#endif