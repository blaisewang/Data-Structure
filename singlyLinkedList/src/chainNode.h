// chain node

#ifndef chainNode_h
#define chainNode_h

template<class T>
struct chainNode
{
	// data members
	T element;
	chainNode<T> *next;

	// methods
	chainNode()
	{
		this->next = NULL;
	}
	chainNode(const T& element)
	{
		this->element = element;
		this->next = NULL;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};

#endif
