#include <iostream>
using namespace std;

// Struct containing details about specific movies.
struct Movie
{
	string mMovieName = "";
	int mMovieRating = 0;

	Movie(string Name) : mMovieName(Name) {};
};

void AskRating(Movie movie)
{
	int rating = 2;

	do
	{
		// Clear the screen.
		system("CLS");

		// Validation Check.
		if (cin.fail() || rating < 1 || rating > 4)
		{
			cout << "ERROR: Enter a Valid Number between 1 and 4" << endl;
			cin.clear();
			cin.ignore(80, '\n');
		}

		// Ask for user rating.
		cout << "How would you rate " << movie.mMovieName << " on a scale of 1 to 4?" << endl << endl;
		cout << "Rating: ";
		cin >> rating;

	} while (cin.fail() || rating < 1 || rating > 4);

	// Display correct response based on rating.
	switch (rating)
	{
		case 1: case 2:
		{
			cout << endl << "Chatbot: That sounds rubbish!" << endl << endl;
			system("pause");
			break;
		}
		case 3:
		{
			cout << endl << "Chatbot: Sounds like it was okay then!" << endl << endl;
			system("pause");
			break;
		}
		case 4:
		{
			cout << endl << "Chatbot: Sounds great!" << endl << endl;
			system("pause");
			break;
		}
	}
}

void main()
{
	// Amount of movies.
	const int kMoviesAmount = 3;

	// Movie Array.
	Movie mMovieArray[kMoviesAmount] =
	{ 
		Movie("Top Gun: Maverick"),
		Movie("Star Wars: The Last Jedi"),
		Movie("Minions: The Rise of Gru")
	};

	// Ask for a rating for each movie.
	for (int i = 0; i < kMoviesAmount; i++)
	{
		AskRating(mMovieArray[i]);
	}
}