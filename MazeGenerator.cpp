#include <iostream>
#include "MazeGenerator.h"

int main()
{
	MazeGenerator maze;
	maze.ShowMenu();
	printf("\n\n");
	system("Pause");

	return 0;
}

void MazeGenerator::ShowMenu()
{
	printf("Maze Generator!\n");
	printf(" 1. Generate New Maze\n 2. Load Maze\n 3. Exit\n");
	printf("\nChoose option: ");
	
	int option;
	std::cin >> option;
	if(option < 1 || option > 3)
	{
		system("cls");
		ShowMenu();
	}

	switch(option)
	{
	case 1:
		system("cls");
		SanitizeInputs();
		break;
	case 2:
		//TODO: Load maze from text file
		break;
	case 3:
		exit(0);
		break;
	}
}

void MazeGenerator::SanitizeInputs()
{
	auto isValidInput = [&](int number)
	{
		if(std::cin.fail() || number % 2 == 0 || number > 99 || number <= 1)
		{
			std::cin.clear();
			std::cin.ignore();
			system("cls");
			return false;
		}

		return true;
	};
	
	while(true)
	{
		printf("Inputs must be odd and between 3-99!\n\n");
		
		printf("Enter width: ");
		std::cin >> mazeWidth;
		if(!isValidInput(mazeWidth)) continue;
		
		printf("Enter height: ");
		std::cin >> mazeHeight;
		if(!isValidInput(mazeHeight)) continue;

		break;
	}

	InitialiseGrid();
	CarveMaze();
}

void MazeGenerator::InitialiseGrid()
{
	for(int y = 0; y < mazeHeight; y++)
	{
		for(int x = 0; x < mazeWidth; x++)
		{
			cell cell;
			cell.x = x;
			cell.y = y;
			cell.visited = false;
			cells.push_back(cell);
		}
	}
	AddEntranceAndExit();
}

void MazeGenerator::CarveMaze()
{
	cell& firstCell = GetCellAt(1, 1);
	firstCell.visited = true;
	stack.push_back(firstCell);

	while(!stack.empty())
	{
		auto neighbours = GetNeighbours(stack.back());
		if(!neighbours.empty())
		{
			int randCellIndex = rand() % neighbours.size();
			cell& chosenCell = GetCellAt(neighbours[randCellIndex].x, neighbours[randCellIndex].y);
			chosenCell.visited = true;
			RemoveWall(chosenCell, stack.back());
			stack.push_back(chosenCell);
		}
		else 
		{
			stack.pop_back();
		}
	}

	PrintMaze();
}

void MazeGenerator::AddEntranceAndExit()
{
	GetCellAt(1, 0).visited = true;
	GetCellAt(mazeWidth - 2, mazeHeight - 1).visited = true;
}

std::vector<cell> MazeGenerator::GetNeighbours(cell& cell)
{
	neighbours.clear();

	auto getOffset = [&](int i)
	{
		switch(i) 
		{
			case 0: return std::make_pair(0, -2); //North
			case 1: return std::make_pair(2, 0); //East
			case 2: return std::make_pair(0, 2); //South
			case 3: return std::make_pair(-2, 0); //West
		}
	};

	for(int i = 0; i < 4; i++)
	{
		std::pair<int, int> offset = getOffset(i);
		int NeighbourX = cell.x + offset.first;
		int NeighbourY = cell.y + offset.second;
		
		if(NeighbourX > 0 && NeighbourX < mazeWidth 
			&& NeighbourY > 0 && NeighbourY < mazeHeight 
			&& !GetCellAt(NeighbourX, NeighbourY).visited)
		{
			neighbours.push_back(GetCellAt(NeighbourX, NeighbourY));
		}
	}

	return neighbours;
}

void MazeGenerator::RemoveWall(cell& chosenCell, cell& stackBack)
{
	int wallX = (stackBack.x + chosenCell.x) / 2;
    int wallY = (stackBack.y + chosenCell.y) / 2;
    GetCellAt(wallX, wallY).visited = true;
}

cell& MazeGenerator::GetCellAt(int x, int y)
{
	return cells.at(y * mazeWidth + x);
}

void MazeGenerator::PrintMaze()
{
	system("cls");
	while(true)
	{
		for(int y = 0; y < mazeHeight; y++)
		{
			printf("\n");
			for(int x = 0; x < mazeWidth; x++)
			{
				cell cell = GetCellAt(x, y);
				printf(cell.visited ? " " : "#");
			}
		}
	

		printf("\n\nSave maze?...(y/n): ");
		char answer;
		std::cin >> answer;
		if(answer != 'y' && answer != 'n')
		{
			system("cls");
			continue;
		}
		else
		{
			//TODO: Save maze to text file or pass
		}
		break;
	}

	cells.clear();
	system("cls");
	ShowMenu();
}