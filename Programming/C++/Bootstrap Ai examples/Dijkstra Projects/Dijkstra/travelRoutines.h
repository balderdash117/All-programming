#ifndef _TRAVEL_ROUTINES_H_
#define _TRAVEL_ROUTINES_H_

#include <list>
#include <string>
#include <vector>
#include <queue>

#include "Texture.h"
#include "Font.h"
#include "Input.h"

class City;
class SkyrimMap;
class DijkstraApp;
class Path
{
public:
	Path();
	Path(City* start, City * dest, int newCost);
	~Path();
	City* getSource() const { return source; };
	City* getDest() const { return destination; };
	int getCost() const { return cost; };

private:
	int cost;
	City* source;
	City* destination;
};

struct Point
{
	Point() = default;
	Point(int p_x, int p_y) : x(p_x), y(p_y) {}
	int x, y;
};

class City
{
public:
	City();
	City(std::string, Point pos, Point map);
	~City();
	std::string getName() const { return name; };
	void addPath(Path newPath);
	bool isVisited() { return visited; };
	void setVisited(bool v);
	bool isQueued() { return queued; };
	void setQueued(bool q);
	const std::list<Path> & getPaths() { return paths; };
	Point getPosition() { return position; };
	Point getPositionOnMap() { return positionOnMap; };
	
	// stuff for pathing algorithms
	double costFromStart;
	double heuristic;
	City* from;

private:
	std::string name;
	std::list<Path> paths;
	Point position;
	Point positionOnMap;
	bool visited;
	bool queued;
};

class SkyrimMap
{
public:
	SkyrimMap();
	~SkyrimMap();

	void addCityTop(std::string name, Point pos, Point map);
	void addCity(std::string name, Point pos, Point map);
	void addPath(std::string source, std::string destination, int cost);
	City * findCity(std::string);
	City * findScreenCity(Point a_map);
	std::vector<City*>* reachable(std::string name);
	std::vector<City*>* shortestPath(std::string nameStart, std::string nameFinish); // Dijkstra's
	std::vector<City*>* reachableCities;

private:
	std::list<City> cities;

	std::vector<City*>* makeCityPath(std::string nameStart, std::string nameFinish);
};


#endif // _TRAVEL_ROUTINES_H_