#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
	sortedSize = bag.size();
	sortedElements = new TComp[sortedSize];
	int pos = 0;

	for (int i = 0; i < bag.capacity; ++i) {
		SortedBag::Node* node = bag.table[i];
		while (node != nullptr) {
			sortedElements[pos++] = node->value;
			node = node->next;
		}
	}

	for (int i = 0; i < sortedSize - 1; ++i) {
		for (int j = i + 1; j < sortedSize; ++j) {
			if (!bag.rel(sortedElements[i], sortedElements[j])) {
				TComp temp = sortedElements[i];
				sortedElements[i] = sortedElements[j];
				sortedElements[j] = temp;
			}
		}
	}

	currentIndex = 0;
	currentNode = nullptr;
}
// Complexity Best case: theta(n^2) Worst case: theta(n^2) Total: theta(n^2)

TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw exception();
	return sortedElements[currentIndex];
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

bool SortedBagIterator::valid() {
	return currentIndex < sortedSize;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

void SortedBagIterator::next() {
	if (!valid())
		throw exception();
	currentIndex++;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

void SortedBagIterator::first() {
	currentIndex = 0;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

// Extra function
void SortedBagIterator::addAll(SortedBag& b) {
	for (int i = 0; i < b.capacity; ++i) {
		SortedBag::Node* node = b.table[i];
		while (node != nullptr) {
			bag.add(node->value);
			node = node->next;
		}
	}
}