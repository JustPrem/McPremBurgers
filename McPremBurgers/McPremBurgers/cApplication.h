/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#pragma once
#include <iostream>
#include <string>
#include "ConsoleGUI/cGUI.h"
using namespace std;

struct Wallet;
class cOrder;

enum Screen
{
	Menu = 0,
	Ordering_SIZE = 1,
	Ordering_TOPPINGS = 2,
	Payment = 3,
	Credits = 4,
	PaymentConfirmation = 5,
	RecentOrders = 6,
};

enum BurgerSize
{
	Small = 0,
	Medium = 1,
	Large = 2,
};

class cApplication
{
public:

	/*  ---- Topping Prices: ----

		0 - Cheese
		1 - Salad
		2 - Bacon
		3 - Ketchup
		4 - Mayo
		5 - Extra Burger

		Prices are displayed in 100s, where 100 = 1cr.

	*/
	const int kSizePrices[3]
	{
		300,
		550,
		725
	};
	const int kToppingPrices[6]
	{
		80,
		50,
		100,
		30,
		30,
		150,
	};
	const string kToppingNames[6]
	{
		"Cheese",
		"Salad",
		"Bacon",
		"Ketchup",
		"Mayo",
		"Extra Burger"
	};
	const int kToppingAmount = 6;
	const int kMaxToppings = 5;

private:
	/* ------------ Main Variables ------------ */
	vector<cOrder*> vOrderHistory;				// All the recent orders.

	bool mIsRunning				= true;			// Determines whenever the program is running.
	cGUI* mGUI					= nullptr;		// The main Graphical User Interface.

	Wallet* mWallet				= nullptr;		// The Wallet, contains the users credits.
	cOrder* mCurrentOrder		= nullptr;		// The current order.
	string mCreditsDisplay		= "";			// String that show the amount of credits in a users account.
	string mPaymentScreen		= "";			// String that displays the screen on the Payment Screen.
	string mPaymentAmount		= "";			// String that shows the amount your burger costs, as well whether you can afford it.
	string mCreditsScreen		= "";			// String that displays the text for the Add Credits screen.
	string mCreditsReturn		= "";			// String used by the Return To Menu button on the credits screen.
	string mRecentOrdersText	= "";			// String used to display the current selected recent order.
	string mRecentOrderReorder	= "";			// String used by the re-order button, displays either "Re-Order" option or if no recent order allows you to jump to the order screen.
	string mRecentOrdersNavBut	= "";			// String used to display the text on the navigation button in the recent orders screen.
	int mRecentOrdersIndex		= 0;			// Index for displaying the correct recent order.

	string mToppingAmounts[6];					// The strings used by the toppings buttons.

public:

	bool mIsOrderProcessing = false;			// Whether the order has reached the processing stage, allows the program to return to the payment screen if extra credits were required.

	/* ------------ Base Functions ------------ */

	// Constructor.
	cApplication();

	// Deconstructor.s
	~cApplication();

private:
	/* ------------ Private Functions ------------ */

	// Setup the Screens.
	void ScreenSetup();

	// Recent Order text setup.
	void RecentOrderSetup();

public:
	/* ------------ Public Functions ------------ */

	// Begins the cApplication.
	void Start();

	// The main cApplication Loop.
	void Loop();

	// Ends the cApplication.
	void End();

	// Choose the size of the burger.
	void BurgerSize(int i);

	// Increase the amount of the specific toppings.
	void ChangeToppings(int Topping_Index, int Amount);

	// Get Order Total.
	int GetOrderTotal(int i);

	// Get Current Credits.
	int GetCurrentCredits();

	// Add Credits.
	void AddCredits();

	// Remove all Credits
	void WithdrawCredits();

	// Removes the current order.
	void ResetOrder();

	// Pay for Order.
	void PayForOrder();

	// Re-Order the most recent burger.
	void ReorderBurger();

	// Move Recent Orders Index.
	void MoveRecentOrderIndex(int i);
};

// This struct handles the processing of payments as well as outputting the current credits correctly.
struct Wallet
{
	// Amount of credits held in the wallet.
	int Credits = 0;
	
	// Add credits to account. (passed in as a float, for example 0.80 for 80 credits.
	void AddCredits(double i);
	
	// Remove credits from account.
	void RemoveCredits(int i);
	
	// Returns a string for displaying credits.
	string GetCredits_Display(int i);
};

// Order Class, contains all the Order information.
class cOrder
{
public:
	/* ------------ Main Variables ------------ */

	// Size of the burger.
	int mBurgerSize = 0;

	/*  ----List of Toppings:----
	
		0 - Cheese			= 0.80
		1 - Salad			= 0.50
		2 - Bacon			= 1.00
		3 - Ketchup			= 0.30
		4 - Mayo			= 0.30
		5 - Extra Burger	= 1.50
	*/
	// Amount of toppings on the burger.
	int mToppings[6] = { 0, 0, 0, 0, 0, 0 };

	// Get the orders burger size as a string.
	string GetBurgeSize();

	// Set this orders values to another ones.
	void SetOrderValues(cOrder* order, cApplication* app);
};

/* ------------ Buttons ------------ */

// Takes user to the Order Screen.
class cButton_OrderScreen : public cElement
{
private:
	cGUI* mGUI = nullptr;	// Pointer to the Main GUI class.

public:
	cButton_OrderScreen(string* Text, cGUI* GUI);

	void ElementFunction();	
	void ElementFunction(int i) {}
};

// Takes user to the Credits Screen.
class cButton_CreditsScreen : public cElement
{
private:
	cGUI* mGUI = nullptr;	// Pointer to the Main GUI class.

public:
	cButton_CreditsScreen(string* Text, cGUI* GUI);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Takes user to the Recent Orders Screen.
class cButton_RecentOrders  : public cElement
{
private:
	cGUI* mGUI = nullptr;	// Pointer to the Main GUI class.

public:
	cButton_RecentOrders(string* Text, cGUI* GUI);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Empty button for menu designing.
class cButton_Divider : public cElement
{
private:
	cGUI* mGUI = nullptr;	// Pointer to the Main GUI class.

public:
	cButton_Divider();

	void ElementFunction() {}
	void ElementFunction(int i) {}
};

/* Returns the user to the main menu
or payment screen if in the middle of an order. */
class cButton_ReturnMenu : public cElement
{
private:
	cGUI* mGUI = nullptr;			// Pointer to the Main GUI class.
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_ReturnMenu(string* Text, cGUI* GUI, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Sets the Burger size of the current order.
class cButton_BurgerSize : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.
	int mBurgerSize;				// Size of the burger for this option.

public:
	cButton_BurgerSize(string* Text, int Burger_Size, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Adds or removes specific topping.
class cButton_Topping : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.
	int mToppingIndex;				// The Index of the Specific Topping this refers to.

public:
	cButton_Topping(string* Text, int Topping_Index, cApplication* APP);

	void ElementFunction() {}
	void ElementFunction(int i);
};

// Takes the user to the payment screen.
class cButton_GoToPayment : public cElement
{
private:
	cGUI* mGUI = nullptr;	// Pointer to the Main GUI class.

public:
	cButton_GoToPayment(string* Text, cGUI* GUI);

	void ElementFunction();
	void ElementFunction(int i) {}
};

/* Allows the user to pay for the order, or takes 
them to the credits screen if they need more credits */
class cButton_PayForOrder : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_PayForOrder(string* Text, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Starts the process for adding more credits to the wallet.
class cButton_AddCredits : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_AddCredits(string* Text, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Used to navigate through recent orders.
class cButton_NavRecentOrders : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_NavRecentOrders(string* Text, cApplication* APP);

	void ElementFunction() {}
	void ElementFunction(int i);
};

// Re-order a burger from the burger history.
class cButton_ReorderBurger : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_ReorderBurger(string* Text, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};

// Withdraw all credits from the wallet.
class cButton_WithdrawCredits : public cElement
{
private:
	cApplication* mApp = nullptr;	// Pointer to the Main Application class.

public:
	cButton_WithdrawCredits(string* Text, cApplication* APP);

	void ElementFunction();
	void ElementFunction(int i) {}
};