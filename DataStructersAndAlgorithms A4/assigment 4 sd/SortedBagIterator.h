#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	SortedBag& bag;
	int currentIndex;
	SortedBag::Node* currentNode;

	TComp* sortedElements;
	int sortedSize;

	SortedBagIterator(SortedBag& b);


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();

	//extra function
	void addAll(SortedBag& b);
};

