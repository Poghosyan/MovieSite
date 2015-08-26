#include "map.h"

template <class T>
class Set
{
	  public:
    Set ();  // constructor for a new empty set

    ~Set (); // destructor

    int size () const; // returns the number of elements in the set

    void add (T item); 
      /* Adds the item to the set.
         If the item is already in the set, it should do nothing.
      */

    void remove (T item);
     /* Removes the item from the set.
        If the item was not in the set, it should do nothing. */

    bool contains (T item) const;
     /* Returns whether the item is in the set. */

    void merge (const Set<T> & other);
     /* Adds all elements of other to this set. 
        However, will not create duplicates, i.e., it ignores elements
        already in the set. */

    T begin() const;

    T end() const;

    T next(const T& other) const;

  private:
    Map<T, T> internalStorage;
     /* You should use a Map (your own implementation) to store your set.
        It is part of your assignment to figure out what types you 
        need for the keyType and valueType. */

     /* If you like, you can add further data fields and private
        helper methods. */
};

#include "set_impl.h"