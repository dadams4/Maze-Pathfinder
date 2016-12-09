/* Daniel Adams
   CPSC 340
   runGame.cpp
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Maze.h"
#include <cstdlib>

using namespace std;

int main(void)
{
	Maze m;
	string filename;
	system("clear");
	cout<<"Welcome Harry, let's find the horocrux!"<<endl;
	cout<<"Please enter a maze to search: ";
	cin>>filename;

	if(!m.readMaze(filename.c_str()))
		return 0;

	cout<<"Running Hermione's Solution"<<endl;
	cout<<"Original maze: "<<endl;
	m.printMaze(false);
	cout<<"Solution sequence is as follows: "<<endl;
	m.runHermione();
	cout<<"Final path: "<<endl;
	m.printSolution();
	cout<<endl;
	
	/* Clean up the maze between runs */
	m.initMaze();	

	cout<<"Running Ron's Solution"<<endl;
	cout<<"Original maze: "<<endl;
	m.printMaze(false);
	cout<<"Solution sequence is as follows: "<<endl;
	m.runRon();
	cout<<"Final path: "<<endl;
	m.printSolution();
	cout<<endl;

	cout<<"Thanks for using our pathfinder Harry!"<<endl;	
	return 0;

}
