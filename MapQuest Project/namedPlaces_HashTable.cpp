#include "namedPlaces_HashTable.h"

namedPlaces_HashTable::namedPlaces_HashTable(int tableSize)
{
	cout << "Initializing namedPlaces_HashTable" << endl;
	size = tableSize;
	table = new List<place> * [size];
	for (int i = 0; i < size; i++)
		table[i] = new List<place>();
	read_named_places_file();
}

namedPlaces_HashTable::~namedPlaces_HashTable()
{
	delete table;
}

unsigned int namedPlaces_HashTable::hashFunc(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);	// Make string lowercase for equal hashing of all equivalent inputs.
	unsigned int h = 34567;
	int len = s.length();
	for (int i = 0; i < len; i++)
		h += h * 69 + s[i];
	if (h < 0)
		h *= -1;

	return h % size;
}


void namedPlaces_HashTable::add(place * p)
{
	// Add to hash table. Calculated index based off the name of place inputted.

	string name = p->get_name();
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	int index = hashFunc(name);
	table[index] -> insert(p);
}

void namedPlaces_HashTable::read_named_places_file()
{
	string line;
	ifstream fin_namedPlaces("named-places.txt");

	if (fin_namedPlaces.fail())
	{
		cerr << "Failed to read in file in read_named_places_file().\n";
		return;
	}

	for (int i = 0; true; i++)
	{
		getline(fin_namedPlaces, line);
		if (fin_namedPlaces.fail())
			break;
		add(new place(line, i));
	}

	fin_namedPlaces.close();
}

void namedPlaces_HashTable::ask_input()
{
	// Get input line instead of cin so that multiple words can be registered. 
	string s;
	while (true)
	{
		cout << "Input the name of a city to find:" << endl;
		cin >> s;

		transform(s.begin(), s.end(), s.begin(), ::tolower);
		int index = hashFunc(s);
		if (! table[index] -> print_list(s))
		{
			cout << "Could not find that city." << endl;
		}
		cout << "-----------------------------" << endl << endl;
	}
}

place * namedPlaces_HashTable::valid_namedPlace(string name)
{
	// Check if inputted name is a valid place. If not, return NULL. If yes, return it. If multiple matches, prompt to specify which state.

	int index = hashFunc(name);
	List<place> * cities;
	cities = table[index] -> return_name_matches(name);		// Get list of cities with a matching name in the hashtable.

	if (cities -> get_length() == 0)						// Name does not exist in namedPlaces hashtable, return nothing.
		return NULL;											
	if (cities -> get_length() == 1)						// One name matches, return that place.
		return cities -> get_first() -> get_data();

	cout << "Multiple matches, choose a state: ";
	while (cities -> get_length() > 1)						// Multiple matches, ask for which state.
	{
		Link<place> * P = cities -> get_first();			// List states.
		while (P != NULL)
		{
			cout << P -> get_data() -> get_state() << " ";
			P = P -> get_next();
		}
		cout << endl;
		string state;
		getline(cin, state);								// Get user input state, convert to lowercase.
		transform(state.begin(), state.end(), state.begin(), ::tolower);

		P = cities -> get_first();
		while (P != NULL)									// Search for matching state in city list.
		{
			string currState = P -> get_data() -> get_state();
			transform(currState.begin(), currState.end(), currState.begin(), ::tolower);
			if (state == currState)
				return P -> get_data();						// Return it if found.
			P = P -> get_next();
		}
		cout << "No matching states, choose from: ";		// If not found, loop again. 

	}
}
  
int namedPlaces_HashTable::get_locationsIndex()
{
	//cout << "Input a city name: " << endl;
	string N;
	getline(cin, N);
	place * P = valid_namedPlace(N);
	while (P == NULL)									// Until a valid city name is inputted, continue prompting the user. 
	{
		cout << "Invalid city name, try again: ";
		getline(cin, N);
		P = valid_namedPlace(N);
	}
	return P -> get_locationsIndex();					// P now contains the desired named place from the user's input. 
}