/* ------------------------ Description ------------------------
*
*			 		   - ConsoleGUI Library -
*			        - By Przemyslaw Kaniewski -
*				  - Created on 17th January 2023 -
*
*  This is a Standalone Library that allows the creation of
*  screen based GUI inside of the Console window using C++.
*
*  It Allows the creation of Buttons and navigation using arrow-keys.
*  This library has been designed to allow expansion based on
*  requirements presented upon the developer.
*
*  ------------------------------------------------------------- */

#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include "cScreen.h"
using namespace std;

class cGUI
{
private:
	/*	This enum contains the definition for the main navigational keybinds, feel free to add more if required.
	(These are returned from _getch() using the "conio.h" library when a key is pressed. */
	enum KEYS
	{
		Enter = 13,
		Backspace = 8,
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77
	};

	/* ------------ Variables ------------ */
	HANDLE hConsole;							// Handler for the Console Window.
	const int kRegularColor = 15; 				// This is the colour of the element when not selected. (Default = 15, White Text on Black Background)
	const int kSelectedColor = 240;				// This is the colour of the element when selected. (Default = 240, Black Text on White Background)

	int	mMenuIndex = 0;					// The Index of the current Menu system.	
	int	mScreenIndex = 0;					// The Index of the current screen.

	vector<cScreen*> vScreens;

public:
	/* ------------ Base Functions ------------ */
	cGUI();

	~cGUI();

private:
	/* ------------ Private Functions ------------ */

	// Get the Header Text of the specific screen.
	string GetHeaderText(int Screen_Index);

	// Get the Body Text of the specific screen.
	string GetBodyText(int Screen_Index);

	// Get the Footer Text of specific screen.
	string GetFooterText(int Screen_Index);

	// Move the menu Index.
	void MoveIndex(int i);

public:
	/* ------------ Public Functions ------------ */

	// Print the current screen.
	void Paint();

	// Controls the Inputs.
	void InputController();

	// Change the screen to the specific Index.
	void ChangeScreen(int Screen_Index);

	// Add a screen to the "vScreens" vector.
	void AddScreen(cScreen* Screen);

	// Add an element to the "vElements" vector in a specific screen.
	void AddElement(int Screen_Index, cElement* Element);

	// Set the Header text of a specific screen.
	void SetHeaderText(int Screen_Index, string* Header_Text);

	// Set the Body text of a specific screen.
	void SetBodyText(int Screen_Index, string* Body_Text);

	// Set the Footer text of a specific screen.
	void SetFooterText(int Screen_Index, string* Footer_Text);
};