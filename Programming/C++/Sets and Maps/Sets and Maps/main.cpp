#include <iostream>
#include <vector>
#include <chrono>

using std::cout;
using std::endl;
using std::vector;
using namespace std::chrono;

#include <string>
#include <set>
#include <map>

#define SETS
class setClass {
public:
	setClass(int p_id, std::string p_message, float p_value) :
		m_id(p_id), m_message(p_message), m_value(p_value) {}

	std::string m_message;
	int m_id;
	float m_value;

	bool operator < (const setClass &rhs) const
	{
		return (m_message < rhs.m_message);
	}
};
// we need an << operator
std::ostream& operator << (std::ostream &os, const setClass &obj)
{
	os << "id = " << obj.m_id << " :: " << obj.m_message <<
		" score of " << obj.m_value << endl;
	return os;
}

auto main(int argc, char ** argv)-> int
{
#ifdef SETS
	std::set<std::string> words;
#else
	std::vector<std::string> words;
#endif

	// build the array
#ifdef SETS
	words.insert("Second");
	words.insert("Third");
	words.insert("First");
	words.insert("First");
#else
	words.push_back("Second");
	words.push_back("Third");
	words.push_back("First");
	words.push_back("First");
#endif

	cout << "Set size = " << words.size() << endl;
	// auto = std::vector<std::string>:: iterator
	for (auto it = words.begin(); it != words.end(); ++it) {
		cout << *it << " :: ";
	}
	cout << endl;

	// we can erase using as usual ..
	// we can find
	auto it = words.find("Second");
	if (it != words.end()) {
		cout << *it << " found" << endl;
		//words.erase(it);
	} else {
		cout << "word not found" << endl;
	}

	// what about a class container
	std::set <setClass> idData;

	setClass d1(04, "John", 10.64f);
	setClass d2(03, "Fred", 0.55f);
	setClass d3(05, "Kelly", 11.55f);
	// and of course
	setClass d4(04, "Roger", 1001.64f);

	idData.insert(d1);
	idData.insert(d2);
	idData.insert(d3);
	idData.insert(d4);

	for (auto it = idData.begin(); it != idData.end(); ++it)
		cout << *it;

	cout << endl;

	// advancing
	std::set<int> setOfInts = { 25, 15, 35, 41, 42, 34, 
		50, 33, 25 };

	auto itMarks = setOfInts.begin();
	std::advance(itMarks, 3);
	cout << "advance is " << *itMarks << endl;
	std::advance(itMarks, 1);
	cout << "advance is " << *itMarks << endl;

	for (auto it = setOfInts.begin(); it != setOfInts.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	// maps ...........
	std::map<int, std::string> mapOfPlanets;

	mapOfPlanets.insert(std::make_pair(1, "Mercury"));
	mapOfPlanets.insert(std::make_pair(2, "Venus"));
	mapOfPlanets.insert(std::make_pair(3, "Earth"));
	mapOfPlanets.insert(std::make_pair(4, "Mars"));
	mapOfPlanets.insert(std::make_pair(5, "Jupiter"));
	mapOfPlanets.insert(std::make_pair(6, "Saturn"));
	mapOfPlanets.insert(std::make_pair(7, "Uranus"));
	mapOfPlanets.insert(std::make_pair(8, "Neptune"));
	mapOfPlanets.insert(std::make_pair(9, "Maybe Pluto"));

	for (auto it = mapOfPlanets.begin();
		it != mapOfPlanets.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

	// we want to do a little maore with maps
	cout << endl << endl;
	struct classComparator {
		bool operator() (const std::string & left,
			const std::string & right) const {
			return (left > right);
		}
	};
	std::map<std::string, int, classComparator> mapOfClass;

	mapOfClass.insert(std::make_pair("John", 1));
	mapOfClass.insert(std::make_pair("Martin", 2));
	mapOfClass.insert(std::make_pair("Russell", 3));
	mapOfClass.insert(std::make_pair("Roger", 4));
	mapOfClass.insert(std::make_pair("Nelson", 1));
	mapOfClass.insert(std::make_pair("Tim", 6));
	mapOfClass.insert(std::make_pair("Jack", 7));
	mapOfClass.insert(std::make_pair("David", 8));
	mapOfClass.insert(std::make_pair("Phillip", 1));

	// we try to add Jake ...
	auto result = mapOfClass.insert(std::make_pair("Jake", 10));
	for (auto it = mapOfClass.begin(); 
		it != mapOfClass.end(); ++it) {
		cout << it->first << " " << it->second << endl;
	}

	if (result.second == false) {
		cout << "failed to add ..." << 
			result.first->first << endl;
	} else {
		cout << "added key " << result.first->first << endl;
	}

	cout << endl;
	cout << mapOfClass["Roger"] << endl;

	// who has value '1'
	int value = 1;
	std::vector<std::string> vec;
	for (auto it = mapOfClass.begin();
		it != mapOfClass.end(); ++it) {
		if (it->second == value)
			vec.push_back(it->first);
	}
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		cout << *it << " has a value of " << value << endl;
	}
	cout << endl << endl;
	
	system("pause");
	return EXIT_SUCCESS;
}