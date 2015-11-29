#include "compareNodes.h"

bool compareNodes::operator()(intersectionNode * A, intersectionNode * B)
{
	// Return priority based on which node is closest to end node. 

	if (A->get_degreesToEndNode() < B->get_degreesToEndNode())
		return false;
	else if (A->get_degreesToEndNode() > B->get_degreesToEndNode())
		return true;

	return false;
}
