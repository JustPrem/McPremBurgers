/* --------------------------------------------------

			McPrem Burger Ordering App.
		  Created By Przemyslaw Kaniewski
				Student ID: 20779943

---------------------------------------------------*/

#include "cApplication.h"

/* ------------ Base Functions ------------ */

// Constructor.
cApplication::cApplication() {};

cApplication::~cApplication()
{
	End();
}
/* ------------ Private Functions ------------ */

// Screens Setup.
void cApplication::ScreenSetup()
{
	// Set up the screens.
		// Screen 0 - Menu.

	cApplication* app = this;

	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::Menu, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::Menu, new string("    Welcome to the McPrem Burger App!\n\n    Please select an option to continue!"));
	mGUI->SetFooterText(Screen::Menu, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));

	mGUI->AddElement(Screen::Menu, new cButton_OrderScreen(new string("Order a Burger"), mGUI));
	mGUI->AddElement(Screen::Menu, new cButton_CreditsScreen(new string("Manage Credits"), mGUI));
	mGUI->AddElement(Screen::Menu, new cButton_RecentOrders(new string("Recent Orders"), mGUI));

	// Screen 1 - Ordering - Size.
	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::Ordering_SIZE, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::Ordering_SIZE, new string("    Please Select the Size of your Burger."));
	mGUI->SetFooterText(Screen::Ordering_SIZE, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));

	mGUI->AddElement(Screen::Ordering_SIZE, new cButton_BurgerSize(new string("Small Burger"), BurgerSize::Small, app));
	mGUI->AddElement(Screen::Ordering_SIZE, new cButton_BurgerSize(new string("Medium Burger"), BurgerSize::Medium, app));
	mGUI->AddElement(Screen::Ordering_SIZE, new cButton_BurgerSize(new string("Large Burger"), BurgerSize::Large, app));
	mGUI->AddElement(Screen::Ordering_SIZE, new cButton_Divider());
	mGUI->AddElement(Screen::Ordering_SIZE, new cButton_ReturnMenu(new string("Return To Menu"), mGUI, app));

	// Screen 2 - Ordering - Toppings.
	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::Ordering_TOPPINGS, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::Ordering_TOPPINGS, new string("    Choose which toppings you'd like!"));
	mGUI->SetFooterText(Screen::Ordering_TOPPINGS, new string("    Use the UP and DOWN arrow to navigate\n    Use the RIGHT and LEFT arrow to change your toppings amount.\n    Press Enter when you're ready "));

	for (int i = 0; i < kToppingAmount; i++)
	{
		mGUI->AddElement(Screen::Ordering_TOPPINGS, new cButton_Topping(&mToppingAmounts[i], i, app));
	}

	mGUI->AddElement(Screen::Ordering_TOPPINGS, new cButton_Divider());
	mGUI->AddElement(Screen::Ordering_TOPPINGS, new cButton_GoToPayment(new string("Continue To Payment"), mGUI));
	mGUI->AddElement(Screen::Ordering_TOPPINGS, new cButton_ReturnMenu(new string("Return to Menu"), mGUI, app));

	// Screen 3 - Payment.
	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::Payment, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::Payment, &mPaymentScreen);
	mGUI->SetFooterText(Screen::Payment, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));
	
	mGUI->AddElement(Screen::Payment, new cButton_PayForOrder(&mPaymentAmount, app));
	mGUI->AddElement(Screen::Payment, new cButton_ReturnMenu(new string("Return to Menu"), mGUI, app));

	// Screen 4 - Credits.
	mGUI->AddScreen(new cScreen());

	mGUI->SetBodyText(Screen::Credits, &mCreditsScreen);
	mGUI->SetFooterText(Screen::Credits, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));

	mGUI->AddElement(Screen::Credits, new cButton_AddCredits(new string("Add Credits"), app));
	mGUI->AddElement(Screen::Credits, new cButton_WithdrawCredits(new string("Withdraw All Credits"), app));
	mGUI->AddElement(Screen::Credits, new cButton_ReturnMenu(&mCreditsReturn, mGUI, app));

	// Screen 5 - Payment Confirmation.
	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::PaymentConfirmation, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::PaymentConfirmation, new string("    Thank you for your purchase!\n    You order can be viewed in the recent orders screen."));
	mGUI->SetFooterText(Screen::PaymentConfirmation, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));

	mGUI->AddElement(Screen::PaymentConfirmation, new cButton_ReturnMenu(new string("Return To Menu"), mGUI, app));

	// Screen 6 - Recent Orders.
	mGUI->AddScreen(new cScreen());

	mGUI->SetHeaderText(Screen::RecentOrders, &mCreditsDisplay);
	mGUI->SetBodyText(Screen::RecentOrders, &mRecentOrdersText);
	mGUI->SetFooterText(Screen::RecentOrders, new string("    Use the UP and DOWN arrow to navigate\n    Press RETURN to confirm your choice!"));

	mGUI->AddElement(Screen::RecentOrders, new cButton_NavRecentOrders(&mRecentOrdersNavBut, app));
	mGUI->AddElement(Screen::RecentOrders, new cButton_Divider());

	mGUI->AddElement(Screen::RecentOrders, new cButton_ReorderBurger(&mRecentOrderReorder, app));
	mGUI->AddElement(Screen::RecentOrders, new cButton_ReturnMenu(new string("Return To Menu"), mGUI, app));

}

// Recent Order text setup.
void cApplication::RecentOrderSetup()
{
	// Initialise local variables.
	bool hasToppings = false;			// Used to write "Toppings" label if burger has toppings.

	// Setup the Recent Order Text of the currently selected order.
	mRecentOrdersText =
		"    Burger Cost: " + mWallet->GetCredits_Display(GetOrderTotal(mRecentOrdersIndex)) + "\n\n" +
		"    Burger Size: " + vOrderHistory.at(mRecentOrdersIndex)->GetBurgeSize() + "\n\n";

	// Go through all possible toppings.
	for (int i = 0; i < kToppingAmount; i++)
	{
		// Check if the specific topping has been added.
		if (vOrderHistory.at(mRecentOrdersIndex)->mToppings[i] > 0)
		{
			// Add toppings label.
			if (!hasToppings)
			{
				mRecentOrdersText += "    ---- Toppings ---- \n";
				hasToppings = true;
			}

			// Add topping to the recent order text.
			mRecentOrdersText += "    " + kToppingNames[i] + ": " + to_string(vOrderHistory.at(mRecentOrdersIndex)->mToppings[i]) + "\n";
		}
	}
}

/* ------------ Public Functions ------------ */

// Begins the cApplication.
void cApplication::Start()
{
	// Create the GUI.
	mGUI = new cGUI();

	// Create the wallet.
	mWallet = new Wallet();

	// Setup the screens.
	ScreenSetup();	

	// Start the loop.
	mIsRunning = true;
	Loop();
}

// The Main cApplication Loop.
void cApplication::Loop()
{
	while (mIsRunning)
	{
		// Get the Current Amount of Credits to display.
		mCreditsDisplay = "    Credits: " + mWallet->GetCredits_Display(mWallet->Credits);

		// Check if an order exists.
		if (mCurrentOrder != nullptr)
		{
			// Setup the Topping displays.
			for (int i = 0; i < kToppingAmount; i++)
			{
				mToppingAmounts[i] = "< [" + kToppingNames[i] + ": " + to_string(mCurrentOrder->mToppings[i]) + "] >";
			}

			// Check if the user has enough credits to make a purchase.
			if (mWallet->Credits >= GetOrderTotal(-1))
			{
				// User has enough credits, display message.
				mPaymentScreen = "    Your total for the order is: " + mWallet->GetCredits_Display(GetOrderTotal(-1)) + "\n    You have enough credits to make the purchase.";
				mPaymentAmount = "Confirm Payment";
			}
			else
			{
				// User lacks credits, ask the user to add more.
				mPaymentScreen = "    Your total for the order is: " + mWallet->GetCredits_Display(GetOrderTotal(-1)) + "\n\n    You don't have enough credits for this order\n    please add more below.";
				mPaymentAmount = "Add More Credits";
			}
		}

		// Set up the Recent orders screen text.
			// Check if there are any recent orders.
		if (vOrderHistory.size() > 0)
		{
			// Recent orders exist, show correct values.
			RecentOrderSetup();
			mRecentOrdersNavBut = "< [Order: " + to_string(mRecentOrdersIndex + 1) + " / " + to_string(vOrderHistory.size()) + "] >";
			mRecentOrderReorder = "Re-order Selected Burger";
		}
		else
		{
			// No Recent Orders available, show default values.
			mRecentOrdersText = "    There are no recent orders to display.\n\n    Please make a start a new order in the main menu.";
			mRecentOrdersNavBut = "< [Order: 0 / 0] >";
			mRecentOrderReorder = "Order a burger";
		}
		

		// Setup the Credits Screen Text.
		mCreditsScreen = "    You currently have: " + mWallet->GetCredits_Display(mWallet->Credits) + "\n\n    Would you like to add more credits or withdraw your current ones?";

		// Check if the user was in the middle of ordering when they went to add more credits.
		if (mIsOrderProcessing)
		{
			// Change button text to show they'll return to payment screen.
			mCreditsReturn = "Return To Payment";
		}
		else
		{
			// Change button text to show they'll return to main menu.
			mCreditsReturn = "Return To Menu";
		}

		// Draw the Screen.
		mGUI->Paint();

		// Manage the Input.
		mGUI->InputController();
	}
}

// Ends the cApplication.
void cApplication::End()
{
	// Clean up Pointers.
	delete mGUI;

	delete mWallet;

	delete mCurrentOrder;
}

// Choose the size of the burger.
void cApplication::BurgerSize(int i)
{
	// Remove mCurrentOrder if it already exists, to avoid memory leaks.
	if (mCurrentOrder != nullptr)
	{
		delete mCurrentOrder;
	}

	// Create a new order.
	mCurrentOrder = new cOrder();

	// Set the burger size.
	mCurrentOrder->mBurgerSize = i;

	// Change the screen to the topping selection screen.
	mGUI->ChangeScreen(Screen::Ordering_TOPPINGS);
}

// Increase the amount of the specific toppings.
void cApplication::ChangeToppings(int Topping_Index, int Amount)
{
	// Check whether the user is trying to add or remove toppings.
	if (mCurrentOrder->mToppings[Topping_Index] > 0 && Amount < 0)
	{
		// The user is trying to remove toppings, and has more than 1. Thus removing a topping.
		mCurrentOrder->mToppings[Topping_Index] += Amount;
	}
	else if (Amount > 0 && mCurrentOrder->mToppings[Topping_Index] < kMaxToppings)
	{
		// The user is adding a topping, and hasn't reached the limit. Thus adding a topping.
		mCurrentOrder->mToppings[Topping_Index] += Amount;
	}
	
}

// Get Order Total. -1 is current order, 0 onwards are recent orders.
int cApplication::GetOrderTotal(int i)
{
	// Amount.
	int amount = 0;				// The total cost.
	cOrder* order = nullptr;	// Order to count total from.

	// Get the Corrent Burger based on the "i" parameter.
	if (i == -1)
	{
		order = mCurrentOrder;
	}
	else if (i >= 0)
	{
		order = vOrderHistory.at(i);
	}
	else // In case of requesting -1 and no current order existing.
	{
		return 0;
	}
	
	if (order != nullptr)
	{
		// Add the cost of the burger based on it's size.
		amount += kSizePrices[order->mBurgerSize];

		// Add the prices of all the toppings.
		for (int i = 0; i < kToppingAmount; i++)
		{
			amount += (kToppingPrices[i] * order->mToppings[i]);
		}
	}
	else
	{
		return 0;
	}
	

	return amount;
}

// Get Current Credits.
int cApplication::GetCurrentCredits()
{
	return mWallet->Credits;
}

// Add Credits.
void cApplication::AddCredits()
{
	// Amount inserted by user.
	double amount = 0;

	// Validation Loop for adding Credits.
	do
	{
		// Clear the screen.
		system("CLS");

		// Check if wrong input.
		if (cin.fail() || amount < 0)
		{
			cout << endl << "    Error, please insert a valid number (Anything above 0)" << endl;
			cin.clear();
			cin.ignore(80, '\n');
		}

		// Ask how many credits and get input from user.
		cout << endl << "    How many credits would you like to add?" << endl << endl;
		cout << "    Credits To Add: ";
		cin >> amount;

	} while (amount < 0 || cin.fail());

	// Add Credits to the wallet.
	mWallet->AddCredits(amount);
}

// Remove all Credits
void cApplication::WithdrawCredits()
{
	mWallet->RemoveCredits(mWallet->Credits);
}

// Removes the current order.
void cApplication::ResetOrder()
{
	// Make sure the variable is set to nullptr.
	mCurrentOrder = nullptr;
}

// Pay for Order.
void cApplication::PayForOrder()
{
	// Check if order exists.
	if (mCurrentOrder != nullptr)
	{
		// Check whether the user has enough credits.
		if (mWallet->Credits >= GetOrderTotal(-1))
		{// The user has enough credits.
			mIsOrderProcessing = false;							// The order is not being processed.
			mWallet->Credits -= GetOrderTotal(-1);				// Remove credits from users wallet.
			vOrderHistory.push_back(mCurrentOrder);				// Add order to recent orders.
			mGUI->ChangeScreen(Screen::PaymentConfirmation);	// Transfer user to the payment confirmation screen.
		}
		else
		{// User doesn't have enough credits.
			mIsOrderProcessing = true;				// Order is still being processed.
			mGUI->ChangeScreen(Screen::Credits);	// Take user to the credits screen to add more credits.
		}
	}
}

// Re-Order burger.
void cApplication::ReorderBurger()
{
	// Check if there are burgers to reorder.
	if (vOrderHistory.size() > 0)
	{
		// Create a new order and set the values to the specific orders.
		mCurrentOrder = new cOrder();
		mCurrentOrder->SetOrderValues(vOrderHistory.at(mRecentOrdersIndex), this);
		
		// Set the Index to the start of the order history.
		mRecentOrdersIndex = 0;

		// Go to the payment screen.
		mGUI->ChangeScreen(Screen::Payment);
	}
	else // No burgers available, start new order.
	{
		mGUI->ChangeScreen(Screen::Ordering_SIZE);
	}
}

// Move Recent Orders Index.
void cApplication::MoveRecentOrderIndex(int i)
{
	// Check if the user is moving down or up the vector.
	if (i < 0)
	{
		// User is moving down, check if reached bottom of the vector.
		if (mRecentOrdersIndex > 0)
		{
			// User hasn't reached the bottom of the vector, moving them down 1 position.
			mRecentOrdersIndex--;
		}
		else
		{
			// User has reached the bottom of the vector, check if there's at least 1 item in the vector.
			if (vOrderHistory.size() > 0)
			{
				// Place the Index at the end of the vector. (Size - 1, since first position is 0)
				mRecentOrdersIndex = vOrderHistory.size() - 1;
			}
		}
	}
	else
	{
		// User is moving up, check if reached the end of the vector.
		if (mRecentOrdersIndex < (vOrderHistory.size() - 1))
		{
			// User hasn't reached the end, move the index up.
			mRecentOrdersIndex++;
		}
		else
		{
			// User reached the end, move the index to the bottom.
			mRecentOrdersIndex = 0;
		}
	}
}

/* ------------ Wallet Functions ------------ */

// Add credits to account. (passed in as a float, for example 0.80 for 80 credits.
void Wallet::AddCredits(double i)
{
	int amount = (i * 100);
	Credits += amount;
}

// Remove credits from account.
void Wallet::RemoveCredits(int i)
{
	Credits -= i;
}

// Returns a string for displaying credits.
string Wallet::GetCredits_Display(int i)
{
	int decimalCreds = 0;
	int wholeCreds = 0;

	// Get whole credits and decimal credits.
	if (i > 0)
	{
		decimalCreds = i % 100;
		wholeCreds = (i - decimalCreds) / 100;
	}

	//  Get the Correct Display.
	if (decimalCreds == 0)
	{
		return to_string(wholeCreds) + " cr";
	}
	else
	{
		if (decimalCreds < 10)
		{
			return to_string(wholeCreds) + ".0" + to_string(decimalCreds) + " cr";
		}
		else
		{
			return to_string(wholeCreds) + "." + to_string(decimalCreds) + " cr";
		}
	}

}

/* ------------ Order Functions ------------ */

// Get the orders burger size as a string.
string cOrder::GetBurgeSize()
{
	switch (mBurgerSize)
	{
		case 0:
		{
			return "Small";
		}
		case 1:
		{
			return "Medium";
		}
		case 2:
		{
			return "Large";
		}
		default:
		{
			return "ERROR - No/Wrong Size";
		}
	}
}

// Set this orders values to another ones.
void cOrder::SetOrderValues(cOrder* order, cApplication* app)
{
	// Set the burger size.
	mBurgerSize = order->mBurgerSize;

	// Set all toppings.
	for (int i = 0; i < app->kToppingAmount; i++)
	{
		mToppings[i] = order->mToppings[i];
	}
}

/* ------------ Button Functions ------------ */

// Constructor.
cButton_OrderScreen::cButton_OrderScreen(string* Text, cGUI* GUI)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mGUI = GUI;
}

// Take user to the order screen.
void cButton_OrderScreen::ElementFunction()
{
	mGUI->ChangeScreen(Screen::Ordering_SIZE);
}

// Constructor.
cButton_CreditsScreen::cButton_CreditsScreen(string* Text, cGUI* GUI)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mGUI = GUI;
}

// Take user to the credits screen,
void cButton_CreditsScreen::ElementFunction()
{
	mGUI->ChangeScreen(Screen::Credits);
}

// Constructor.
cButton_RecentOrders::cButton_RecentOrders(string* Text, cGUI* GUI)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mGUI = GUI;
}

// Take user to the Recent Orders screen.
void cButton_RecentOrders::ElementFunction()
{
	mGUI->ChangeScreen(Screen::RecentOrders);
}

// Constructor.
cButton_Divider::cButton_Divider()
{
	mDisplayText = new string("");
	mIsIncremental = false;
}

// Constructor.
cButton_ReturnMenu::cButton_ReturnMenu(string* Text, cGUI* GUI, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mGUI = GUI;
	mApp = APP;
}

// Returns the user to the main menu or the payment screen if in the middle of an order.
void cButton_ReturnMenu::ElementFunction()
{
	if (mApp->mIsOrderProcessing)
	{
		mGUI->ChangeScreen(Screen::Payment);
		return;
	}

	mApp->ResetOrder();
	mGUI->ChangeScreen(Screen::Menu);
}

// Constructor.
cButton_BurgerSize::cButton_BurgerSize(string* Text, int Burger_Size, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mBurgerSize = Burger_Size;
	mApp = APP;
}

// Set the Burger Size of the current order.
void cButton_BurgerSize::ElementFunction()
{
	mApp->BurgerSize(mBurgerSize);
}

// Constructor.
cButton_Topping::cButton_Topping(string* Text, int Topping_Index, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = true;
	mToppingIndex = Topping_Index;
	mApp = APP;
}

// Adds or removes specific topping.
void cButton_Topping::ElementFunction(int i)
{
	mApp->ChangeToppings(mToppingIndex, i);
}

// Constructor.
cButton_GoToPayment::cButton_GoToPayment(string* Text, cGUI* GUI)
{
	mDisplayText = Text;
	mIsIncremental = true;
	mGUI = GUI;
}

// Take the user to the payment screen.
void cButton_GoToPayment::ElementFunction()
{
	mGUI->ChangeScreen(Screen::Payment);
}

// Constructor.
cButton_PayForOrder::cButton_PayForOrder(string* Text, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mApp = APP;
}

// Allows the user to pay for the order, or takes them to the credits screen if they need more credits
void cButton_PayForOrder::ElementFunction()
{
	mApp->PayForOrder();
}

// Constructor.
cButton_AddCredits::cButton_AddCredits(string* Text, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mApp = APP;
}

// Starts the process for adding more credits to the wallet.
void cButton_AddCredits::ElementFunction()
{
	mApp->AddCredits();
}

// Constructor.
cButton_NavRecentOrders::cButton_NavRecentOrders(string* Text, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = true;
	mApp = APP;
}

// Used to navigate through recent orders.
void cButton_NavRecentOrders::ElementFunction(int i)
{
	mApp->MoveRecentOrderIndex(i);
}

// Constructor.
cButton_ReorderBurger::cButton_ReorderBurger(string* Text, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mApp = APP;
}

// Re-order a burger from the burger history.
void cButton_ReorderBurger::ElementFunction()
{
	mApp->ReorderBurger();
}

// Constructor.
cButton_WithdrawCredits::cButton_WithdrawCredits(string* Text, cApplication* APP)
{
	mDisplayText = Text;
	mIsIncremental = false;
	mApp = APP;
}

// Withdraw all credits from the wallet.
void cButton_WithdrawCredits::ElementFunction()
{
	mApp->WithdrawCredits();
}