/* Daniel Adams
   CPSC 340
   Cell.h
*/
#ifndef CELLH
#define CELLH

#include <iostream>

using namespace std;

class Cell
{
	private:
		/* Direction currently being traveled */
		char direction;
		char value;		
		int parentRow;
		int parentCol;
		bool visited;
		bool isSolutionCell;
		bool isIntersection;
		
		/* If the previous move was a backtrack */
		bool backtracked; 

		int row;
		int col;
	public:
		Cell();
		
		char getValue();
		void setValue(char newValue);

		char getDirection();
		void setDirection(char newDir);
	
		int getparentRow();
		void setparentRow(int newRow);

		int getparentCol();
		void setparentCol(int newCol);

		bool getVisited();
		void setVisited(bool visit);

		bool getbackTrack();
		void setbackTrack(bool bt);
		
		int getRow();
		void setRow(int newRow);
	
		int getCol();
		void setCol(int newCol);

		bool getIntersection();
		void setIntersection(bool inter);
		
		bool getisSolution();
		void setisSolution(bool yes);
};
//#include "Cell.cpp"
#endif		
