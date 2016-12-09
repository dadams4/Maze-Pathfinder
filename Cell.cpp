/* Daniel Adams
   CPSC 340
   Cell.cpp
*/

#ifndef CELLCPP
#define CELLCPP

#include "Cell.h"

#include <iostream>

using namespace std;


Cell::Cell()
{
	direction = 'N';
	parentRow = 0;
	parentCol = 0;
	visited = false;
	isIntersection = false;
	backtracked = false;
	isSolutionCell = false;
	row = 0;
	col = 0;
}
char Cell::getDirection()
{
	return direction;	
}
void Cell::setDirection(char newDir)
{
	direction = newDir;
}
int Cell::getparentRow()
{
	return parentRow;
}
void Cell::setparentRow(int newRow)
{
	parentRow = newRow;
}
int Cell::getparentCol()
{
	return parentCol;
}
void Cell::setparentCol(int newCol)
{
	parentCol = newCol;
}
bool Cell::getbackTrack()
{
	return backtracked;
}
void Cell::setbackTrack(bool bt)
{
	backtracked = bt;
}
bool Cell::getVisited()
{
	return visited;
}
void Cell::setVisited(bool visit)
{
	visited = visit;
}
int Cell::getRow()
{
	return row;
}
void Cell::setRow(int newRow)
{
	row = newRow;
}
int Cell::getCol()
{
	return col;
}
void Cell::setCol(int newCol)
{
	col = newCol;
}
char Cell::getValue()
{
	return value;
}
void Cell::setValue(char newVal)
{
	value = newVal;
}
bool Cell::getIntersection()
{
	return isIntersection;
}
void Cell::setIntersection(bool inter)
{
	isIntersection = inter;
}
bool Cell::getisSolution()
{
	return isSolutionCell;
}
void Cell::setisSolution(bool yes)
{
	isSolutionCell = yes;
}
#endif
