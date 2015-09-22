#include <iostream>
#include <vector>
class MergeSort {
	public:
		template <class T>
		static std::vector<T> sort (std::vector<T> a) {
			std::vector<T> f_half;
			std::vector<T> s_half;
			if(a.size() > 1) {
				std::size_t const half_size = a.size()/2;
				f_half = std::vector<T>(a.begin(), a.begin() + half_size);
				s_half = std::vector<T>(a.begin() + half_size, a.end());
			}
			else { return a; }
			f_half = sort(f_half);
			s_half = sort(s_half);
			typename std::vector<T>::iterator f_iter = f_half.begin();
			typename std::vector<T>::iterator s_iter = s_half.begin();
			for(int i = 0; i < a.size(); ++i) {
				if(s_iter == s_half.end()) 
				{
					a[i] = *f_iter;
					++f_iter;
				}
				else if (f_iter == f_half.end())
				{
					a[i] = *s_iter;
					++s_iter; 
				}
				else if (*f_iter <= *s_iter) 
				{
					a[i] = *f_iter;
					++f_iter;
				}
				else
				{
					a[i] = *s_iter;
					++s_iter;
				}
			}
			return a;
		}
};