/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#pragma once
#include <iostream>
using namespace std;

/*
	This is a Purely Virtual Class that handles menu elements such
	as buttons.

	This class should be added onto.
*/
class cElement
{
protected:
	/* ------------ Variables ------------ */
	bool mIsIncremental = false;		// Whether this element uses ElementFunction or it's overload.

public:
	string* mDisplayText;				// The Text that will be displayed.
	/* ------------ Public Methods ------------ */

	~cElement();

	// The main function of this "cElement"
	virtual void ElementFunction()		= 0;
	virtual void ElementFunction(int i) = 0;
};