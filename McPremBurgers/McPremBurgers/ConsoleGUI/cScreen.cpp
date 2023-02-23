/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#include "cScreen.h"

/* ------------ Base Functions ------------ */

// Deconstructor.
cScreen::~cScreen()
{
	// Delete all elements.
	for (cElement* element : vElements)
	{
		delete element;
	}
}