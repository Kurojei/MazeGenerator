#pragma once
#include <vector>

struct cell 
{
	int x;
	int y;
	bool visited = false;
};

class MazeGenerator 
{
public:
	void ShowMenu();
	void SanitizeInputs();
	void InitialiseGrid();
	void CarveMaze();
	void PrintMaze();
	void AddEntranceAndExit();
	cell& GetCellAt(int x, int y);
	std::vector<cell> GetNeighbours(cell& cell);
	void RemoveWall(cell& chosenCell, cell& stackBack);
	
public:
	int mazeWidth;
	int mazeHeight;
	std::vector<cell> stack;
	std::vector<cell> cells;
	std::vector<cell> neighbours;
};