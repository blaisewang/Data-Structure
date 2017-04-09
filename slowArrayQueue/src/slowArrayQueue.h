#ifndef slowArrayQueue_
#define slowArrayQueue_

#include <sstream>
#include "queue.h"
#include "myExceptions.h"

using namespace std;

template<class T>
class slowArrayQueue: public queue<T>
{
public:
	slowArrayQueue(int initialCapacity = 10);
	~slowArrayQueue()
	{
		delete[] queue;
	}
	bool empty() const
	{
		return theFront > theBack;
	}
	int size() const
	{
		return theBack - theFront + 1;
	}
	T& front()
	{ // return front element
		if (theFront > theBack)
			throw queueEmpty();
		return queue[theFront];
	}
	T& back()
	{ // return theBack element
		if (theFront > theBack)
			throw queueEmpty();
		return queue[theBack];
	}
	void pop()
	{ // remove theFront element
		if (theFront > theBack)
			throw queueEmpty();
		theFront = theFront + 1;
		queue[theFront].~T();  // destructor for T
	}
	void push(const T& theElement);

private:
	int theFront;       // position of theFront element
	int theBack;        // position of theBack element
	int arrayLength;    // queue capacity
	T *queue;           // element array
};

template<class T>
slowArrayQueue<T>::slowArrayQueue(int initialCapacity)
{           // Constructor.
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = -1;
}

template<class T>
void slowArrayQueue<T>::push(const T& theElement)
{ // Add theElement to queue.

	// increase array length if necessary
	if ((theBack + 1) == arrayLength)
	{ // double array length
	  // allocate a new array
		T* newQueue = new T[2 * arrayLength];

		// copy elements into new array
		copy(queue + theFront, queue + theBack + 1, newQueue + theFront);

		// switch to newQueue and set theFront and theBack
		arrayLength *= 2;
		delete[] queue;
		queue = newQueue;
	}
	// put theElement at the theBack of the queue
	theBack = theBack + 1;
	queue[theBack] = theElement;
}

#endif
