/*  MapTraversal Project from ECE 318: Algorithms in C++
 *	Grant Kimes
 *	
 *	Reads in data from geographical data files. Information on files can be found here: rabbit.eng.miami.edu/geographical/
 *	After user inputs two cities, it finds the shortest path between the cities using BFS and a priority queue.
 *	The correct map tile is then drawn, and the road path between cities is drawn. Driving directions are printed. 
 */	

#include "library.h"
#include "MapTraversal.h"

void main()
{
	MapTraversal * X = new MapTraversal();
	X -> traverse_graph();
}