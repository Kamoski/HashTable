/////////////////////////////////////////////////////////////////////
//
// Cell
//
// Class that is used to store values for hashtable
// it helps to maintain data in ordered manner
//
// Date of creation
// 27.02.2019
//
// Author
// Kamil Kręcichwost
//
// Changelog
// null
//
//*********************************************************************
//
// HashTable
//
// Class that allows user to create and use hashtable type
// !!WARNING: Table does not provide full hashtable with linear probing!!
// !!Table does not function properly when user tries to add new Cell in allready full table!!
//
// Date of creation
// 27.02.2019
//
// Author
// Kamil Kręcichwost
//
// Changelog
// null
//////////////////////////////////////////////////////////////////////Z 


#include <iostream>
#include <string>
#include <fstream>

#define CHECK(a) ((int(order[a]) > 47) && (int(order[a]) < 58))			// Macro used solely to make code clean 

class Cell
{
public:
	// Konstr
	Cell()
		:
	 indexNum(0)
	{
		for (int i = 0; i < 8; ++i) {
			text[i] = 0;
		}
	}
	// Destr
	~Cell() {

	}
	// Konstr copy
	Cell(Cell&copy)
		:
		indexNum(copy.indexNum)
	{
		for (int i = 0; i < 8; ++i) {
			this->text[i] = copy.text[i];
		}
	}
	// Oper =
	Cell& operator= (Cell&equals) {
		this->indexNum = equals.indexNum;
		for (int i = 0; i < 8; ++i) {
			this->text[i] = equals.text[i];
		}
	}

	// Gettery
	int getIndexNum() {
		return indexNum;
	}

	char* getText() {
		return text;
	}

	// Settery

	void setIndexNum(long indexNum_) {
		indexNum = indexNum_;
	}

	void setText( const char* text_) {
		for (int i = 0; i < 8; i++) {
			text[i] = text_[i];
		}
	}

private:
	long indexNum;
	char text[9];
};

class HashTable
{
public:
	// Konstr
	HashTable() 
	:
	tableSize(0)
	{
		data = nullptr;
	}
	// Destr
	~HashTable() {
		delete[]data;
	}
	// Konstr copy
	HashTable(HashTable& copy) 
	:
	tableSize(copy.tableSize)
	{
		delete[]data;
		data = new Cell[copy.tableSize];
		for (int i = 0; i < copy.tableSize; i++) {
			data[i] = copy.data[i];
		}
	}
	// Oper = 
	HashTable& operator= (HashTable& equals) {

		delete[]data;
		data = new Cell[equals.tableSize];
		for (int i = 0; i < tableSize; i++) {
			data[i] = equals.data[i];
		}
	}
	// Adding data to table (Cells)
	void addData(long index_, char* text_) {


		long temp = (index_ +tableSize) % tableSize;
		long iter;
		long i = temp;
		bool notSame = false;

		for (int i = 0; i < tableSize; i++) {
			if (data[i].getIndexNum() == index_) {
				data[i].setText(text_);
				notSame = true;
			}
		}

		if (notSame == false) {
			do {
				if (i < tableSize) {
					if (data[i].getIndexNum() == -1) {
						data[i].setIndexNum(index_);
						data[i].setText(text_);
						break;
					}
				}
				else {
					iter = i % tableSize;
					if (data[iter].getIndexNum() == -1) {
						data[iter].setIndexNum(index_);
						data[iter].setText(text_);
						break;
					}
				}
				++i;
			} while (temp != i % tableSize);
		}
	}

	// Removing data from table (Cells)
	void deleteData(long index_) {


		long i = index_%tableSize;
		do{
			if (data[i%tableSize].getIndexNum() == -2) {

			}
			else if (data[i%tableSize].getIndexNum() == index_) {
				//std::cout << " Usnieto " << index_ << std::endl;
				data[i%tableSize].setIndexNum(-1);
				data[i%tableSize].setText("00000000");
				break;
			}
			++i;
		} while (i != index_ % tableSize);
		dataValidityCheck(i%tableSize);

	}
	// Printing data from table
	void printData(std::istream& whereTo ) {

		// Logic check is done to determine if modulo operation is required on given index number
		for (int i = 0; i < this->getTableSize(); i++) {
			if ((data[i].getIndexNum() > this->getTableSize()) && (data[i].getIndexNum() != -1)) {
			std::cout << i << " " << data[i].getIndexNum()
					<< " "<<data[i].getText() << std::endl;
		}
			else if ( (data[i].getIndexNum() <= this->getTableSize()) && (data[i].getIndexNum() != -1) ) {
			std::cout << i << " " << data[i].getIndexNum()
				<< " " << data[i].getText() << std::endl;
			}
		}
		printf("\n");

	}
	// Set size of given hashTable, if table already exists, delete and create new - empty one
	void setDataLength(long value_) {
		
		if (value_ == 0) {
			tableSize = value_;
			data = new Cell[value_];

			for (size_t i = 0; i < value_; i++) {
				data[i].setIndexNum(-1);
				data[i].setText("");
			}
		}
		else {
			delete[]data;
			tableSize = value_;
			data = new Cell[value_];

			for (size_t i = 0; i < value_; i++) {
				data[i].setIndexNum(-1);
				data[i].setText("");
			}
		}
	}

	long getTableSize() const {
		return tableSize;
	}

	// Function that makes sure that data is spread properly across table

	void dataValidityCheck(long _index) {

		
			long temp = _index;
			long i = temp;
			long lastProperIndex = -2;
			++i;
			do {

					if (data[i%tableSize].getIndexNum() == -1) {
						break;
					}
					else if ( (data[i%tableSize].getIndexNum() % tableSize) == temp) 
					{
						lastProperIndex = i%tableSize;
					}

				++i;

			} while (temp != i % tableSize);

		if (lastProperIndex != -2) {
			swapCells(data[temp], data[lastProperIndex], lastProperIndex);
		}
		else {
			long i = _index;
			do {
				++i;
				if (data[i%tableSize].getIndexNum() == -1) {
					break;
				}

				if (i > tableSize) {
					if
						(
						(data[i%tableSize].getIndexNum() % tableSize != i % tableSize)
							&&
							((data[i%tableSize].getIndexNum() % tableSize) < _index)
							&&
							((data[i%tableSize].getIndexNum() % tableSize) > i%tableSize)
							)
					{
						lastProperIndex = i % tableSize;
					}
				}
				else {
					if
							(
							(data[i%tableSize].getIndexNum() % tableSize != i % tableSize)
							&&
							((data[i%tableSize].getIndexNum() % tableSize) < _index)
							)
					{
						lastProperIndex = i % tableSize;
					}

				}
				

			} while (i%tableSize != _index );

			if (lastProperIndex != -2)
			{
				swapCells(data[_index], data[lastProperIndex], lastProperIndex);
			}
		}
	}

	void swapCells(Cell& left, Cell& right, long& _index) {
		Cell temp;
		temp.setIndexNum(left.getIndexNum());
		temp.setText(left.getText());

		left.setIndexNum(right.getIndexNum());
		left.setText(right.getText());

		right.setIndexNum(temp.getIndexNum());
		right.setText(temp.getText());
		dataValidityCheck(_index);
	}

private:
	int tableSize;
	Cell *data;

};

char parseOrders(std::string& order, long &value);					// Explanation with f definition

int main()
{
	std::ifstream inf;
	//std::istream&in = inf;				// Section dealing with console/file i/o
	std::istream&in = std::cin;

	std::string inOrder = "";
	long value = 0;
	int numberOfCases = 1;					// Few helpful variables
	char order = ' ';
	HashTable *tab = nullptr;
 
		for (int i = 0; numberOfCases > i;) {				// Main loop
			
			do {
				getline(in, inOrder);				// Reading line
				order = parseOrders(inOrder, value);

				switch (order)									// Understanding an order
				{
				case 'A':
					tab[i].addData(value, &inOrder[0]);			// ADD DATA
					break;
				case 'D':
					tab[i].deleteData(value);					// DELETE DATA
					break;
				case 'P':
					tab[i].printData(in);						// PRINT DATA
					break;
				case 'S':
					i++;										// STOP SECTION
					break;
				case 'N':
					numberOfCases = value;						// NUMBER OF CASES
					tab = new HashTable[value];
					break;
				case 'Y':
					tab[i].setDataLength(value);				// LENGTH OF TABLE IN CASE
					break;
				}
			} while (order != 'S' );

		}
}

char parseOrders(std::string& order, long &value) {				// Function parsing a single order

	std::string temporary = "";
	std::string holdData = "";								// Few helpful variables
	bool keepReading = true;

	if (CHECK(0)) {
		for (size_t i = 0; i < order.size(); i++) {
				temporary += order[i];							// NUMBER OF CASES PARSER
		}
		value = std::stoi(temporary);
		temporary = "";
		return 'N';
	}
	else {
			for (size_t i = 0; i < order.size(); i++) {

				if (keepReading == true)				// Check if first part of order is parsed
					temporary += order[i];

				if (temporary == "size ") {								// Check type of order
					keepReading = false;								// Means that first part of order is parsed
					if (CHECK(i)) {										// Check if next value is number
						for (size_t j = i; j < order.size(); j++) {		// Loop for rest of numbers
							holdData += order[j];						// Add each to numbers variable
							value = std::stoi(holdData);				// Translate numbers string to number
						}												
						return 'Y';										// Return which order have been parsed
					}
					
				}														// All functions work ackordingly

				if (temporary == "add ") {
					keepReading = false;
					if ( CHECK(i) ) {
						for (i; CHECK(i); i++) {
							holdData += order[i];
							value = std::stoi(holdData);
						}
						holdData = "";
						i++;
						for (i; i < order.size(); i++) {
							holdData += order[i];
						}
						order = holdData;
						return 'A';
					}
				}

				if (temporary == "delete ") {
					keepReading = false;
					if (CHECK(i)) {
						for (size_t j = i; j < order.size(); j++) {
							holdData += order[j];
							value = std::stoi(holdData);
						}
						return 'D';
					}
				}

				if (temporary == "print") {
					keepReading = false;
					return 'P';
				}

				if (temporary == "stop") {
					keepReading = false;
					return 'S';
				}
			
			}
			keepReading = true;
	}
}