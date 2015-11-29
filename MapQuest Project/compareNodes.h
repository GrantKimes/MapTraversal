/*	Object for comparison in priority queue.
 *	TODO: Develop better priority than closeness to destination latitude and longitude.
 */

#ifndef __COMPARENODES_H
#define __COMPARENODES_H

#include "intersectionNode.h"

struct compareNodes
{
	bool operator()(intersectionNode * A, intersectionNode * B);
};

#endif