/******************************************************************************
* AUTHOR        : Jesus Sanchez
* STUDENT ID    : 1024834
* ASSIGNMENT #3 : Pointers
* CLASS         : CS1C
* SECTION       : MW: 1:30pm
* DUE DATE      : 02/15/2017
* ****************************************************************************/

#include "Equipment.h"

/******************************************************************************
 * EMPLOYEE - INHERITANCE
 * ----------------------------------------------------------------------------
 * This program will read in a list of inventory from a text file and store the
 * data in an array of Equipment class objects and display the inventory for
 * the customer. The customer will be prompted to enter the number of unique items they
 * will purchase and that number will be used to set the size of the dynamic
 * array holding the items and quantity of those items that the customer wants to
 * purchase. Once the customer has entered all of the items and quantities they
 * would like to purchase, their receipt will be printed and the final inventory
 * after their purchase will be displayed.
 * ----------------------------------------------------------------------------
 * INPUT:
 *    numItems    - Number of unique items to be purchased (size of dynamic array)
 *    searchEquip  - Name of item to be purchased
 *    purchaseAmt - Amount of items of that kind to be purchased
 *
 * OUTPUT:
 *    inventory     - All Equipment class data members
 *    customerOrder - Dynamic array of Equipment type; items and quantities
 *    				  customer wishes to purchase
 *****************************************************************************/

void PrintHeader(string labName, char labType, int labNum);

int main()
{
	Equipment test;                 // Equipment object used to call class functions
	Equipment inventory[MAX_ITEMS]; // Array of Equipment class objects

	Equipment *customerOrder; // Dynamic array holding customer's order
	int *numItems;            // Points to new integer created when customer
							  // enters amount of unique items to be purchased

	string searchEquip;  // Item customer wishes to purchase
	int    purchaseAmt;  // Quantity of desired item to be purchased

	// Prints assignment header.
	PrintHeader("Pointers", 'A', 3);

	// Initializes the items in the inventory with their costs and quantities.
	test.InitializeInventory(inventory);

	// Prints the initial inventory before the customer makes their purchases.
	cout << setw(36) << "----- Initial Inventory -----" << endl;
	test.PrintInventory(inventory);

	// Prompts the customer for the size of the dynamic array.
	cout << "How many unique items will you be purchasing? ";
	numItems = new int;
	cin  >> *numItems;
	cin.ignore(1000, '\n');

	// Creates the dynamic array with the specified array size.
	customerOrder = new Equipment[*numItems];

	// Prompts the customer to enter the name of the item they would like to
	// purchase and the quantity they would like to purchase until they enter
	// the same number of items as the array size.
	for(int index = 0; index < *numItems; index++)
	{
		// Ensures that the item entered by the customer is the name of an item
		// in the inventory.
		do
		{
			cout << "\nEnter the name of the item #" << index + 1 << ": ";
			getline(cin, searchEquip);

			if(!test.FindItem(searchEquip, inventory))
			{
				cout << "\nItem not found - Enter a valid item name.\n\n";
			}
		}while(!test.FindItem(searchEquip, inventory));

		// Puts the name of the item to be purchased and its cost in the dynamic array.
		test.SetName(searchEquip, customerOrder, index);
		test.SetCost(searchEquip, inventory, customerOrder, index);

		// Prompts the customer for how many of that item they want to purchase.
		cout << "Enter the quantity to be purchased: ";
		cin  >> purchaseAmt;
		cin.ignore(1000, '\n');

		// Sets the quantity to be purchased in the dynamic array.
		test.SetQuantity(purchaseAmt, customerOrder, index);

		// Updates the quantity of the chosen item in the inventory.
		test.UpdateQuantity(purchaseAmt, searchEquip, inventory);
	}

	// Prints the customers receipt.
	test.PrintReceipt(customerOrder, numItems);

	// Deletes the pointers used for the dynamic array and size to free up memory.
	delete [] customerOrder;
	delete numItems;

	// Prints the final inventory after the customer has made their purchases.
	cout << right << setw(35) << "----- Final inventory -----" << endl;
	test.PrintInventory(inventory);

	return 0;
}

/******************************************************************************
 * PrintHeader
 * ----------------------------------------------------------------------------
 * This function prints the project header.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS:
 *     labName - Lab Name has to be preciously defined
 *     labType -  Lab Type has to be preciously defined
 *     labNum  - Lab Number has to be preciously defined
 *
 * POST-CONDITIONS:
 *     This function will print the class heading.
 *****************************************************************************/
void PrintHeader(string labName, char labType, int labNum)
{
	cout << left;
	cout << "*******************************************\n";
	cout << "* PROGRAMMED BY  : Jesus Sanchez";
	cout << "\n* " << setw(15) << "STUDENT ID" << ": 1024834" ;
	cout << "\n* " << setw(15) << "CLASS" << ": MW: 1:30pm - 2:50pm";
	cout << "\n* ";

	if(toupper(labType) == 'L')
	{
		cout << "LAB #" << setw(9);
	}
	else
	{
		cout << "ASSIGNMENT #" << setw(2);
	}

	cout << labNum << " : " << labName;
	cout << "\n*******************************************\n\n";
	cout << right;
}
