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
    Set<T>& Set<T>::operator = (const Set<T> & rhs)
    {
        if(this == &rhs) return *this;
        if(this->size() > 0)
        {
            for (Set<T>::Iterator i = this->begin(); i != this->end(); ++i)
            {
                this->remove (*i);
            }
        }

        this->addToThisFrom(rhs);
        return *this;
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
    const T & Set<T>::getCurrentKey()
    {
        return internalStorage.getCurrentKey();
    }

template <class T>
    void Set<T>::merge (const Set<T> & other)
    {
    	for (Set<T>::Iterator i = other->begin(); i != other->end(); ++i)
        {
            this->add (*i);
        }
    }

template <class T>
    Set<T> Set<T>::setUnion (const Set<T> & other) const
    {
        std::vector<T> vthis, vother, sorted;
        Set<T> unionSet;
        for(Set<T>::Iterator i = this->begin(); i != this->end(); ++i)
        {
            vthis.push_back(*i);
        }
        for(Set<T>::Iterator i = other.begin(); i != other.end(); ++i)
        {
            vother.push_back(*i);
        }
        vthis = MergeSort::sort(vthis);
        vother = MergeSort::sort(vother);
        Set<T>::Iterator ithis = this->begin(), iother = other.begin();
        while (ithis != this->end() || iother != other.end())
        {
            if ((ithis == this->end()) != (iother == other.end())) 
            {    

                if (ithis == this->end() && sorted.back() != *iother)
                {
                    sorted.push_back(*iother);
                    ++iother;
                }
                else if (iother == other.end() && sorted.back() != *ithis)
                {
                    sorted.push_back(*ithis);
                    ++ithis;
                }
                else if (iother != other.end())
                {
                    ++iother;
                }
                else
                {
                    ++ithis;
                }
            }
            else
            {
                if(*iother == *ithis)
                {
                    sorted.push_back(*ithis);
                    ++ithis;
                    ++iother;
                }
                else if (*iother > *ithis) 
                { 
                    sorted.push_back(*ithis);
                    ++ithis;
                }
                else
                {
                    sorted.push_back(*iother);
                    ++iother;
                }
            }
        }
        for (typename std::vector<T>::iterator i = sorted.begin(); i != sorted.end(); ++i)
        {
            unionSet.add(*i);
        }
        return unionSet;
    }

template <class T>
    Set<T> Set<T>::setIntersection (const Set<T> & other) const
    {
        std::vector<T> vthis, vother, sorted;
        Set<T> intersectionSet;
        for(Set<T>::Iterator i = this->begin(); i != this->end(); ++i)
        {
            vthis.push_back(*i);
        }
        for(Set<T>::Iterator i = other.begin(); i != other.end(); ++i)
        {
            vother.push_back(*i);
        }
        vthis = MergeSort::sort(vthis);
        vother = MergeSort::sort(vother);
        Set<T>::Iterator ithis = this->begin(), iother = other.begin();
        while (ithis != this->end() && iother != other.end())
        {
            if(*iother == *ithis)
            {
                sorted.push_back(*ithis);
                ++ithis;
                ++iother;
            }
            else if (*iother > *ithis) 
            { 
                ++ithis;
            }
            else
            {
                ++iother;
            }
        }
        for (typename std::vector<T>::iterator i = sorted.begin(); i != sorted.end(); ++i)
        {
            intersectionSet.add(*i);
        }
        return intersectionSet;
    }

template <class T>
    Set<T>::~Set()
    {
    	
    }

template <class T>
    void Set<T>::addToThisFrom(const Set<T>& other)
    {
        for (Set<T>::Iterator i = other.begin(); i != other.end(); ++i)
        {
            this->add (*i);
        }
    }

template <class T>
    Set<T>::Iterator::Iterator (const Set<T> *s,  typename Map<T, T>::Iterator & i)
    {
        whoIBelongTo = s;
        activeIt = i;
    }

template <class T>
    T Set<T>::Iterator::operator* () const
    {
        Pair<T, T> p = *activeIt;
        return p.first;
    }

template <class T>
    typename Set<T>::Iterator Set<T>::Iterator::operator++ () {
        activeIt = ++activeIt;
        return *this;
    }

template <class T>
    typename Set<T>::Iterator Set<T>::Iterator::operator= (const Set<T>::Iterator & other) {
        whoIBelongTo = other.whoIBelongTo;
        activeIt = other.activeIt;
        return *this;
    }

template <class T>
    bool Set<T>::Iterator::operator== (const Set<T>::Iterator & other) const {
        return (whoIBelongTo == other.whoIBelongTo && activeIt == other.activeIt);
    }

template <class T>
    bool Set<T>::Iterator::operator!= (const Set<T>::Iterator & other) const {
        return (whoIBelongTo != other.whoIBelongTo || activeIt != other.activeIt);
    }

template <class T>
    typename Set<T>::Iterator Set<T>::begin () const {
        typename Map<T, T>::Iterator iter = internalStorage.begin();
        Set<T>::Iterator it(this, iter);
        return it;
    }

template <class T>
    typename Set<T>::Iterator Set<T>::end () const {
        typename Map<T, T>::Iterator iter = internalStorage.end(); 
        Set<T>::Iterator it(this, iter);
        return it;
    }