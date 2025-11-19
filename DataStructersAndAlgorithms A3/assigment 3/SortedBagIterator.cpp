#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	// constructor
	first();
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)

TComp SortedBagIterator::getCurrent() {
	//returns the current element from the iterator
	if (!valid())
		throw exception();

	return bag.nodes[currentIndex].info;
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)

bool SortedBagIterator::valid() {
	return currentIndex != -1;
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)

void SortedBagIterator::next() {
	if (!valid()) 
		throw std::exception();


	if (frequencyIndex < bag.nodes[currentIndex].frequency) {
		//if the current element has more than one occurence, we just move to the next occurence
		frequencyIndex++;
	}

	else {
		//if the current element has no more occurences, we move to the next element
		currentIndex = bag.nodes[currentIndex].next;
		frequencyIndex = 1;
	}
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)

void SortedBagIterator::first() {
	//sets the iterator to the first element of the sorted bag
	//if the bag is empty, the iterator is invalid

	currentIndex = bag.head;
	frequencyIndex = 1;
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)