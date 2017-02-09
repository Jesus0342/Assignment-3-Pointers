/******************************************************************************
* PROGRAMMED BY  : Jesus Sanchez
* STUDENT ID     : 1024834
* CLASS          : MW: 1:30pm - 2:50pm
* ASSIGNMENT #3  : Pointers
******************************************************************************/

#ifndef EQUIPMENT_H_
#define EQUIPMENT_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

namespace receipt
{
	#define NAME 27
	#define	COST 7
	#define QUANTITY 8
	#define QTY 4
	#define TAX_RATE .0825
}

using namespace receipt;

const int MAX_ITEMS = 5;

class Equipment
{
	public:
		Equipment();
		~Equipment();
		void InitializeInventory(Equipment inventory[]);
		bool FindItem(string searchItem, Equipment inventory[]);
		void SetName(string equipName, Equipment customerOrder[], int index);
		void SetCost(string equipName, Equipment inventory[], Equipment customerOrder[], int index);
		void SetQuantity(int numPurchased, Equipment customerOrder[], int index);
		void UpdateQuantity(int numPurchased, string searchItem, Equipment inventory[]);
		void PrintReceipt(Equipment customerOrder[], int *&numItems);
		void PrintInventory(Equipment inventory[]);

	private:
		string name;
		float  cost;
		int    quantity;
};

#endif
