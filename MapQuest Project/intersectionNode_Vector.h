/*	
 *	Object to hold a vector of all intersectionNodes, each containing a location and all roads connecting to that location.
 *	Also contains starting and end city nodes inputted from user.
 */

#ifndef __INTERSECTIONNODE_VECTOR_H
#define __INTERSECTIONNODE_VECTOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include "intersectionNode.h"

class intersectionNode_Vector 
{
  protected:
	vector<intersectionNode *> V;
	intersectionNode * startNode;
	intersectionNode * endNode;
	
	void read_locations_file();
	void read_major_roads_file();

  public:
	intersectionNode_Vector();
	~intersectionNode_Vector();
	void print_location(int locationIndex);
};

#endif