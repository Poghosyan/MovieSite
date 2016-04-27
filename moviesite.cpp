#include "lib/map.h"
#include "lib/set.h"
#include "user.h"
#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

enum menuNavCommand {MAIN, LOGGEDIN, DISPLAY, QUEUE, EXIT};

void getUserRecords (const std::string & fileName, Map <std::string, User*> &);
void getMovieRecords (const std::string & fileName, Map <std::string, Movie*> &);
void mapMovieToKeyword (Map <std::string, Movie*> &, Map <std::string, Set <Movie*>*> &);
void displayLogin ();
void displayCommands ();
int getInput ();
menuNavCommand MainMenu (Map <std::string, User*> *, Map <std::string, Movie*> *, Map <std::string, Set <Movie*>*> *, User * curr);
menuNavCommand LoggedInMenu (Map <std::string, Movie*> *, Map <std::string, Set <Movie*>*> *, User * curr);
void ViewingMovMenu (Set <Movie*>* &, User * curr);
void displayMovie (Movie * mov);

int main (int argc, char * argv[]) {
	bool stop = true;
	//menuNavCommand instr = menuNavCommand::MAIN;
	std::string nextStep("MainMenu");
	std::string userFile, mediaFile;
	User * current = nullptr;
	Map <std::string, User*> users;
	Map <std::string, Movie*> movies;
	Map <std::string, Set <Movie*>*> keywordIndex;
	if (argc <= 1) {
		std::cout << "Didn't specify file, exiting program" << std::endl;
		return 0;
	}

	std::ifstream file (argv[ argc - 1 ]);
	if (file.is_open ()) {
		std::getline (file, userFile);
		std::getline (file, mediaFile);
		file.close();
	}

	getUserRecords (userFile, users);
	getMovieRecords (mediaFile, movies);
	mapMovieToKeyword (movies, keywordIndex);

	while (stop) {
		stop = MainMenu (&users, &movies, &keywordIndex, current);
	}
	//Add new users here.
	std::ofstream outfile (userFile.c_str());
	if (outfile.is_open ()) {

	}
	outfile.close();
}


void getUserRecords (const std::string & fileName, Map <std::string, User*> & container) {
	User* user;
	std::string line, id, name;
	std::ifstream file (fileName.c_str ());
	if (file.is_open ()) {
		while (std::getline (file, line)) {
			std::istringstream iss(line);
			iss >> line;
			if (line == "BEGIN") {
				iss.get();
				std::getline (iss, line);
				id = line;
			}		
			else if (line == "NAME:") {
				iss.get();
				std::getline (iss, line);
				name = line;
				user = new User (id, name);
			}
			else if (line == "END") {
				container.add (id, user);
				container.get(id);
			}
		}
	}
	file.close ();	
}

void getMovieRecords (const std::string & fileName, Map <std::string, Movie*> & container) {
	Movie* movie;
	std::string line, title, keyword;
	std::ifstream file (fileName.c_str ());
	if (file.is_open ()) {
		while (std::getline (file, line)) {
			std::istringstream iss(line);
			iss >> line;
			if (line == "BEGIN") {
				iss.get();
				std::getline (iss, line);
				title = line;
				movie = new Movie(title);
			}		
			else if (line == "KEYWORD:") {
				iss.get();
				std::getline (iss, line);
				keyword = line;
				movie->addKeyword(keyword);
			}
			else if (line == "END")
				container.add(title, movie);
		}
	}	
	file.close ();
}

void mapMovieToKeyword (Map <std::string, Movie*> & movies, Map <std::string, Set <Movie*>*> & keyMap) {
	Movie * curr;
	Set <std::string> currKeywords;
	Set <Movie*>* currMovieSet;

	for (Map <std::string, Movie*>::Iterator it = movies.begin(); it != movies.end(); ++it) {
		curr = (*it).second;
		currKeywords = curr->getAllKeywords ();
		for (Set<std::string>::Iterator iter = currKeywords.begin(); iter != currKeywords.end(); ++iter) {
			try {
				currMovieSet = keyMap.get(*iter);
				currMovieSet->add(curr);
			} catch (NoSuchElementException & e) {
				currMovieSet = new Set <Movie*>();
				currMovieSet->add(curr);
				keyMap.add(*iter, currMovieSet);
			}
		}
	}
}

void displayLogin () {
	std::cout << "1. Log In" << std::endl;
	std::cout << "2. Create a new user" << std::endl;
	std::cout << "3. Quit" << std::endl;
}

void displayCommands () {
	std::cout << "1. Search for a movie by title" << std::endl;
	std::cout << "2. Search for a movie by keyword" << std::endl;
	std::cout << "3. Return current movie" << std::endl;
	std::cout << "4. View Queue" << std::endl;
	std::cout << "5. Logout" << std::endl;
}

int getInput () {
	int input = 0;
	std::cin.exceptions (std::ios::failbit);
	try {
		std::cin >> input;
		std::cin.ignore();
	}
	catch (std::ios::failure & e) {
		std::cin.clear ();
		std::cin.ignore (std::numeric_limits<int>::max(), '\n');
		return 0;
	}
	return input;
}

menuNavCommand MainMenu (Map <std::string, User*> *users, Map <std::string, Movie*> *movies, Map <std::string, Set <Movie*>*> *keywordIndex, User * curr) {
	int input;
	std::string id, name;
	User *newUser;

	displayLogin ();
	input = getInput ();

	switch (input) {
		case 1:
			std::cout << "Please enter User ID" << std::endl;
			std::getline (std::cin, id);

			try { curr = users->get(id); }
			catch (NoSuchElementException & e) { 
				std::cout << "No user with that user ID exists" << std::endl;
				return menuNavCommand::MAIN;
			}
			return menuNavCommand::LOGGEDIN;
		case 2:
			for (;;) {
				std::cout << "Enter preferred user id" << std::endl;
				std::getline (std::cin, id);

				try { users->get (id); }
				catch (NoSuchElementException & e) {
					std::cout << "Enter preferred user name" << std::endl;
					std::getline (std::cin, name);
					newUser = new User(id, name);
					users->add (id, newUser);
					std::cout << "New User created" << std::endl;
					return menuNavCommand::MAIN;
				}
				std::cout << "The user ID you enetered already exists." << std::endl;
			}
		case 3:
			return menuNavCommand::EXIT;
		default:
			std::cout << "You did not choose one of 3 options, please enter 1, 2 or 3" << std::endl;			
			return menuNavCommand::MAIN;
	}
}

menuNavCommand LoggedInMenu (Map <std::string, Movie*> *movies , Map <std::string, Set <Movie*>*> *keywordIndex, User * curr) {
	int input;
	std::string id;
	Movie* currMovie;
	Set <Movie*>* moviesFound;
	displayCommands ();
	input = getInput ();
	switch (input) {
		case 1:
			std::cout << "Please enter title of movie" << std::endl;
			std::getline (std::cin, id);
			try { currMovie = movies->get(id); }
			catch (NoSuchElementException & e) { 
				std::cout << "No movie with that title in database" << std::endl;
				return menuNavCommand::LOGGEDIN;
			}
			displayMovie (currMovie);
			return menuNavCommand::LOGGEDIN;
		case 2:
			std::cout << "Please enter a keyword" << std::endl;
			std::getline (std::cin, id);
			try { moviesFound = keywordIndex->get(id); }
			catch (NoSuchElementException & e) {
				std::cout << "No match" << std::endl;
				return menuNavCommand::LOGGEDIN;
			}
			ViewingMovMenu (moviesFound, curr);
			return menuNavCommand::LOGGEDIN;
		case 3:
			curr->returnMovie();
			break;
		case 4:
			return menuNavCommand::QUEUE;
		case 5:
			curr = nullptr;
			return menuNavCommand::MAIN;
		default:
			std::cout << "You did not choose one of 5 options, please enter 1, 2, 3, 4 or 5" << std::endl;
			return menuNavCommand::LOGGEDIN;
	}
}

void ViewingMovMenu (Set <Movie*>* & movies, User * curr) {
	int input;
	std::cout << "There are " << movies->size() << " movies." << std::endl;
	Set <Movie *>::Iterator it = movies->begin();

	if(it == movies->end())
		std::cout << "No movies found" << std::endl;

	while (it != movies->end()) {
		displayMovie (*it);
		
		if (movies->size() > 1)
			std::cout << "1. Next movie" << std::endl; 

		std::cout << "2. Add movie to queue" << std::endl;
		std::cout << "3. Return to menu" << std::endl;
		input = getInput ();
		switch (input) {
			case 1:
				if(movies->size() > 1)
					++it;
				else
					std::cout << "Please choose one of the following options" << std::endl;
				break;
			case 2:
				curr->movieQueue()->enqueue(*it);
				break;
			case 3:
				return;
			default:
				std::cout << "You did not choose one of 3 options, please enter 1, or 2" << std::endl;
				break;	
		}
	}	
}

menuNavCommand viewQueue (User * curr) {
	int input;
	std::cout << "1. Order movie" << std::endl;
	std::cout << "2. Remove movie from queue" << std::endl;
	std::cout << "3. Move movie back to queue" << std::endl;
	std::cout << "4. Return to user menu" << std::endl;

	input = getInput ();
	switch (input) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			std::cout << "You did not choose a valid option" <<std::endl;
			return menuNavCommand::QUEUE;
	}

}

void displayMovie (Movie * mov) {
	Set<std::string> keywords = mov->getAllKeywords ();
	Set<std::string>::Iterator iter = keywords.begin();
	if(iter == keywords.end())
		std::cout << "Movie not found" << std::endl;

	while (iter != keywords.end()) {
		std::cout << keywords.getCurrentKey () << std::endl;
		++iter;
	}
}