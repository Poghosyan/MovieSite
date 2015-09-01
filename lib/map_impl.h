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
	keyType Map<keyType, valueType>::begin() const
	{
		if(head == nullptr)
		{
			throw NoSuchElementException();
		}
		return head->key;
	}

template <class keyType, class valueType>
	keyType Map<keyType, valueType>::end() const
	{
		if(tail == nullptr)
			throw NoSuchElementException();
		return tail->key;
	}

template <class keyType, class valueType>
	keyType Map<keyType, valueType>::nextKey(keyType& key) const
	{
		MapItem<keyType, valueType> *curr = head;
		if(tail->key != key)
		{
			while(curr->key != key)
			{
				curr = curr->next;
			}
			return curr->next->key;
		}
		else
			return tail->key;
	}

template <class keyType, class valueType>
	void  Map<keyType, valueType>::first()
	{
		if(this->size() == 0)
			throw NoSuchElementException();
		current = head;
	}

template <class keyType, class valueType>
	void  Map<keyType, valueType>::next()
	{
		if(current == tail)
			throw NoSuchElementException();
		current = current->next;
	}

template <class keyType, class valueType>
	const keyType &  Map<keyType, valueType>::getCurrentKey () const
	{
		if(current != nullptr)
			return current->key;
	}

template <class keyType, class valueType>
	const valueType &  Map<keyType, valueType>::getCurrentValue () const
	{
		if(current != nullptr)
			return current->value;
	}

template <class keyType, class valueType>
	void  Map<keyType, valueType>::merge(const Map<keyType, valueType> & other)
	{
		bool keepGoing = true;
		keyType current = other.begin();
		do
		{
			if(current == other.end())
				keepGoing = false;

			try
			{
				this->get(current);
			}	
			catch(NoSuchElementException & e)
			{
				this->add(current, other.get(current));
			}
			current = other.nextKey(current);
		}while(!(current == other.end() && !keepGoing));
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
		valueType val;
		try
		{
			keyType curr = other.begin();
			std::cout << "Here" << std::endl;

			while(curr != other.end())
			{
				try
				{
					val = other.get(curr);
				}
				catch(NoSuchElementException & e){}
				this->add(curr, val);
				curr = other.nextKey(curr);
			}
			try
			{
				val = other.get(curr);
			}	
			catch(NoSuchElementException & e){}
			this->add(curr, val);
		}
		catch(NoSuchElementException & e) {}
	}