// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
// atoi()
#include <stdlib.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	
	// Slownik mesko-zenski Slowian.
	create_slav_sex_map(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	srand(time(NULL));
	for(int i=0; i<n; i++)
		if(rand()%2) vectorOfSlavs.push_back(&slavs[i]);
		else vectorOfSlavs.insert(vectorOfSlavs.begin(), &slavs[i]);
	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	for(vector<Slav*>::iterator i=vectorOfSlavs.begin(); i!=vectorOfSlavs.end(); i++)
		cout << (*i)->description() << endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(vector<Slav*>::iterator i=vectorOfSlavs.begin(); i!=vectorOfSlavs.end(); i++)
		setOfSlavs.insert(*i);
	vectorOfSlavs.clear(); // Czyszczenie wektora.
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	for(set<Slav*>::iterator i=setOfSlavs.begin(); i!=setOfSlavs.end(); i++)
		mapOfSlavs[*i]=*(++i);
	setOfSlavs.clear();
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	for(map<Slav*, Slav*>::iterator i=mapOfSlavs.begin(); i!=mapOfSlavs.end(); i++)
		cout << i->first->description() << "\t" << i->second->description() << endl;
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i=0; i<n; i++)
		queueOfSlavs.push(&slavs[i]);
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	for(int i=0; i<n; i++)
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	for(int i=0; i<n; i++)
	{
		cout << stackOfSlavs.top()->description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

// Slownik mesko-zenski Slowian.
void create_slav_sex_map(Slav* slavs, int n)
{
	map <vector<Slav*>, vector<Slav*>> slav_sex_map;
	vector<Slav*> slav_males, slav_females;
	for(int i=0; i<n; i++)
	{
		if(slavs[i].sex()==Slav::male)
			slav_males.push_back(&slavs[i]);
		else
			slav_females.push_back(&slavs[i]);
	}
	slav_sex_map[slav_males]=slav_females;
	// Sprawdzenie poprawnosci dzialania.
	//printf("[slav_males = %lu, slav_females = %lu, slav_sex_map = %lu, existingSlavs = %i]\n", slav_males.size(), slav_females.size(), slav_sex_map.size(), Slav::counter());
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
