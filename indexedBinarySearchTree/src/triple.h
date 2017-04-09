#ifndef triple_h
#define triple_h

using namespace std;

template<class K, class E>
class triple
{
public:
	triple(const pair<const K, E> thePair) :
			thePair(thePair)
	{
		leftSize = 0;
	}
	int leftSize;
	pair<K, E> thePair;
};

#endif
