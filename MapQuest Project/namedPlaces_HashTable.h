/*	Hash table class of place structs read from named-places.txt.
 *	Implemented as closed addressing using linked lists. 
 */

#ifndef __NAMEDPLACES_HASHTABLE_H
#define __NAMEDPLACES_HASHTABLE_H

#include <fstream>
#include <algorithm>
#include "place.h"
#include "List.hxx"

class namedPlaces_HashTable
{
  protected:
	List<place> * * table;
	int size;

	unsigned int hashFunc(string s);
	void add(place * p);
	void read_named_places_file();
	place * valid_namedPlace(string name);

  public:
	namedPlaces_HashTable(int tableSize = 50000);
	~namedPlaces_HashTable();
	void ask_input();
	int get_locationsIndex();
};

#endif