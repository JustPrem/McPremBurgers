/* -------------------------------------------------- 
		
			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#include <iostream>
#include "cApplication.h"
using namespace std;

void main()
{
	// Create The Main Application Class.
	unique_ptr<cApplication> mApplication(new cApplication());

	// Begin the Application.
	mApplication->Start();
}