// abstract class bsTree
// abstract data type specification for binary search trees
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef bsTree_
#define bsTree_

#include "dictionary.h"

template<class K, class E>
class bsTree : public dictionary<K, E> {
public:
    virtual ~bsTree() // there must have non-virtual destructor if the class has virtual method
    {
    }

    virtual void ascend() = 0;
    // output in ascending order of key
};

#endif

