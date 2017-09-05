////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																									////
////																									////
////				Marc Chee(marcc@aie.edu.au), June 2016												////
////																									////
////				Showing some code for running Dijkstra's Shortest Path								////
////				and A* Search on a simple weighted node graph										////
////																									////
////																									////
////																									////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

//#include "Timer.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

#include "travelRoutines.h"


using std::cout;
using std::endl;



Path::Path()
{
}

Path::Path(City * start, City * dest, int newCost)
{
	source = start;
	destination = dest;
	cost = newCost;
}


Path::~Path()
{
}


City::City()
{
}

City::City(std::string newName, Point pos, Point map)
{
	name = newName;
	position = pos;
	positionOnMap = map;
	costFromStart = 0.0;
	heuristic = 0.0;
	from = nullptr;
}


City::~City()
{
}

void City::addPath(Path newPath)
{
	paths.push_back(newPath);
}

void City::setVisited(bool v)
{
	visited = v;
}

void City::setQueued(bool q)
{
	queued = q;
}


bool nearer(City * a, City * b)
{
	return a->costFromStart < b->costFromStart;
}

SkyrimMap::SkyrimMap()
{
}

SkyrimMap::~SkyrimMap()
{
}

void SkyrimMap::addCityTop(std::string name, Point pos, Point map)
{
	// modification for '0' being at the bottom, not the top
	pos.y = 767 - pos.y;
	map.y = 767 - map.y;
	City newCity(name, pos, map);

	cities.push_back(newCity);
}

void SkyrimMap::addCity(std::string name, Point pos, Point map)
{
	City newCity(name, pos, map);

	cities.push_back(newCity);
}

void SkyrimMap::addPath(std::string source, std::string destination, int cost)
{
	City * sourceCity = findCity(source);
	City * destCity = findCity(destination);
	Path newPath(sourceCity, destCity, cost);
	sourceCity->addPath(newPath);
}

City * SkyrimMap::findCity(std::string name)
{
	// loop through the cities and find the one that matches the name
	for (auto &city : cities)
	{
		if (city.getName() == name)
		{
			City * cityPtr = &city;
			return cityPtr;
		}
	}
	return nullptr; // we didn't find a city of that name
}

City * SkyrimMap::findScreenCity(Point a_map)
{
	int bestDist = 10000;
	City * cityPtr = nullptr;
	// loop through the cities and find the one that matches the location within 200 pixels
	for (auto &city : cities)
	{
		Point map = city.getPositionOnMap();
		int diffX = map.x - a_map.x;
		int diffY = map.y - a_map.y;
		int dist = (int) sqrt(diffX*diffX + diffY*diffY);

		if (dist > 200) continue;

		if (dist < bestDist) {
			bestDist = dist;
			cityPtr = &city;
		}
	}
	return cityPtr; // find the city
}

// Return a list of all the cities reachable from the current
std::vector<City*>* SkyrimMap::reachable(std::string name)
{
	for (auto &city : cities) // set all cities to not visited
	{
		city.setVisited(false);
		city.setQueued(false);
	}
	City* startingCity = findCity(name);
	std::queue<City*> bfsQueue;
	bfsQueue.push(startingCity);
	startingCity->setQueued(true);

	// loop through Breadth First Search
	while (!bfsQueue.empty())
	{
		City* current = bfsQueue.front(); // use then pop the front
		bfsQueue.pop();
		current->setVisited(true); // mark the front as visited
		for (auto &path : current->getPaths())
		{ // add all neighbours that haven't been queued to the queue
			if (!path.getDest()->isQueued())
			{
				bfsQueue.push(path.getDest());
			}
		}
	}
	// create the vector of City pointers that are reachable
	std::vector<City*>* reachableCities = new std::vector<City*>;
	for (auto city : cities)
	{
		if (city.isVisited())
		{
			reachableCities->push_back(&city);
		}
	}
	return reachableCities;
}

std::vector<City*>* SkyrimMap::shortestPath(std::string nameStart, std::string nameFinish)
{
	// returns shortest path between two cities

	for (City &c : cities)
	{
		c.setVisited(false);
		c.costFromStart = 10000;
		c.from = nullptr;
	}

	std::vector<City *> explored;
	std::list <City *> connectedQueue;

	explored.push_back(findCity(nameStart));
	findCity(nameStart)->setVisited(true);
	findCity(nameStart)->costFromStart = 0;
	cout << "Starting city " << nameStart << " and Finishing: " << nameFinish << endl;

	for (const Path &path : explored[0]->getPaths())
	{
		City *current = path.getDest();

		current->costFromStart = path.getCost();
		current->from = findCity(nameStart);

		if (!current->isVisited())
		{
			connectedQueue.push_back(current);
			current->setVisited(true);

			cout << "Adding " << current->getName() << " to connected." << endl;
		}
	}

	connectedQueue.sort(nearer);


	while (true)
	{
		if (connectedQueue.size() == 0)
		{
			cout << "No more connected cities .. Finished Search" << endl;

			std::vector<City *> *cityPath = makeCityPath(nameStart, nameFinish);
			return cityPath;
		}
		else
		{
			City* next = connectedQueue.front();

			connectedQueue.pop_front();
			cout << "City Selected is: " << next->getName() << " at: " << next->costFromStart << endl;

			explored.push_back(next);
			next->setVisited(true);

			if (next->getName() == nameFinish)
			{
				cout << "Found Final City" << endl;

				std::vector<City *> *cityPath = makeCityPath(nameStart, nameFinish);
				return cityPath;
			}
			
			for (Path path : next->getPaths())
			{
				City *connectedCity = path.getDest();
			
				if (!connectedCity->isVisited())
				{
					double pathCost = path.getCost() + path.getSource()->costFromStart;
					
					if (pathCost < connectedCity->costFromStart)
					{
						connectedCity->from = path.getSource();
						connectedQueue.push_back(connectedCity);
						cout << "Adding " << connectedCity->getName() << " to connnected." << endl;
						connectedCity->setVisited(true);
						connectedCity->costFromStart = pathCost;
					}
				}
			}
			connectedQueue.sort(nearer);
		}
	}
	return nullptr;
}

std::vector<City*>* SkyrimMap::makeCityPath(std::string nameStart, std::string nameFinish)
{
	std::vector<City*>* cityPath = new std::vector<City*>;
	
	City *finalPathBackwards = findCity(nameFinish);

	while (finalPathBackwards->from != nullptr)
	{
		cityPath->push_back(finalPathBackwards);
		finalPathBackwards = finalPathBackwards->from;
	}

	if (finalPathBackwards == findCity(nameStart))
	{
		cout << "Path successful" << endl;
		cityPath->push_back(findCity(nameStart));
		// now reverse it
		std::reverse(cityPath->begin(), cityPath->end());
		// and print it out
		for (auto cty : *cityPath)
		{
			cout << "Final Path: " << cty->getName() << endl;
		}
	}
	return cityPath;
}

// end of travelRoutines.cpp