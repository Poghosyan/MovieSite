#include <cstddef>
#include <iostream>

template <class keyType, class valueType>
	Map<keyType, valueType>::Map()
	{
		head = nullptr;
		tail = nullptr;
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
	void Map<keyType, valueType>::add(keyType key, valueType value)
	{
		bool hasKey = false;
		this->get(key, hasKey);
		if(hasKey)
		{
			return;
		}	

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

template <class keyType, class valueType>
	void Map<keyType, valueType>::remove (keyType key)
	{
		bool hasKey = false;
		this->get(key, hasKey);
		if(!hasKey)
		{
			return;
		}

		MapItem<keyType, valueType> *curr = head;
		while(curr->key != key && curr != nullptr)
		{
			curr = curr->next;
		}
		if(curr == head )
			if(curr->next != nullptr)
				head = curr->next;
		delete curr;
	}

template <class keyType, class valueType>
	valueType Map<keyType, valueType>::get (keyType key, bool & success) const
	{
		if(this->size() == 0)
		{
			success = false;
			valueType v;
			return v;
		}

		MapItem<keyType, valueType> *curr = head;
		while(curr->key != key && curr != tail)
		{
			curr = curr->next;
		}

		if(curr->key == key)
		{
			success = true;
			return curr->value;
		}

		success = false;
		valueType v;
		return v;
	}

template <class keyType, class valueType>
	keyType Map<keyType, valueType>::begin() const
	{
		return head->key;
	}

template <class keyType, class valueType>
	keyType Map<keyType, valueType>::end() const
	{
		return tail->key;
	}

template <class keyType, class valueType>
	keyType Map<keyType, valueType>::nextKey(keyType key) const
	{
		bool success = false;
		keyType pass_back;
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
	void  Map<keyType, valueType>::merge(const Map<keyType, valueType> & other)
	{
		bool hasKey = false;
		bool keepGoing = true;
		keyType current = other.begin();
		do
		{
			if(current == other.end())
				keepGoing = false;

			this->get(current, hasKey);
			if(!hasKey)
			{
				bool gotIt = false;
				this->add(current, other.get(current, gotIt));
			}
			current = other.nextKey(current);
		}while(!(current == other.end() && !keepGoing));
	}

template <class keyType, class valueType>
	Map<keyType, valueType>::~Map()
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