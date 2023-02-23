/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#include "cGUI.h"

/* ------------ Base Functions ------------ */
cGUI::cGUI()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

cGUI::~cGUI()
{
	// Delete all the screen pointers from "vScreens".
	for (cScreen* screen : vScreens)
	{
		delete screen;
	}
}

/* ------------ Private Functions ------------ */

// Get the Header Text of the specific screen.
string cGUI::GetHeaderText(int Screen_Index)
{
	if (vScreens.at(Screen_Index)->mHeaderText != nullptr)
	{
		return *vScreens.at(Screen_Index)->mHeaderText;
	}

	return "";
}

// Get the Body Text of the specific screen.
string cGUI::GetBodyText(int Screen_Index)
{
	if (vScreens.at(Screen_Index)->mBodyText != nullptr)
	{
		return *vScreens.at(Screen_Index)->mBodyText;
	}

	return "";
}

// Get the Footer Text of specific screen.
string cGUI::GetFooterText(int Screen_Index)
{
	if (vScreens.at(Screen_Index)->mFooterText != nullptr)
	{
		return *vScreens.at(Screen_Index)->mFooterText;
	}

	return "";
}

// Move the menu Index.
void cGUI::MoveIndex(int i)
{
	if (i < 0)
	{
		if (mMenuIndex > 0)
		{
			mMenuIndex--;
		}
		else
		{
			mMenuIndex = (vScreens.at(mScreenIndex)->vElements.size() - 1);
		}
	}
	else if (i > 0)
	{
		if (mMenuIndex < (vScreens.at(mScreenIndex)->vElements.size() - 1))
		{
			mMenuIndex++;
		}
		else
		{
			mMenuIndex = 0;
		}
	}

	/*
	if (mMenuIndex > 0 && i < 0)
	{
		mMenuIndex--;
	}
	else if (mMenuIndex < (vScreens.at(mScreenIndex)->vElements.size() - 1) && i > 0)
	{
		mMenuIndex++;
	}
	*/
}

/* ------------ Public Functions ------------ */

// Print the current screen.
void cGUI::Paint()
{
	system("CLS");

	// Reset the colour of the console text.
	SetConsoleTextAttribute(hConsole, kRegularColor);

	// Render Header Text.
	if (GetHeaderText(mScreenIndex) != "")
	{
		cout << "------------------------------------------------------------" << endl;
		cout << GetHeaderText(mScreenIndex) << endl;
	}

	// Render Body Text.
	if (GetBodyText(mScreenIndex) != "")
	{
		cout << "------------------------------------------------------------" << endl << endl;
		cout << GetBodyText(mScreenIndex) << endl << endl;
		cout << "------------------------------------------------------------" << endl << endl;
	}

	// Print out all elements.
	if (vScreens.at(mScreenIndex)->vElements.size() > 0)
	{
		for (int i = 0; i < vScreens.at(mScreenIndex)->vElements.size(); i++)
		{
			// Reset the Colour of the console text.
			SetConsoleTextAttribute(hConsole, kRegularColor);

			// Print out a space before each option.
			cout << "     ";

			// Check if the forloop has reached the Index.
			if (i == mMenuIndex)
			{
				// Change the colour of the text to be highlighted.
				SetConsoleTextAttribute(hConsole, kSelectedColor);
			}
			else
			{
				// Change the colour of the text to be regular.
				SetConsoleTextAttribute(hConsole, kRegularColor);
			}

			// Print out the Element text at the specific Index.
			if (*vScreens.at(mScreenIndex)->vElements.at(i)->mDisplayText == "")
			{
				cout << endl;
			}
			else
			{
				string elementText = *vScreens.at(mScreenIndex)->vElements.at(i)->mDisplayText;
#
				// Check if the first symbol is < which indicates it's an incremental element.
				if (elementText[0] == '<')
				{
					cout << elementText << endl;
				}
				else
				{
					cout << " - " << elementText << endl;
				}
			}
				
		}
	}

	// Reset the colour of the console text.
	SetConsoleTextAttribute(hConsole, kRegularColor);

	// Render Footer Text.
	if (GetFooterText(mScreenIndex) != "")
	{
		cout << endl << "------------------------------------------------------------" << endl;
		cout << endl << GetFooterText(mScreenIndex) << endl;
	}
}

// Check the user input and perform specific actions.
void cGUI::InputController()
{
	int input = 0;

	switch (input = _getch())
	{
		case KEYS::Up:
		{
			MoveIndex(-1);
			break;
		}
		case KEYS::Down:
		{
			MoveIndex(1);
			break;
		}
		case KEYS::Enter:
		{
			vScreens.at(mScreenIndex)->vElements.at(mMenuIndex)->ElementFunction();
			break;
		}
		case KEYS::Right:
		{
			vScreens.at(mScreenIndex)->vElements.at(mMenuIndex)->ElementFunction(1);
			break;
		}
		case KEYS::Left:
		{
			vScreens.at(mScreenIndex)->vElements.at(mMenuIndex)->ElementFunction(-1);
			break;
		}
	}
}

// Change the screen to the specific Index.
void cGUI::ChangeScreen(int Screen_Index)
{
	// Check if the Screen Index is within bounds.
	if (Screen_Index >= 0 && Screen_Index < vScreens.size())
	{
		mScreenIndex = Screen_Index;
		mMenuIndex = 0;
	}
}

// Add a screen to the "vScreens" vector.
void cGUI::AddScreen(cScreen* Screen)
{
	vScreens.push_back(Screen);
}

// Add an element to the "vElements" vector in a specific screen.
void cGUI::AddElement(int Screen_Index, cElement* Element)
{
	// Check if the Screen Index is within bounds.
	if (Screen_Index >= 0 && Screen_Index < vScreens.size())
	{
		vScreens.at(Screen_Index)->vElements.push_back(Element);
	}
	else
	{
		delete Element;
	}
}

// Set the Header text of a specific screen.
void cGUI::SetHeaderText(int Screen_Index, string* Header_Text)
{
	vScreens.at(Screen_Index)->mHeaderText = Header_Text;
}

// Set the Body text of a specific screen.
void cGUI::SetBodyText(int Screen_Index, string* Body_Text)
{
	vScreens.at(Screen_Index)->mBodyText = Body_Text;
}

// Set the Footer text of a specific screen.
void cGUI::SetFooterText(int Screen_Index, string* Footer_Text)
{
	vScreens.at(Screen_Index)->mFooterText = Footer_Text;
}