#include <list>
#include <string>
#include <iostream> 
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

// Global constants & variables 
const int MAX_SIZE = 10;
int rows = 4;
int columns = 4;
int mazeArray[MAX_SIZE][MAX_SIZE]; // 2D array of ints for maze cells - 0 = clear, 1 = wall

struct position
{
	position()
	{
		row = 1;
		col = 0;
	}

	position(int r, int c)
	{
		row = r;
		col = c;
	}

	int row;
	int col;

	//compares two positions, returns true if they match
	bool compareLocation(const position location) const
	{
		return row == location.row && col == location.col;
	};
};

list<position> solution;  // should be in order from start position to end position
#include "graphics.h" // application-specific graphics functions, uses global vars defined above

 /*
* Function inserts a string, char by char into the mazeArray properly
*/
void insertIntoMazeArray(const string line, const int row, const int cols)
{
	int c = 0;
	for (int i = 0; i < line.length(); ++i)
	{
		if (line.at(i) != ' ')
		{
			mazeArray[row][c] = line.at(i) - 48;// convert char to int
			++c;
		}
	}
};
/*
* Function finds the start of the maze, returns a int representing the row
*/
int findAStart()
{
	for (int r = 0; r < rows; ++r)
	{
		if (mazeArray[r][0] == 0)
			return r;
	}
}
/*
* Function finds the end of the maze, returns a int representing the row
*/
int findAEnd()
{
	for (int r = 0; r < rows; ++r)
	{
		if (mazeArray[r][columns - 1] == 0)
			return r;
	}
}

int main()
{
	// Queue --> Stacks -->Stack of positions
	stack<position> stackOfPaths;
	queue<stack<position>> queueOfStacks;
	string fileName = "";
	cout << "Enter the name of the file containing the maze." << endl;
	cin >> fileName;

	string singleLine;//temp string used to read from a txt file
	ifstream myStream(fileName);

	if (myStream.is_open())
	{
		getline(myStream, singleLine);
		rows = singleLine.at(0) - 48;// convert char to int
		columns = singleLine.at(2) - 48;
		mazeArray[rows][columns];// maze is given a new size

		int rowCount = 0;
		int colCount = 0;
		//going through all lines in the txt file
		while (getline(myStream, singleLine))
		{
			insertIntoMazeArray(singleLine, rowCount, colCount);
			++rowCount;
			++colCount;
		}
	}
	myStream.close();

	position startPosition(findAStart(), 0);
	position endPosition(findAEnd(), columns - 1);// -1 to offset 0 based counting

	stackOfPaths.push(startPosition);//pushing the start position to the stack
	queueOfStacks.push(stackOfPaths);//pushing the stack to the queue

	while (!queueOfStacks.front().top().compareLocation(endPosition))
	{
		//resetting the stackOfPaths to the first stack in the Queue
		//aka setting the stack equal to all previous valid moves
		stackOfPaths = queueOfStacks.front();
		int r = stackOfPaths.top().row;//using new row values
		int c = stackOfPaths.top().col;//using new row values

		queueOfStacks.pop();//removing the front of the queue becasue it didn't contain the solution
							//if statements checks the vailtiy of the moves including bounds
		if (c + 1 < columns && mazeArray[r][c + 1] == 0) {//moving right
			position move(r, c + 1);//making a right step
			stackOfPaths.push(move);//adding the step
			queueOfStacks.push(stackOfPaths);//adding the stack of potential solutions to the queue
			stackOfPaths.pop();//removing the new step so another can be added later
		}
		if (c - 1 >= 0 && mazeArray[r][c - 1] == 0) {//moving left
			position move(r, c - 1);
			stackOfPaths.push(move);
			queueOfStacks.push(stackOfPaths);
			stackOfPaths.pop();
		}
		if (r + 1 < rows && mazeArray[r + 1][c] == 0) {//moving down
			position move(r + 1, c);
			stackOfPaths.push(move);
			queueOfStacks.push(stackOfPaths);
			stackOfPaths.pop();
		}
		if (r - 1 >= 0 && mazeArray[r - 1][c] == 0) {//moving up
			position move(r - 1, c);
			stackOfPaths.push(move);
			queueOfStacks.push(stackOfPaths);
			stackOfPaths.pop();
		}
	}

	//Saving the stack Of Solutions
	stack<position> stackOfSolutions = queueOfStacks.front();
	int size = stackOfSolutions.size();

	//Pushing the positions off the solutions stack onto the solution list for graphics
	for (int i = 0; i < size; ++i) {
		solution.push_back(stackOfSolutions.top());
		stackOfSolutions.pop();
	}
	solution.reverse();
	//Printing out the output position via iterator
	list<position>::iterator itr;
	for (itr = solution.begin(); itr != solution.end(); ++itr)
	{
		cout << "--> [" << itr->row << "," << itr->col << "]" << endl;
	}
	start_graphics_loop();

	return EXIT_SUCCESS;
}