#pragma once
#include <iostream>

class User {
  public:
    User ();

    User (std::string ID, std::string name);  
    /* constructor that generates a user with the given name and ID.
       While multiple users may have the same name, the ID should be unique
       (e.g., an e-mail address), so that users can log in with it. */

    User (const User & other); // copy constructor

    ~User ();            // destructor

    std::string getID () const;    // returns the ID associated with this user

    std::string getName () const;  // returns the name associated with this user

  private:
    // you get to decide what goes here.
    std::string m_ID;
    std::string m_name;
};
