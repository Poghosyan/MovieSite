template <class T>
	Set<T>::Set()
	{
		internalStorage = Map<T, T>();
	}

template <class T>
	int Set<T>::size () const
	{
		return internalStorage.size();
	}

template <class T>
    void Set<T>::add (T item)
    {
    	internalStorage.add(item, item);
    }

template <class T>
    void Set<T>::remove (T item)
    {
    	internalStorage.remove(item);
    }

template <class T>
    bool Set<T>::contains (T item) const
    {
    	bool gotIt = false;
    	internalStorage.get(item, gotIt);
    	return gotIt;
    }

template <class T>
    T Set<T>::begin() const
    {
    	return internalStorage.begin();
    }

template <class T>
    T Set<T>::end() const
    {
    	return internalStorage.end();
    }

template <class T>
    T Set<T>::next(const T& item) const
    {
    	return internalStorage.nextKey(item);
    }

template <class T>
    void Set<T>::merge (const Set<T> & other)
    {
    	bool hasKey = false;
		bool keepGoing = true;
		T current = other.begin();
		do
		{
			if(current == other.end())
				keepGoing = false;

			if(!contains(current))
			{
				bool gotIt = false;
				this->add(current);
			}
			current = other.next(current);
		}while(!(current == other.end() && !keepGoing));
    }

template <class T>
    Set<T>::~Set()
    {
    	
    }