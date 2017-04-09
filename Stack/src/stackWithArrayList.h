#ifndef stackWithArrayList_h
#define stackWithArrayList_h

#include <iostream>
#include "stack.h"
#include "arrayList.h"

using namespace std;

template<class T>
class stackWithArrayList: public stack<T>
{
public:
	stackWithArrayList(int initialCapacity = 10)
	{
	}
	~stackWithArrayList()
	{
		while (list.size())
			list.erase(0);
	}
	bool empty() const
	{
		return list.empty();
	}
	int size() const
	{
		return list.size();
	}
	T& top()
	{
		if (list.empty())
			throw stackEmpty();
		return list.get(list.size() - 1);
	}
	void pop()
	{
		if (list.empty())
			throw stackEmpty();
		list.erase(list.size() - 1);
	}
	void push(const T& theElement)
	{
		list.insert(list.size(), theElement);
	}

private:
	arrayList<T> list;
};

#endif
