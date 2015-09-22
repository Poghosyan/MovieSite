#pragma once

#include "pair.h"

template <class keyType, class valueType>
struct MapItem
{
   keyType key;
   valueType value;
   MapItem<keyType, valueType> *prev, *next;
};
   
template <class keyType, class valueType>
class Map
{
   public:
      Map ();  // constructor for a new empty map

      Map (const Map<keyType, valueType> & other);

      Map& operator=(const Map<keyType, valueType> & rhs);

      ~Map (); // destructor

      int size () const; // returns the number of key-value pairs

      void add (const keyType & key, const valueType & value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should do nothing.
      */

      void remove (const keyType & key);
      /* Removes the association for the given key.
        If the key has no association, it should do nothing. */

      const valueType & get (const keyType & key) const;
      /* Returns the value associated with the given key.
        If the key existed in the map, success should be set to true.
        If the key has no association, it should set success to false. */

      void merge (const Map<keyType, valueType> & other);
      /* Adds all the key-value associations of other to the current map.
        If both maps (this and other) contain an association for the same
        key, then the one of this is used. */

      const keyType & getCurrentKey () const;

      const valueType & getCurrentValue () const;
  private:
      /* The head and tail of the linked list you're using to store
        all the associations. */

      MapItem <keyType, valueType> *current, *head, *tail;

      /* If you like, you can add further data fields and private
        helper methods. */
      void addToThisFrom(const Map<keyType, valueType> & other);
      void deleteData();

  public:
    class Iterator {
    /* add any constructors that you feel will be helpful,
      and choose whether to make them public or private. */
    private:
      const Map<keyType, valueType> *whoIBelongTo;
      MapItem<keyType, valueType> *activeIndex;

      Iterator(const Map<keyType, valueType> *s, MapItem<keyType,valueType> *p);

    public:
      friend class Map<keyType, valueType>;
      Iterator();
      Pair<keyType, valueType> operator* () const;
          // return the current (key, value) pair the iterator is at

      Map<keyType, valueType>::Iterator operator++ ();
          // advances the iterator (pre-increment)

      Map<keyType, valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other);
          // assigns the other iterator to this iterator and returns this

      bool operator== (const Map<keyType,valueType>::Iterator & other) const;
      // returns whether this iterator is equal to the other iterator

      bool operator!= (const Map<keyType,valueType>::Iterator & other) const;
      // returns whether this iterator is not equal to the other iterator

      /* Optionally, if you think that it makes your code easier to write,
      you may also overload other operators: */

      /* You may define a public copy constructor and/or default constructor
      if you think it would be helpful. */
  };

      Iterator begin () const;
       // returns an iterator initialized to the first element

      Iterator end () const;
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */
};

#include "map_impl.hpp"

