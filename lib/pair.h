#pragma once

template <class FirstType, class SecondType> 
struct Pair {
   FirstType first;
   SecondType second;

   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
};