template <class T>
	Set<T>::Set()
	{
		internalStorage = Map<T, T>();
	}

template <class T>
    Set<T>::Set (const Set<T> & other)
    {
        this->addToThisFrom(other);
    }

template <class T>
    Set<T>& Set<T>::operator = (const Set<T>& rhs)
    {
        if(this == rhs) { return *this; }
        if(this->size() > 0)
        {
            T temp, item = this->begin();
            while(item != this->end())
            {
                temp = item;
                item = this->nextKey(item);
                this->remove(temp);
            }
            this->remove(this->end());
        }

        this->addToThisFrom(rhs);
    }

template <class T>
	int Set<T>::size () const
	{
		return internalStorage.size();
	}

template <class T>
    void Set<T>::add (const T& item)
    {
    	internalStorage.add(item, item);
    }

template <class T>
    void Set<T>::remove (const T& item)
    {
    	internalStorage.remove(item);
    }

template <class T>
    bool Set<T>::contains (T item) const
    {   try
        {
    	   internalStorage.get(item);
        }
        catch(NoSuchElementException & e)
        {
            return false;
        }
        return true;
    }

template <class T> 
    T Set<T>::begin () const
    {
        return internalStorage.begin();;
    }

template <class T>
    T Set<T>::end () const
    {
    	return internalStorage.end();
    }

template <class T>
    T Set<T>::nextKey (T& item) const
    {
        T current;
        current = internalStorage.nextKey(item);
    	return current;
    }

template <class T>
    void Set<T>::first()
    {
         try
        {
            internalStorage.first();
        }
        catch(NoSuchElementException & e)
        {
            throw e;
        }
    }

template <class T>
    void Set<T>::next()
    {
        try
        {
            internalStorage.next();
        }
        catch(NoSuchElementException & e)
        {
            throw e;
        }
    }

template <class T>
    const T & Set<T>::getCurrentKey()
    {
        return internalStorage.getCurrentKey();
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
			current = other.nextKey(current);
		}while(!(current == other.end() && !keepGoing));
    }

template <class T>
    Set<T> Set<T>::setUnion (const Set<T> & other) const
    {
        Set<T> *set = new Set<T>();
        addAllFromTo(*this, *set);
        addAllFromTo(other, *set);
        return *set;
    }

template <class T>
    Set<T> Set<T>::setIntersection (const Set<T> & other) const
    {
        Set<T> *set = new Set<T>();
        try
        {
            this->first();
            if(other.contains(this->getCurrentKey()))
                set->add(this->getCurrentKey());
            for(;;)
            {
                try
                {
                    this->next();
                    if(other.contains(this->getCurrentKey()))
                        set->add(this->getCurrentKey());
                }
                catch(NoSuchElementException & e)
                {
                    break;
                }
            } 
        }
        catch(NoSuchElementException & e)
        {
            std::cout << "Nothing in union!" << std::endl;
        }
        return *set;
    }

template <class T>
    Set<T>::~Set()
    {
    	
    }

template <class T>
    void Set<T>::addToThisFrom(const Set<T>& other)
    {
        bool hasKey = false;
        bool keepGoing = true;
        T current = other.begin();
        do
        {
            if(current == other.end())
                keepGoing = false;

            bool gotIt = false;
            this->add(current);
            current = other.nextKey(current);
        }while(!(current == other.end() && !keepGoing));
    }

template <class T>
    void Set<T>::addAllFromTo(const Set<T> & from, const Set<T> & to) const
    {
        try
        {
            from->first(); 
            to->add(from->getCurrentKey());
            for(;;)
            {
                try
                { 
                    from->next();
                    to->add(from->getCurrentKey());
                }
                catch(NoSuchElementException & e) { break; }
            }
        }
        catch(NoSuchElementException & e) {}
    }