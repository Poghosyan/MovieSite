#include "user.h"

User::User () {

}

User::User (std::string ID, std::string name) : m_ID(ID), m_name(name) {

}

User::User (const User & other) {
	m_ID = other.getID();
	m_name = other.getName();
}

std::string User::getID () const {
	return m_ID;
}

std::string User::getName () const {
	return m_name;
}

User::~User () {

}
