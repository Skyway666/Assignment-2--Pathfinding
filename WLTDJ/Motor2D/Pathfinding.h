#pragma once
#include "j1Module.h"
#include "p2DynArray.h"
#include "p2Point.h"
#include "p2List.h"

//This class will be used by any entity in order to get a path to a certain destination. It will have a public attribute called "last_path" 
//and a public method called "create path", that when used will fill last path with a set of tiles, that will represent the path. It will be a part of App
class Pathfinding: public j1Module
{
public:
	//Constructor/Destructor
	Pathfinding();
	~Pathfinding();
private:
	//Private methods

	//Private attributes
	uint height, width;
	uint* walkability_values;
	p2DynArray<iPoint> last_path;

	//p2PQueue<iPoint>	frontier;
	p2List<iPoint>		visited;
	p2List<iPoint>		breadcrumbs;
public:
	//Public methods
	void SetMap(uint wiudth_, uint height_, uint* walkability_values_);
	void CreatePath(); //This will fill "last path"
	bool CleanUp();
	bool IsWalkable();
	p2DynArray<iPoint> GetLastPath();
	//Public attributes
	
};

