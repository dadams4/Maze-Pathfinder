/* Daniel Adams
   CPSC 340
   Maze.cpp
   This file contains all of the code which performs the actual path finding.  runHermione() finds a path using a stack, while runRon()
   finds a path using a queue.
*/
#ifndef MAZECPP
#define MAZECPP

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <fstream>
#include "Maze.h"
#include "Cell.h"
using namespace std;

Maze::Maze()
{
	int entranceRow = 0;
	int entranceCol = 0;
}

bool Maze::readMaze(string filename)
{
	ifstream infile;
	
	infile.open(filename.c_str());
	if(!infile)
	{
		cout<<"No maze with that name exists in the current directory... Stopping program... "<<endl;
		return false;
	}
	int rows, cols;
	infile>>rows>>cols;
	setRows(rows);
	setCols(cols);

	if(rows > 10 || cols > 10)
	{
		cout<<"Maze is too big"<<endl;
		return false;
	}

	for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				char c;
				infile >> c;
				maze[i][j].setValue(c);
				if(c == 'e')
				{
					entranceRow = i;
					entranceCol = j;					
				}
			}
		}
	infile.close();
	return true;
}
int Maze::getEntranceRow()
{
		return entranceRow;
}
int Maze::getEntranceCol()
{
		return entranceCol;
}
void Maze::printMaze(bool solutionPrint)
{
	int rows = getRows();
	int cols = getCols();
	if(!solutionPrint)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if(maze[i][j].getValue() == 'p')
					cout<<" "<<" ";
				else
					cout<<maze[i][j].getValue()<< " ";
			}
			cout<<endl;
		}
	}
	else
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if(maze[i][j].getValue() == 'p')
				{
					if(maze[i][j].getisSolution())
					
						cout<<"s"<<" ";
					else
						cout<<" "<<" ";
				}
				else
					cout<<maze[i][j].getValue()<<" ";
			}
			cout<<endl;
		}
	}
}
void Maze::runHermione()
{
	bool found = false;

	/* Used to track the last cell i.e. the parent */
	int previousRow = entranceRow;
	int previousCol = entranceCol;

	/* Remember to get the directions as you pop */
	stack<Cell> holdValues;
	stack<Cell> neighborCells;

	/* Initializing the Cell's data members as well as the stack */
	Cell c; 
	c.setRow(entranceRow);
	c.setCol(entranceCol);
	c.setparentRow(entranceRow);
	c.setparentCol(entranceCol);
	
	HermioneSolution.push(c);	

	/* Loop to find the horocrux */
	while(!found && !HermioneSolution.empty())
	{
		/* Taking cell from the stack and marking visited*/
		Cell temp;	
		temp = HermioneSolution.top();
		HermioneSolution.pop();
		temp.setVisited(true);
	


		/* Variables to modify the neighbor Cell */
		int currentRow = temp.getRow();
		int currentCol = temp.getCol();	
		char nextDir = temp.getDirection();
		temp.setparentRow(previousRow);
		temp.setparentCol(previousCol);
		maze[currentRow][currentCol].setVisited(true);
		/* Check if it's the horocrux */

		if(maze[currentRow][currentCol].getValue() != 'e')
			
			holdValues.push(temp);

		if(temp.getValue() == 'h')
		{
			holdValues.push(temp);	
			found = true;
			continue;
		}

		/* Initialize variables to help back tracking */
		int neighbors = 0;

		/* Get every neighbor of the current Cell and store them in temporary variables */
		for(int i = 0; i < 4; i++)
		{
			Cell n1;
			/* Check North */
			if(nextDir == 'N')
			{
				n1.setRow(currentRow - 1);
				n1.setCol(currentCol);		
				nextDir = 'S';
				char ch = 'N';
				temp.setDirection(ch);
			}
			/* Check South */
			else if(nextDir == 'S')
			{
				n1.setRow(currentRow + 1);
				n1.setCol(currentCol);
				nextDir = 'W';
				char ch = 'S';
				temp.setDirection(ch);
			}
			/* Check West */
			else if(nextDir == 'W')
			{
				n1.setRow(currentRow);
				n1.setCol(currentCol - 1);
				nextDir = 'E';
				char ch = 'W';
				temp.setDirection(ch);
			}
			/* Check East */
			else if(nextDir == 'E')
			{
				n1.setRow(currentRow);
				n1.setCol(currentCol + 1);
				nextDir = 'N';
				char ch = 'E';
				temp.setDirection(ch);
			}

			int neighborRow = n1.getRow();
			int neighborCol = n1.getCol();
		
			/* Check each neighbor to make sure it's actually a valid location on the grid */
			if(neighborRow > -1 && neighborRow < 10 && neighborCol > -1 && neighborCol < 8)
			{
				/* If this neighbor contains the target */
				if(maze[neighborRow][neighborCol].getValue() == 'h')
				{
					found = true;
					break;
				}


				/* If this neighbor is not a wall and it's not visited */
				else if(maze[neighborRow][neighborCol].getValue() == 'p' && 
						maze[neighborRow][neighborCol].getVisited() == false)
				{
					char currentDirection = temp.getDirection();

					/* Set its parent to the current cell */
					n1.setparentRow(currentRow);
					n1.setparentCol(currentCol);
				
					/* Set its direction to the direction we were traversing */
					
					n1.setDirection(currentDirection);

					/* Pushing to both the final stack and the temp stack */
					neighbors++;
					

					HermioneSolution.push(n1);

				}
			}			
			
		}//end for loop to check neighbors
		if(neighbors > 1)
		{
			maze[currentRow][currentCol].setIntersection(true);
		}
		else if(neighbors == 0 && !found && !holdValues.empty())
		{
			Cell temp = holdValues.top();
			int topRow = temp.getRow();
			int topCol = temp.getCol();

			
			do
			{
				holdValues.pop();
				
				temp = holdValues.top();
				topRow = temp.getRow();
				topCol = temp.getCol();

			}while(maze[topRow][topCol].getIntersection() == false);
				
			temp = HermioneSolution.top();
		}

	}//end while loop looking for h
	stack<Cell> finalstack;
	if(holdValues.empty())
	{
		cout<<"No solution"<<endl;
	}
	else
	{
		/* Re-order the stack to print in correct order */
		while(!holdValues.empty())
		{
			/* Comparing the top two elements on the stack */
			Cell temp;
			temp = holdValues.top();
			
			int solutionRow = temp.getRow();
			int solutionCol = temp.getCol();
		
				maze[solutionRow][solutionCol].setisSolution(true);
				finalstack.push(temp);
				holdValues.pop();
		}
		/* Send the values to printSequence and printSolution*/
		while(!finalstack.empty())
		{
			Cell temp;
			temp = finalstack.top();
			printSequence(temp.getDirection());
			finalstack.pop();
		}
	}
}


/* This solution is completed */
void Maze::runRon()
{

	/* Setting variables */
	Cell path[80] ;
	int pathcount = 0;
	Cell c;
	bool found = false;
	int totalSpots = 0;

	/* Used to track the last cell i.e. the parent */
	int previousRow = entranceRow;
	int previousCol = entranceCol;


	/* Initialize the entrance cell */
	c.setRow(entranceRow);
	c.setCol(entranceCol);
	c.setVisited(true);

	/* We intialize this originally here but it changes inside the while loop */
	c.setparentRow(entranceRow);
	c.setparentCol(entranceCol);

	/* Push the entrance cell to the queue */
	RonSolution.push(c);	

	while(!found && !RonSolution.empty())
	{
		/* Popping the queue and storing it in a temp Cell while marking it visited */
		Cell temp;
		temp = RonSolution.front();
		RonSolution.pop();
		temp.setVisited(true);

		/* Variables to modify the neighbor Cell */
		int currentRow = temp.getRow();
		int currentCol = temp.getCol();
		char nextDir = temp.getDirection();		
		path[pathcount] = temp;
		pathcount++;


		/* Changing the parent rows/cols to be whatever cell we just checked */
		temp.setparentRow(previousRow);
		temp.setparentCol(previousCol);

		/* Checking if the first item in the queue is the horocrux cell */
		if(temp.getValue() == 'h')
		{
			found = true;
			RonSolution.push(temp);
			break;
		}

		/* This loop checks every side of the current Cell to find a valid neighbor */
		for(int i = 0; i < 4; i++)
		{
			Cell n1;
			/* Check North */
			if(nextDir == 'N')
			{
				n1.setRow(currentRow - 1);
				n1.setCol(currentCol);		
				nextDir = 'S';
				char ch = 'N';
				temp.setDirection(ch);
			}
			/* Check South */
			else if(nextDir == 'S')
			{
				n1.setRow(currentRow + 1);
				n1.setCol(currentCol);
				nextDir = 'W';
				char ch = 'S';
				temp.setDirection(ch);
			}
			/* Check West */
			else if(nextDir == 'W')
			{
				n1.setRow(currentRow);
				n1.setCol(currentCol - 1);
				nextDir = 'E';
				char ch = 'W';
				temp.setDirection(ch);
			}
			/* Check East */
			else if(nextDir == 'E')
			{
				n1.setRow(currentRow);
				n1.setCol(currentCol + 1);
				nextDir = 'N';
				char ch = 'E';
				temp.setDirection(ch);
			}

			int neighborRow = n1.getRow();
			int neighborCol = n1.getCol();

			/* Check each neighbor to make sure it's actually a valid location on the grid */
			if(neighborRow > -1 && neighborRow < 10 && neighborCol > -1 && neighborCol < 10)
			{	
				/* If this neighbor contains the target */
				if(maze[neighborRow][neighborCol].getValue() == 'h')
				{
					found = true;
					RonSolution.push(n1);
					break;
				}


				/* If this neighbor is not a wall and it's not visited */
				if(maze[neighborRow][neighborCol].getValue() == 'p' && 
						maze[neighborRow][neighborCol].getVisited() == false)
				{
					/* Get the current direction that we are travelling */
					char currentDirection = temp.getDirection();	


					/* Set its visited to true. Also change the 2d array which we are using to track where we've been */
					maze[neighborRow][neighborCol].setVisited(true);
					n1.setVisited(true);				

					/* Set its parent to the current cell */
					n1.setparentRow(currentRow);
					n1.setparentCol(currentCol);


					/* Set its direction to the direction we were traversing */
					n1.setDirection(currentDirection);
					RonSolution.push(n1);
				}
			}
		}//end for loop to search for neighbors



	}//end search for horcrux 


	if(RonSolution.empty())
	
		cout<<"No solution"<<endl;

	else

	{	
		int initialLength = pathcount - 1;
		while(pathcount > 0)
		{

			/* Grab the parent row and column of the last(X) cell in the path */ 
			int pathCellpRow = path[pathcount - 1].getparentRow();
			int pathCellpCol = path[pathcount - 1].getparentCol();			

			/* Grab the value of the Cell in the position X-1 in the path */
			int pathParentRow = path[pathcount - 2].getRow();
			int pathParentCol = path[pathcount - 2].getCol();


			/* If they're equal, we assume they're in the right order and move to the next pair */
			if(pathCellpRow == pathParentRow && pathCellpCol == pathParentCol)
			{
				pathcount--;
				totalSpots++;
			}	
			/* If they're not equal, we assume the previous element is garbage and remove it */
			else
			{
				for(int i = pathcount - 2; i < initialLength; i++)

					path[i] = path[i + 1];

				pathcount--;
			}

		}
	}

	/* Printing out the solution sequence */
	for(int i = 0; i < totalSpots; i++)
	{
		Cell temp = path[i];
		/* Need to update maze with the solution sequence */
		int solutionRow = temp.getRow();
		int solutionCol = temp.getCol();	
		maze[solutionRow][solutionCol].setisSolution(true);
		printSequence(temp.getDirection());
			
	}			


}
void Maze::printSequence(char c)
{
	char temp = c;
	cout<<" Move: "<<c<<endl;
}
void Maze::printSolution()
{
	printMaze(true);
}
int Maze::getRows()
{
	return numRows;
}
void Maze::setRows(int row)
{
	numRows = row;
}
int Maze::getCols()
{
	return numCols;
}
void Maze::setCols(int col)
{
	numCols = col;
}
void Maze::initMaze()
{
	for(int i = 0; i < getRows(); i++)
	{
		for(int j = 0; j < getCols(); j++)
		{
			maze[i][j].setDirection('N');
			maze[i][j].setVisited(false);
			maze[i][j].setisSolution(false);
			maze[i][j].setIntersection(false);
		}
	}
}	
#include "Maze.cpp"
#endif
