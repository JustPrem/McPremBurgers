/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#pragma once
#include <iostream>
#include <vector>
#include "cElement.h"
using namespace std;

class cScreen
{
public:
	/* ------------ Variables ------------ */
	string* mHeaderText = nullptr;			// The text that is displayed in the header.
	string* mBodyText = nullptr;			// The text that is displayed in the main body.
	string* mFooterText = nullptr;			// The text that is displayed in the footer.

	vector<cElement*> vElements;				// Vector filled with all elements that get displayed.
	/* ------------ Base Functions ------------ */

	// Constructor.
	cScreen() {};

	// Deconstructor.
	~cScreen();
};