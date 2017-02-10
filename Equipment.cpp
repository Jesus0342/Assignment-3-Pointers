/******************************************************************************
* PROGRAMMED BY  : Jesus Sanchez
* STUDENT ID     : 1024834
* CLASS          : MW: 1:30pm - 2:50pm
* ASSIGNMENT #3  : Pointers
******************************************************************************/

#include "Equipment.h"

/******************************************************************************
 * Equipment
 * ----------------------------------------------------------------------------
 * Default class constructor. Initializes all data members to 0.
 *****************************************************************************/
Equipment::Equipment() : name(""), cost(0.0), quantity(0)
{
}

/******************************************************************************
 * Equipment
 * ----------------------------------------------------------------------------
 * Class destructor. Does nothing.
 *****************************************************************************/
Equipment::~Equipment()
{
}

/******************************************************************************
 * InitializeInventory
 * ----------------------------------------------------------------------------
 * This function initializes the data members of the Equipment objects in the
 * inventory array by reading in the name, cost, and quantity of each item
 * from a text file.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     inventory - Array of Equipment objects is not defined.
 *
 * POST-CONDITIONS:
 *     Initializes all Equipment objects in the inventory array.
 *****************************************************************************/
void Equipment::InitializeInventory(Equipment inventory[])
{
	ifstream fin;

	int index = 0;

	fin.open("Inventory.txt");

	// Reads in the name, cost, and quantity of each item into an index of the
	// inventory array.
	while(!(fin.eof()) && index < MAX_ITEMS)
	{
		getline(fin, inventory[index].name);

		fin >> inventory[index].cost;
		fin.ignore(1000, '\n');

		fin >> inventory[index].quantity;
		fin.ignore(1000, '\n');

		index++;
	}

	fin.close();
}

/******************************************************************************
 * PrintInventory
 * ----------------------------------------------------------------------------
 * This function prints the inventory of equipment by outputting the name, cost,
 * and quantity of each Equipment item stored in the inventory array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     inventory - Array of Equipment objects must be defined.
 *
 * POST-CONDITIONS:
 *     Print's the inventory.
 *****************************************************************************/
void Equipment::PrintInventory(Equipment inventory[])
{
	// Prints column headings.
	cout << left << setw(NAME)   << "Name of Equipment" << setw(1) << " "
		 << setw(COST) << "Cost" << setw(QUANTITY) << "Quantity" << endl;

	// Prints lines to underline column headings.
	cout << setw(NAME) << "-----------------" << setw(1) << "-"
		 << setw(COST) << "------" << setw(QUANTITY) << "--------" << endl;

	// Prints the name, cost, and quantity of each object in the inventory array.
	for(int index = 0; index < MAX_ITEMS; index++)
	{
		cout << setw(NAME) << inventory[index].name << setw(1) << "$"
			 << setw(COST) << inventory[index].cost << right
			 << setw(QUANTITY - 3) << inventory[index].quantity << left << endl;
	}

	cout << endl << right;
}

/******************************************************************************
 * FindItem
 * ----------------------------------------------------------------------------
 * This function receives the name of the equipment entered by the customer and
 * compares that name to the names stored in the inventory array. If two names
 * match, the function returns true meaning that the customer's input is valid.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     searchItem - Name of Equipment being searched for must be defined.
 *     inventory  - Array of Equipment objects must be defined.
 *
 * POST-CONDITIONS:
 *     Returns true if the customer's input is valid and false if not.
 *****************************************************************************/
bool Equipment::FindItem(string searchItem, Equipment inventory[])
{
	bool found = false; // Determines whether or not the name entered matches
						// a name in the specified index of inventory
	int  index = 0;

	// Searches for the name entered by the customer in the inventory array until
	// one of the names is a match or until index equals the array size.
	while(!found && index < MAX_ITEMS)
	{
		// If the name entered by the customer matches a name in the array, true
		// is assigned to found and the loop is exited.
		if(searchItem == inventory[index].name)
		{
			found = true;
		}
		else
		{
			index++;
		}
	}

	return found;
}

/******************************************************************************
 * SetName
 * ----------------------------------------------------------------------------
 * This function sets the name data member in the current index of the dynamic
 * array to the name entered by the customer.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     equipName     - Name of item must be defined.
 *     customerOrder - Dynamic Array of Equipment objects must be defined.
 *     index         - Index being accessed must be defined.
 *
 * POST-CONDITIONS:
 *     Sets the name of the Equipment object in the current index.
 *****************************************************************************/
void Equipment::SetName(string equipName, Equipment customerOrder[], int index)
{
	customerOrder[index].name = equipName;
}

/******************************************************************************
 * SetCost
 * ----------------------------------------------------------------------------
 * This function sets the cost data member in the current index of the dynamic
 * array by searching for the index where the item is stored in the inventory
 * array and assigning the cost in that index to the index being accessed in
 * the dynamic array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     equipName     - Name of item must be defined.
 *     inventory     - Array of Equipment objects must be defined.
 *     customerOrder - Dynamic Array of Equipment objects must be defined.
 *     index         - Index being accessed must be defined.
 *
 * POST-CONDITIONS:
 *     Sets the cost of item to be purchased in the indicated index of array.
 *****************************************************************************/
void Equipment::SetCost(string equipName, Equipment inventory[],
						Equipment customerOrder[], int index)
{
	int index2 = 0; // Index used to search inventory from the beginning

	while(equipName != inventory[index2].name)
	{
		index2++;
	}

	customerOrder[index].cost = inventory[index2].cost;
}

/******************************************************************************
 * SetQuantity
 * ----------------------------------------------------------------------------
 * This function sets the quantity data member in the current index of the
 * dynamic array to the quantity entered by the customer.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     numPurchased  - Quantity of item purchased must be defined.
 *     customerOrder - Dynamic Array of Equipment objects must be defined.
 *     index         - Index being accessed must be defined.
 *
 * POST-CONDITIONS:
 *     Sets the quantity of the Equipment object in the current index.
 *****************************************************************************/
void Equipment::SetQuantity(int numPurchased, Equipment customerOrder[], int index)
{
	customerOrder[index].quantity = numPurchased;
}

/******************************************************************************
 * UpdateQuantity
 * ----------------------------------------------------------------------------
 * This function updates the quantity of an Equipment object in the inventory
 * array by finding the index of the item using the name entered by the customer
 * and subtracting the quantity entered by the customer from the quantity stored
 * in the inventory array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     numPurchased - Quantity of item purchased must be defined.
 *     searchItem   - Name of Equipment to be searched for must be defined.
 *     inventory    - Array of Equipment objects must be defined.
 *
 * POST-CONDITIONS:
 *     Updates the quantity of an Equipment object in the inventory array.
 *****************************************************************************/
void Equipment::UpdateQuantity(int numPurchased, string searchItem, Equipment inventory[])
{
	int index = 0;

	// Finds the index of the item to be purchased so that the quantity can
	// be subtracted from the correct item.
	while(searchItem != inventory[index].name)
	{
		index++;
	}

	// Subtracts the quantity entered by the customer from the total quantity and
	// stores that in the quantity data member of the index of the inventory array.
	inventory[index].quantity -= numPurchased;
}

/******************************************************************************
 * PrintReceipt
 * ----------------------------------------------------------------------------
 * This function prints the customer's receipt by outputting the quantity, name,
 * and cost of each item purchased and outputting the subtotal and total after
 * the tax rate has been added.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     numItems      - Array size must be defined.
 *     customerOrder - Dynamic Array of Equipment objects must be defined.
 *
 * POST-CONDITIONS:
 *     Print's the customer's receipt.
 *****************************************************************************/
void Equipment::PrintReceipt(Equipment customerOrder[], int *&numItems)
{
	float subTotal = 0.0; // Initializes accumulator to 0.

	cout << setw(27) << endl << "----- RECEIPT -----" << endl;

	// Prints the column headings.
	cout << fixed << setprecision(2) << left
		 << setw(QTY)  << "QTY"  << setw(NAME) << "ITEM" << setw(1) << " "
		 << setw(COST) << "COST" << endl;

	// Prints lines to underline column headings.
	cout << setw(QTY)  << "---" << setw(NAME) << "----" << setw(1) << "-"
		 << setw(COST) << "-----" << endl;

	// Prints the quantity, name, and cost of each item in the dynamic array.
	for(int index = 0; index < *numItems; index++)
	{
		cout << setw(QTY)  << customerOrder[index].quantity
			 << setw(NAME) << customerOrder[index].name << setw(1) << "$"
			 << setw(COST) << customerOrder[index].cost << endl;

		// Accumulates the total cost of the items in the order by multiplying
		// the cost of each item by the quantity purchased.
		subTotal += (customerOrder[index].cost * customerOrder[index].quantity);
	}

	// Prints the subtotal, tax, and total of the order.
	cout << "\nSUBTOTAL: $" << subTotal  << endl
		 << "TAX:      $"   << (subTotal * TAX_RATE) << endl
		 << "TOTAL:    $"   << subTotal + (subTotal * TAX_RATE) << "\n\n" << right;
}
