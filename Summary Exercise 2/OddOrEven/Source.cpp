#include <iostream>
using namespace std;

void main()
{
	// Initialise Variables.
	int startNumber = 0;
	int endNumber = 0;
	int oddNumber = 0;

	// Get Starting Number.
	do
	{
		// Clear the Screen.
		system("CLS");

		// Check if failed.
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
		}

		// Ask for the initial number.
		cout << "Enter the Initial Number: ";
		cin >> startNumber;

	} while (cin.fail());

	// Get Last Number.
	do
	{
		// Clear the Screen.
		system("CLS");

		// Check if failed.
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
		}

		// Ask for the last number.
		cout << "Enter the last Number: ";
		cin >> endNumber;

	} while (cin.fail());

	// Check whether the user wants Odd or Even numbers.
	do
	{
		// Clear the Screen.
		system("CLS");

		// Check if failed.
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
		}

		// Ask for the initial number.
		cout << "Would you like Odd or Even Numbers?" << endl << endl << "  0 - Even Numbers\n  1 - Odd Numbers\n  Choice: ";
		cin >> oddNumber;

	} while (cin.fail() || (oddNumber != 0 && oddNumber != 1));

	system("CLS");

	// Print all values.
	for (int i = startNumber; i <= endNumber; i++)
	{
		if (i % 2 == oddNumber)
		{
			cout << i << endl;
		}
	}
}