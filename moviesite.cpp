#include "lib/map.h"
#include "lib/set.h"
#include "user.h"
#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

void getUserRecords (const std::string & fileName, Map <std::string, User*> &);
void getMovieRecords (const std::string & fileName, Map <std::string, Movie*> &);
void mapMovieToKeyword (Map <std::string, Movie*> &, Map <std::string, Set <Movie*>*> &);
void displayLogin ();
void displayCommands ();
int getInput ();
bool executeMenu1 (Map <std::string, User*> *, Map <std::string, Movie*> *, Map <std::string, Set <Movie*>*> *);
bool executeMenu2 (Map <std::string, Movie*> *, Map <std::string, Set <Movie*>*> *);
void executeMenu3 (Set <Movie*>* &);
void displayMovie (Movie * mov);

int main (int argc, char * argv[]) {
	bool stop = true;
	std::string userFile, mediaFile;
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
		stop = executeMenu1 (&users, &movies, &keywordIndex);
	}
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
	try {
		movies.first ();
	} catch (NoSuchElementException & e) { 
		std::cout << "No movies to search." << std::endl;
		return;
	}

	for (;;) {
		curr = movies.getCurrentValue ();
		currKeywords = curr->getAllKeywords ();
		try {
			currKeywords.first ();
			for (;;) {
				try {
					currMovieSet = keyMap.get(currKeywords.getCurrentKey ());
					currMovieSet->add(curr);
				} catch (NoSuchElementException & e) {
					currMovieSet = new Set <Movie*>();
					currMovieSet->add(curr);
					keyMap.add(currKeywords.getCurrentKey (), currMovieSet);
				}
				currKeywords.next();
			}
		} catch (NoSuchElementException & e) { }
		try {
			movies.next ();
		} catch (NoSuchElementException & e) { 
			break;
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
	std::cout << "3. Logout" << std::endl;
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

bool executeMenu1 (Map <std::string, User*> *users, Map <std::string, Movie*> *movies, Map <std::string, Set <Movie*>*> *keywordIndex) {
	int input;
	std::string id, name;
	User *newUser;
	displayLogin ();
	input = getInput ();
	switch (input) {
		case 1:
			std::cout << "Please enter User ID" << std::endl;
			std::getline (std::cin, id);
			try { users->get(id); }
			catch (NoSuchElementException & e) { 
				std::cout << "No user with that user ID exists" << std::endl;
				return true;
			}
			return executeMenu2 (movies, keywordIndex);
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
					break;
				}
				std::cout << "The user ID you enetered already exists." << std::endl;
			}
			return true;
		case 3:
			return false;
		default:
			std::cout << "You did not choose one of 3 options, please enter 1, 2 or 3" << std::endl;			
			return true;
	}
}

bool executeMenu2 (Map <std::string, Movie*> *movies , Map <std::string, Set <Movie*>*> *keywordIndex) {
	int input;
	std::string id;
	Movie* currMovie;
	Set <Movie*>* moviesFound;
	for (;;) {
		displayCommands ();
		input = getInput ();
		switch (input) {
			case 1:
				std::cout << "Please enter title of movie" << std::endl;
				std::getline (std::cin, id);
				try { currMovie = movies->get(id); }
				catch (NoSuchElementException & e) { 
					std::cout << "No movie with that title in database" << std::endl;
					break;
				}
				displayMovie (currMovie);
				break;
			case 2:
				std::cout << "Please enter a keyword" << std::endl;
				std::getline (std::cin, id);
				try { moviesFound = keywordIndex->get(id); }
				catch (NoSuchElementException & e) {
					std::cout << "No match" << std::endl;
					break;
				}
				executeMenu3 (moviesFound);
				break;
			case 3:
				return true;
			default:
				std::cout << "You did not choose one of 3 options, please enter 1, 2 or 3" << std::endl;
				break;
		}
	}
}

void executeMenu3 (Set <Movie*>* & movies) {
	int input;
	std::cout << "There are " << movies->size() << " movies." << std::endl;
	try { movies->first (); }
	catch (NoSuchElementException & e) {
		std::cout << "No movies to display" << std::endl;
		return;
	}
	for (;;) {
		displayMovie (movies->getCurrentKey ());
		if (movies->size() > 1)
			std::cout << "1. Next movie" << std::endl;
		std::cout << "2. Return to menu" << std::endl;
		input = getInput ();
		switch (input) {
			case 1:
				try { movies->next (); }
				catch (NoSuchElementException & e) {
					return;
				}
				break;
			case 2:
				return;
			default:
				std::cout << "You did not choose one of 3 options, please enter 1, or 2" << std::endl;
				break;	
		}
	}	
}

void displayMovie (Movie * mov) {
	Set<std::string> keywords = mov->getAllKeywords ();
	std::cout << mov->getTitle () << std::endl;
	try { keywords.first(); }
	catch (NoSuchElementException & E) {
		std::cout << "Movie not found" << std::endl;
		return;
	} 
	for (;;) {
		std::cout << keywords.getCurrentKey () << std::endl;
		try { keywords.next (); }
		catch (NoSuchElementException & E) {
			break;
		}
	}
}