/*	MapTraversal object containing: intersectionNode_Vector, namedPlaces_HashTable, and coverageFile.
 *	TODO: More effective priority queue comparison function. 
 */

#ifndef __MAPTRAVERSAL_H
#define __MAPTRAVERSAL_H

#include <queue>
#include <stack>
#include <iomanip>
#include "intersectionNode_Vector.h"
#include "namedPlaces_HashTable.h"
#include "coverageFile.h"
#include "compareNodes.h"

class MapTraversal:		public intersectionNode_Vector, 
						public namedPlaces_HashTable, 
						public coverageFile
{
  protected:
	priority_queue<intersectionNode *, vector<intersectionNode *>, compareNodes> nodesToVisit;
	stack<majorRoad *> pathBack;
	
	void find_node_path();
	void visit(intersectionNode * curr);
	void trace_back_path();
	void print_pathBack(stack<majorRoad *> pathBack);
	void draw_city_points();
	void draw_pathBack(stack<majorRoad *> pathBack);
	void draw_tile();

  public:
	MapTraversal() {};
	void traverse_graph();
};

#endif