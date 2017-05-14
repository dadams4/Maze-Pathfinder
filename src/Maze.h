/* Daniel Adams
   CPSC 340
   Maze.h
*/
#ifndef MAZEH
#define MAZEH
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "Cell.h"
using namespace std;
class Maze
{
	public:
		Maze();
		bool readMaze(string filename);
		void runHermione();
		void runRon();
		void printSequence(char c);
		void printSolution();
		int getEntranceRow();
		int getEntranceCol();
		void printMaze(bool solutionPrint);
		int getRows();
		void setRows(int row);
		int getCols();
		void setCols(int cols);
		void initMaze();
		
	private:
		Cell maze[10][10];
		int entranceRow;
		int entranceCol;
		int numRows;
		int numCols;
		stack<Cell> HermioneSolution;
		queue<Cell> RonSolution;
};
//#include "Maze.cpp"
#endif
