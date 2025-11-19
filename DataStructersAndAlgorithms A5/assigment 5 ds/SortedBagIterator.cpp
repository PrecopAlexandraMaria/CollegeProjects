#include "SortedBagIterator.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

void SortedBagIterator::pushLeft(SortedBag::BSTNode* node) {
	//Impinge toate nodurile din subarborele stang al nodului dat in stiva
    while (node != nullptr) {
        stack.push(node);
        node = node->left;
    }
}
// Complexity Best case: θ(1) Worst case: θ(capacity) Total: O(capacity)

TComp SortedBagIterator::getCurrent() {
	// Verifica daca iteratorul este valid, daca da, returneaza valoarea curenta
    if (!valid())
        throw exception();
    return stack.top()->info;
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)

bool SortedBagIterator::valid() {
	// Verifica daca stiva nu este goala, ceea ce inseamna ca iteratorul este valid
    return !stack.empty();
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)

void SortedBagIterator::next() {
	// Verifica daca iteratorul este valid, daca nu, arunca o exceptie
    if (!valid())
        throw exception();

	// Scoate nodul curent din stiva
    SortedBag::BSTNode* node = stack.top();
    stack.pop();
    pushLeft(node->right);
}
// Complexity Best case: θ(1) Worst case: θ(capacity) Total: O(capacity)

void SortedBagIterator::first() {
	// Incepe iterarea de la radacina arborelui, impingand toate nodurile din subarborele stang in stiva
    while (!stack.empty())
        stack.pop();
    pushLeft(bag.root);
}
// Complexity Best case: θ(1) Worst case: θ(capacity) Total: O(capacity)
