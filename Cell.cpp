#include "Cell.h"



Cell::Cell(int val, CellCoor coor) : coordinates(coor)
{
	value = val;
	if(value == 0)
	{
		initializePossibleValues();
		changeable = true;
	}
	else
	{
		possibleValues.push_back(PossibleValue(value,true));
		changeable = false;
	}
}





//  All values are initialized to possible when we first go on an empty cell. //
//  The sorting will be done after.  ///////////////////////////////////////////
void Cell::initializePossibleValues()
{
	for(int i = 1; i < 10; i++)
	{
		possibleValues.push_back(PossibleValue(i, true));
	}
}





// This function takes the user-given sudoku puzzle as its input.  ////////////////////////////////////////////// 
// For an empty cell, the function eliminates the numbers which exist on the same column with the empty cell.  //
void Cell::searchColumn(vector <Cell> map)
{

	int xCor = coordinates.columnCoor;
	//cout << "This is the cell with the coordinates (" << xCor << "," << coordinates.rowCoor << ")" << endl;

	// This loop starts from the first row with the same column as the input cell, and loops until the last row is reached.  //
	for(int i = xCor; i <= (xCor + 72); i = i + 9)
	{
		//cout << "The searched x coordinates are: " << i << endl;
		if(map[i].value !=0 && (coordinates.rowCoor *9 + xCor) != i)
		{
			if(map[i].value > 9 || map[i].value < 0)
				cout << "You entered a number bigger than 9 or smaller than 0. This sudoku is not valid." << endl;
			else
				possibleValues[(map[i].value) -1].possible = false;

		}
	}
}





// This function takes the user-given sudoku puzzle as its input.  /////////////////////////////////////////// 
// For an empty cell, the function eliminates the numbers which exist on the same row with the empty cell.  //
void Cell::searchRow(vector <Cell> map)
{
	int yCor = coordinates.rowCoor;
	//cout << "This is the cell with the coordinates (" << coordinates.columnCoor << "," << coordinates.rowCoor << ")" << endl;

	//  This loop stars from the first element of the cell element's row, and iterates through the same row.  //
	for(int i = (yCor * 9); i < (yCor * 9 + 9); i++) 
	{
		//cout << "The searched y coordinates are: " << i << endl;
		if (map[i].value != 0 && !(i >= (coordinates.rowCoor *9 + coordinates.columnCoor) && map[i].changeable == true))
		{
			if(map[i].value > 9 || map[i].value < 0)
				cout << "You entered a number bigger than 9 or smaller than 0. This sudoku is not valid." << endl;
			else 
				possibleValues[(map[i].value) -1].possible = false;
		}
	}
}





// This function takes the user-given puzzle as the input and checks the 3X3 square that the cell belongs to. //
void Cell::searchSquare(vector <Cell> map)
{
	int sCor = coordinates.squareCoor;

	//this gives the beginning position of the 3 x 3 square on the map.  //
	int sqStartCoordinate = (((sCor - 1) / 3) * 27) + (((sCor - 1) % 3) * 3); 

	//out << "This is the cell with the coordinates (" << coordinates.columnCoor << "," << coordinates.rowCoor << ")" << endl;
	//cout << "This is the square" << sCor << endl;
	//cout << "The beginning posision on the puzzle map is " << sqStartCoordinate << endl;


	for(int i = 0; i < 3; i++)
	{
		for(int j = sqStartCoordinate; j < sqStartCoordinate + 3; j++)
		{
			//cout << "the position you are checking on the puzzle map is  " << j << endl;
			if(map[j].value != 0 && !(j >= (coordinates.rowCoor *9 + coordinates.columnCoor) && map[j].changeable == true) ) 
			{
				
				if(map[j].value > 9 || map[j].value < 0)
					cout << "You entered a number bigger than 9 or smaller than 0. This sudoku is not valid." << endl;
				else
					possibleValues[(map[j].value) -1].possible = false;
			}
		}
		sqStartCoordinate = sqStartCoordinate + 9;
	}
}

//This function searches a cell's row column and square and then pushes the possible values into a vector  //
void Cell::findPossibleValues(vector <Cell> map)
{
	possibleValues.clear();
	initializePossibleValues();
	searchColumn(map);
	searchRow(map);
	searchSquare(map);

}

/*void Cell::setPossibleVector()
{
	for(int i = 9; i < 0; i--)
	{ 
		if(possibleValues[i].possible)
			onlyPossibleValues.push_back(possibleValues[i].value);
	}
}*/

int Cell::howManyPossible()
{
	int count = 0;
	for(int i = 0; i<possibleValues.size(); i++)
	{
		if(possibleValues[i].possible == true)
			count++;
	}
	return count;
}

