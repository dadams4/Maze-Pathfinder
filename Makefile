run: Cell.o Maze.o MazeApp.o
	g++ Cell.o Maze.o MazeApp.o -o run

MazeApp.o: MazeApp.cpp Maze.o Cell.o
	g++ -c MazeApp.cpp

Maze.o: Maze.cpp Maze.h
	g++ -c Maze.cpp

Cell.o: Cell.cpp Cell.h
	g++ -c Cell.cpp

clean:
	rm -rf *.o
