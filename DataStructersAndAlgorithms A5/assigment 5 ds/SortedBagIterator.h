#pragma once
#include "SortedBag.h"
#include <stack>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	std::stack<SortedBag::BSTNode*> stack;

	SortedBagIterator(const SortedBag& b);
	void pushLeft(SortedBag::BSTNode* node);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

