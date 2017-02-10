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
 * This function reads in the name, cost, and quantity of an item from a text
 * file and stores it in the specified index of the inventory array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     inventory  - Array of items in the inventory is not previously defined.
 *
 * POST-CONDITIONS:
 *     Initializes the inventory array with names, costs, and quantities of
 *     the items.
 *****************************************************************************/
void Equipment::InitializeInventory(Equipment inventory[])
{
	ifstream fin;

	int index = 0;

	fin.open("Inventory.txt");

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
 * FindItem
 * ----------------------------------------------------------------------------
 * This function searches ensures that the user entered a valid item name by
 * comparing the name entered to the names of the items in the inventory
 * array - returns true if the entered name matches a name in the array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     searchItem - Name of Item to be searched for must be previously defined.
 *     inventory  - Array of items in the inventory must be previously defined.
 *
 * POST-CONDITIONS:
 *     Returns true if item name entered matches a name in the array.
 *****************************************************************************/
bool Equipment::FindItem(string searchItem, Equipment inventory[])
{
	bool found = false;
	int  index = 0;

	// Searches for the name entered by comparing it to the names in the
	// inventory.
	while(!found && index < MAX_ITEMS)
	{
		// Assigns true to found and exits the loop if the names match, else
		// increments the index and checks the remaining items in the array.
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
 * This function sets the name of the item to be purchased in the specified
 * index of the customerOrder array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     equipName     - Name of item must be previously defined.
 *     customerOrder - Array of items to be purchased is not previously defined.
 *     index         - Index of array where name is to be stored must be
 *     				   previously defined.
 *
 * POST-CONDITIONS:
 *     Sets the name of item to be purchased in the indicated index of array.
 *****************************************************************************/
void Equipment::SetName(string equipName, Equipment customerOrder[], int index)
{
	customerOrder[index].name = equipName;
}

/******************************************************************************
 * SetCost
 * ----------------------------------------------------------------------------
 * This function sets the cost of the item to be purchased by finding the name
 * of the item in the inventory and assigning the cost of that item to the cost
 * in the index of the customerOrder array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     equipName     - Name of item must be previously defined.
 *     inventory     - Array of items in inventory is not previously defined.
 *     customerOrder - Array of items to be purchased is not previously defined.
 *     index         - Index of array where cost is to be stored must be
 *     				   previously defined.
 *
 * POST-CONDITIONS:
 *     Sets the cost of item to be purchased in the indicated index of array.
 *****************************************************************************/
void Equipment::SetCost(string equipName, Equipment inventory[], Equipment customerOrder[], int index)
{
	int index2 = 0; // Index used to search inventory from the beginning

	while(equipName != inventory[index2].name)
	{
		index2++;
	}

	customerOrder[index].cost = inventory[index2].cost;
}

/******************************************************************************
 * SetName
 * ----------------------------------------------------------------------------
 * This function sets the quantity to be purchased of the item in the specified
 * index of the customerOrder array.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     numPurchased  - Quantity of item purchased must be previously defined.
 *     customerOrder - Array of items to be purchased is not previously defined.
 *     index         - Index of array where quantity is to be stored must be
 *     				   previously defined.
 *
 * POST-CONDITIONS:
 *     Sets the name of item to be purchased in the indicated index of array.
 *****************************************************************************/
void Equipment::SetQuantity(int numPurchased, Equipment customerOrder[], int index)
{
	customerOrder[index].quantity = numPurchased;
}

/******************************************************************************
 * UpdateQuantity
 * ----------------------------------------------------------------------------
 * This function updates the quantity of an item that is available in the main 
 * inventory once the user has entered the quantity they would like to purchase.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     numPurchased - Quantity of item purchased must be previously defined.
 *     searchItem   - Name of items to be purchased must be previously defined.
 *     inventory    - Array holding the quantities of each item available must
 *                    be previously defined.
 *
 * POST-CONDITIONS:
 *     Updates the quantity of an item that is available in the main inventory.
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

	inventory[index].quantity -= numPurchased;
}

void Equipment::PrintReceipt(Equipment customerOrder[], int *&numItems)
{
	float subTotal = 0.0;

	cout << setw(27) << endl << "----- RECEIPT -----" << endl << endl;

	cout << fixed << setprecision(2) << left
		 << setw(QTY) << "QTY" << setw(NAME) << "ITEM" << setw(1) << " " << setw(COST) << "COST" << endl
		 << setw(QTY) << "---" << setw(NAME) << "----" << setw(1) << "-" << setw(COST) << "-----" << endl;

	for(int index = 0; index < *numItems; index++)
	{
		cout << setw(QTY)  << customerOrder[index].quantity
			 << setw(NAME) << left  << customerOrder[index].name << setw(1) << "$"
			 << setw(COST) << customerOrder[index].cost << endl;

		subTotal += (customerOrder[index].cost * customerOrder[index].quantity);
	}

	cout << "\nSUBTOTAL: $" << subTotal  << endl
		 << "TAX:      $"   << (subTotal * TAX_RATE) << endl
		 << "TOTAL:    $"   << subTotal + (subTotal * TAX_RATE) << endl << endl << right;
}

void Equipment::PrintInventory(Equipment inventory[])
{
	cout << left
		 << setw(NAME) << "Name of Equipment" << setw(1) << " " << setw(COST) << "Cost"
		 << setw(QUANTITY) << "Quantity" << endl;

	cout << setw(NAME) << "-----------------" << setw(1) << "-" << setw(COST) << "------"
		 << setw(QUANTITY) << "--------" << endl;

	for(int index = 0; index < MAX_ITEMS; index++)
	{
		cout << setw(NAME) << inventory[index].name << setw(1) << "$" << setw(COST) << inventory[index].cost
			 << right << setw(QUANTITY - 3) << inventory[index].quantity << left << endl;
	}

	cout << endl << right;
}
