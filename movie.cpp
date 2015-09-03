#include "movie.h"

std::string Movie::getTitle () const {
	return m_title;
}

void Movie::addKeyword (std::string keyword) {
	keywords.add(keyword);
}

Set<std::string> Movie::getAllKeywords () const {
	return keywords;
}

Movie::Movie () {

}

Movie::Movie (std::string & title) : m_title(title), keywords(Set <std::string>()) { 

}

Movie::Movie (const Movie & other) {
	m_title = other.getTitle();
	keywords = other.getAllKeywords();
}

Movie::~Movie () {

}

