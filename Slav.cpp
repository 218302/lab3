#include "Slav.h"
#include <fstream>

// czas i rand()
#include <time.h>
#include <stdlib.h>
// istream_iterator
#include <iterator>

using namespace std;

vector <string> Slav::names;
int Slav::_counter = 0;

void Slav::init()
{
	srand(time(NULL));
	ifstream file("names.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();
}

Slav::Slav()
{
	static int amountOfNames = (init(), names.size());
/*
inicjalizacja zmiennej statycznej w konstruktorze klasy - wykonanie funkcji init(),
a pozniej przypisanie zmiennej wartosci names.size() (leniwa inicjalizacja)
*/
	_name = names[rand() % amountOfNames];
	_id = _counter++;
}

string Slav::description()
{
	return string("  ") + _name + " [" + to_string(_id) + "]";
}

Slav::sex_enum Slav::sex()
{
	if(_name[_name.size()-1]=='a')
		return female;
	else
		return male;
}
