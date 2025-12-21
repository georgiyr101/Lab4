#pragma once
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

// Algorithm class with static methods for search and sort operations
class Algorithms
{
public:
    // Search function using iterators
    // Returns iterator to first element that matches the predicate, or end if not found
    template<typename Iterator, typename Predicate>
    static Iterator find(Iterator begin, Iterator end, Predicate pred)
    {
        for (Iterator it = begin; it != end; ++it)
        {
            if (pred(*it))
                return it;
        }
        return end;
    }

    // Sort function using iterators
    template<typename Iterator, typename Compare>
    static void sort(Iterator begin, Iterator end, Compare comp)
    {
        if (begin == end)
            return;

        // Convert to vector for easier sorting
        vector<typename iterator_traits<Iterator>::value_type> temp;
        for (Iterator it = begin; it != end; ++it)
        {
            temp.push_back(*it);
        }

        // Sort the vector
        std::sort(temp.begin(), temp.end(), comp);

        // Copy back (if iterator allows writing)
        Iterator it = begin;
        for (size_t i = 0; i < temp.size() && it != end; ++i, ++it)
        {
            *it = temp[i];
        }
    }
};

