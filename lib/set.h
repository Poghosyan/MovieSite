#pragma once
#include "map.h"
#include "pair.h"
#include "mergesort.h"
#include <vector>

template <class T>
class Set
{
	  public:
    Set ();  // constructor for a new empty set

    Set (const Set<T> & other);

    Set<T>& operator=(const Set<T>& rhs);

    ~Set (); // destructor

    int size () const; // returns the number of elements in the set

    void add (const T& item); 
      /* Adds the item to the set.
         If the item is already in the set, it should do nothing.
      */

    void remove (const T& item);
     /* Removes the item from the set.
        If the item was not in the set, it should do nothing. */

    bool contains (T item) const;
     /* Returns whether the item is in the set. */

    void merge (const Set<T> & other);
     /* Adds all elements of other to this set. 
        However, will not create duplicates, i.e., it ignores elements
        already in the set. */

    Set<T> setUnion (const Set<T> & other) const;
    // Returns the union of this and other. Does not alter this.

    Set<T> setIntersection (const Set<T> & other) const;
    // Returns the intersection of this and other. Does not alter this.

    const T & getCurrentKey();

  private:
    Map<T, T> internalStorage;
    
     /* You should use a Map (your own implementation) to store your set.
        It is part of your assignment to figure out what types you 
        need for the keyType and valueType. */

     /* If you like, you can add further data fields and private
        helper methods. */
    void addToThisFrom(const Set<T> & other);

  public:
    class Iterator {
      private: 
        const Set<T> *whoIBelongTo;
        typename Map<T, T>::Iterator activeIt;
        Iterator (const Set<T> *s,  typename Map<T, T>::Iterator &);

      public:
        friend class Set<T>;
        T operator* () const;
        // return the item the iterator is at

        Set<T>::Iterator operator++ ();
        // advances the iterator (pre-increment)

        Set<T>::Iterator operator= (const Set<T>::Iterator & other);
        // assigns the other iterator to this iterator and returns this

        bool operator== (const Set<T>::Iterator & other) const;
        // returns whether this iterator is equal to the other iterator

        bool operator!= (const Set<T>::Iterator & other) const;
        // returns whether this iterator is not equal to the other iterator

        /* Optionally, if you think that it makes your code easier to write,
        you may also overload other operators: */

        /* You may define a public copy constructor and/or default constructor
        if you think it would be helpful. */
    };

     Set<T>::Iterator begin () const;
       // returns an iterator initialized to the first element

     Set<T>::Iterator end () const;
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */
};

#include "set_impl.hpp"