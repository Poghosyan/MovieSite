#include <cstddef>
#include <iostream>
#include <exception>

struct NoSuchElementException : public std::exception
{
	const char* what() const throw()
	{
		return "End of list";
	}
};

template <class keyType, class valueType>
	Map<keyType, valueType>::Map()
	{
		head = nullptr;
		tail = nullptr;
	}

template <class keyType, class valueType>
	Map<keyType, valueType>::Map (const Map<keyType, valueType> & other)
	{
		addToThisFrom(other);
	}

template <class keyType, class valueType>
	Map<keyType, valueType>& Map<keyType, valueType>::operator = (const Map<keyType, valueType> & rhs)
	{
		if(this == &rhs) return *this;
		if(this->size() > 0)
		{
			deleteData();
		}
		addToThisFrom(rhs);
		return *this;
	}

template <class keyType, class valueType>
	int Map<keyType, valueType>::size() const
	{
		int counter = 0;
		MapItem<keyType, valueType> *curr = head;
		while(curr != nullptr)
		{
			++counter;
			curr = curr->next;
		}
		return counter;
	}	

template <class keyType, class valueType>
	void Map<keyType, valueType>::add(const keyType & key,const valueType & value)
	{
		try
		{
			this->get(key);
		}
		catch(NoSuchElementException & e)
		{	
			if(head == nullptr)
			{
				head = new MapItem<keyType, valueType>();
				tail = head;
				head->key = key;
				head->value = value;
				head->prev = nullptr;
				head->next = nullptr;
			}
			else
			{
				tail->next = new MapItem<keyType, valueType>();
				tail->next->prev = tail;
				tail->next->key = key;
				tail->next->value = value;
				tail = tail->next;
			}
		}

		//std::cout << "Never got to add" << std::endl;	
	}

template <class keyType, class valueType>
	void Map<keyType, valueType>::remove (const keyType & key)
	{
		try
		{
			this->get(key);
		}
		catch(NoSuchElementException & e)
		{
			return;
		}

		MapItem<keyType, valueType> *curr = head;
		while(curr->key != key && curr != nullptr)
		{
			curr = curr->next;
		}
		if(curr == head )
			head = curr->next;
		if(curr == tail)
			tail = curr->next;
		delete curr;
	}

template <class keyType, class valueType>
	const valueType & Map<keyType, valueType>::get (const keyType & key) const
	{
		if(this->size() == 0)
		{
			throw NoSuchElementException();
		}

		MapItem<keyType, valueType> *curr = head;
		while(curr->key != key && curr != tail)
		{
			curr = curr->next;
		}

		if(curr->key == key)
		{
			return curr->value;
		}

		throw NoSuchElementException();
	}

template <class keyType, class valueType>
	const keyType &  Map<keyType, valueType>::getCurrentKey () const
	{
		if(current != nullptr)
			return current->key;
		throw NoSuchElementException ();
	}

template <class keyType, class valueType>
	const valueType &  Map<keyType, valueType>::getCurrentValue () const
	{
		if(current != nullptr)
			return current->value;
		throw NoSuchElementException ();
	}

template <class keyType, class valueType>
	void  Map<keyType, valueType>::merge(const Map<keyType, valueType> & other)
	{
		for (Map<keyType,valueType>::Iterator i = other.begin(); i != other.end(); ++i)
		{
			this->add(i->keyType, i->valueType);
		}
	}

template <class keyType, class valueType>
	Map<keyType, valueType>::~Map()
	{
		deleteData();
	}

template <class keyType, class valueType>
	void Map<keyType, valueType>::deleteData()
	{
		if(this->size() > 0)
		{
			MapItem<keyType, valueType> *temp, *curr = head;
			while(curr != tail)
			{
				temp = curr;
				curr = curr->next;
				delete temp;
			}

			delete tail;
		}
	}


template <class keyType, class valueType>
	void Map<keyType, valueType>::addToThisFrom(const Map<keyType, valueType> & other)
	{
		for (Map<keyType,valueType>::Iterator i = other.begin(); i != other.end(); ++i)
		{
			Pair<keyType, valueType> p = *i;
			this->add(p.first, p.second);
		}
	}

template <class keyType, class valueType>
	Map<keyType, valueType>::Iterator::Iterator () {
	}

template <class keyType, class valueType>
	Map<keyType, valueType>::Iterator::Iterator (const Map<keyType, valueType> *s, 
														MapItem<keyType,valueType> *p) {
		whoIBelongTo = s; 
		activeIndex = p;
	}

template <class keyType, class valueType>
	Pair<keyType, valueType> Map<keyType, valueType>::Iterator::operator* () const {
		Pair<keyType, valueType> item(activeIndex->key, activeIndex->value);
		return item;
	}

template <class keyType, class valueType>
	typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::Iterator::operator++ () {
		activeIndex = activeIndex->next;
		return *this;
	}

template <class keyType, class valueType>
	typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::Iterator::operator= 
															(const Map<keyType,valueType>::Iterator & other) {
		whoIBelongTo = other.whoIBelongTo; 
		activeIndex = other.activeIndex;
		return *this;
	}

template <class keyType, class valueType>
	bool Map<keyType, valueType>::Iterator::operator== (const Map<keyType,valueType>::Iterator & other) const {
		return (whoIBelongTo == other.whoIBelongTo && activeIndex == other.activeIndex);
	}

template <class keyType, class valueType>
	bool Map<keyType, valueType>::Iterator::operator!= (const Map<keyType,valueType>::Iterator & other) const {
		return (whoIBelongTo != other.whoIBelongTo || activeIndex != other.activeIndex);
	}

template <class keyType, class valueType>
	typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::begin () const {
		Map<keyType, valueType>::Iterator it(this, head);
		return it;
	}

template <class keyType, class valueType>
	typename Map<keyType, valueType>::Iterator Map<keyType, valueType>::end () const {
		Map<keyType, valueType>::Iterator it(this, nullptr);
		return it;
	}