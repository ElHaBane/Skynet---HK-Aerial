/*
	El Hadji Omar Bane
	6/3/22
	Skynet HK
*/

#include <iostream>	//iostream header file
#include <tgmath.h>
using namespace std; // std == standard


int targetLocationPrediction(int searchGridLowNumber, int searchGridHighNumber) { // gets the midpoint of two numbers
	
	return (((searchGridHighNumber - searchGridLowNumber) / 2) + searchGridLowNumber);
}

bool sharesRow(int lengthOfRows, int a, int b) { //determines if two values in a sorted two dimentional array share the same first value.
	return floor(a / lengthOfRows) == floor(b / lengthOfRows);
}

void discoverEnemy(int TDGrid[8][8],int enemysNum) { // TDGrid means two dimensional grid
	int turns = 0;

	int rowsLength = 8;
	int columnsLength = 8;


	int lowestRow = 0;
	int highestRow = columnsLength - 1;
	int rowPrediction = targetLocationPrediction(lowestRow, highestRow); // starting prediction

	while(!sharesRow(rowsLength, enemysNum, rowPrediction * columnsLength)){ // repeats until it finds what row the enemy is located
		if (rowPrediction * columnsLength > enemysNum) { highestRow = rowPrediction; turns++; }
		else { lowestRow = rowPrediction + 1; turns++; }

		rowPrediction = targetLocationPrediction(lowestRow, highestRow);
	}


	int lowestColumn = 0;
	int highestColumn = rowsLength - 1;
	int columnPrediction = targetLocationPrediction(lowestColumn, highestColumn); // starting prediction

	while (TDGrid[rowPrediction][columnPrediction] != enemysNum) { // repeats until it finds where the enemy is located using the newly discovered row
		if (TDGrid[rowPrediction][columnPrediction] > enemysNum) { highestColumn = columnPrediction; turns++; }
		else { lowestColumn = columnPrediction + 1; turns++; }

		columnPrediction = targetLocationPrediction(lowestColumn, highestColumn); // gets the number in between the lowest and highest column
	}

	cout << "it took " << turns << " tries to find the enemy" << endl;
	cout << "The enemy was on " << TDGrid[rowPrediction][columnPrediction] << endl;
	return;
}


const int ROWS = 8;
const int COLUMNS = 8;
int grid[ROWS][COLUMNS];


int main() {
	srand(time(NULL)); // initializes rand

	for (int row = 0; row < ROWS; row++) { // assigns addresses in the grid numbers in ascending order (0-63)
		for (int column = 0; column < COLUMNS; column++) { grid[row][column] = column + (row * 8); }
	}

	int enemyLocation = rand() % 63; // picks a location for the enemy 

	discoverEnemy(grid, enemyLocation);

	system("pause");
	return 0;
}