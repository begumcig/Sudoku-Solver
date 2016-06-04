#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>

using namespace std;

struct CellCoor
{
	int columnCoor;
	int rowCoor;
	int squareCoor;
	CellCoor::CellCoor(int c, int r, int s)
		:columnCoor(c),rowCoor(r),squareCoor(s)
	{}
};

struct PossibleValue
{
	int value;
	bool possible;
	PossibleValue::PossibleValue(int i, bool b)
		:value(i),possible(b)
	{}
};

class Cell
{
public:
	vector <PossibleValue> possibleValues;
	vector <int> onlyPossibleValues;
	int value;
	bool changeable;
	CellCoor coordinates;

	Cell(int val, CellCoor coor);
	void findPossibleValues (vector <Cell> map);
	void setPossibleVector();
	void searchColumn(vector <Cell> map);
	void searchRow(vector <Cell> map); 
	void searchSquare(vector <Cell> map);
	void moveForward(vector <Cell> & map);
	int howManyPossible();
	
	  



private:
	void initializePossibleValues();





};



#endif