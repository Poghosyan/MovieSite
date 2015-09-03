#include "lib/map.h"
#include "lib/set.h"
#include "user.h"
#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>

void getUserRecords (const std::string & fileName, Map <std::string, User*> &);
void getMovieRecords (const std::string & fileName, Map <std::string, Movie*> &);
void displayLogin();

int main (int argc, char * argv[]) {
	std::string userFile, mediaFile;
	if (argc <= 1) {
		std::cout << "Didn't specify file, exiting program" << std::endl;
		return 0;
	}

	std::ifstream file (argv[ argc - 1 ]);
	if (file.is_open ()) {
		std::getline (file, userFile);
		std::getline (file, mediaFile);
	}


}


void getUserRecords (const std::string & fileName, Map <std::string, User*> & container) {
	User* user;
	std::string line, id, name;
	std::ifstream file (fileName.c_str ());
	if (file.is_open ()) {
		while (std::getline (file, line, ' ')) {
			if (line == "BEGIN") {
				std::getline (file, line);
				id = line;
			}		
			else if (line == "NAME:") {
				std::getline (file, line);
				name = line;
				user = new User (id, name);
			}
			else if ( line == "END")
				container.add (id, user);
		}
	}	
}

void getMovieRecords (const std::string & fileName, Map <std::string, Movie*> & container) {
	Movie* movie;
	std::string line, title, keyword;
	std::ifstream file (fileName.c_str ());
	if (file.is_open ()) {
		while (std::getline (file, line, ' ')) {
			if (line == "BEGIN") {
				std::getline (file, line);
				title = line;
				movie = new Movie(title);
			}		
			else if (line == "KEYWORD:") {
				std::getline (file, line);
				keyword = line;
				movie->addKeyword(keyword);
			}
			else if (line == "END")
				container.add(title, movie);
		}
	}	
}

void displayLogin () {
	std::cout << "1. Log In" << std::endl;
	std::cout << "2. Create a new user" << std::endl;
	std::cout << "3. Quit" << std::endl;
}
