#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->capacity = 13;
	this->totalElements = 0;
	this->rel = r;
	this->loadFactor = 0.7;
	this->table = new Node * [capacity];
	for (int i = 0; i < capacity; i++) {
		table[i] = nullptr;
	}
}
// Complexity Best case: theta(capacity) Worst case: theta(capacity) Total: theta(capacity)


int SortedBag::hash(TComp e) const {
	if (e < 0) {
		e = -e;
	}
	int h = e % capacity;
	return h;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

void SortedBag::resizeAndRehash() {
	int oldCapacity = capacity;
	capacity *= 2;
	Node** oldTable = table;
	table = new Node * [capacity];
	for (int i = 0; i < capacity; i++)
		table[i] = nullptr;

	totalElements = 0;
	for (int i = 0; i < oldCapacity; i++) {
		Node* current = oldTable[i];
		while (current != nullptr) {
			add(current->value);
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}
	}

	delete[] oldTable;
}
// Complexity Best case: theta(capacity) Worst case: theta(capacity) Total: theta(capacity)

void SortedBag::add(TComp e) {
	//verificam daca trebuie sa facem resize
	if ((double)(totalElements + 1) / capacity > loadFactor)
		resizeAndRehash();

	//setam indexul la care trebuie sa adaugam si cream un nod nou
	int index = hash(e);
	Node* newNode = new Node{ e, nullptr };

	Node* current = table[index];
	Node* prev = nullptr;
	
	//parcurgem lista de la indexul respectiv
	while (current != nullptr && rel(current->value, e)) {
		prev = current;
		current = current->next;
	}

	//daca lista este goala sau nodul curent este mai mare decat nodul pe care vrem sa-l adaugam
	if (prev == nullptr) {
		newNode->next = table[index];
		table[index] = newNode;
	}
	//altfel, daca nodul curent este mai mic decat nodul pe care vrem sa-l adaugam il punem in fata
	else {

		newNode->next = prev->next;
		prev->next = newNode;
	}

	totalElements++;
}
// Complexity Best case: theta(1) Worst case: theta(capacity) Total: O(capacity)


bool SortedBag::remove(TComp e) {
	//verificam daca trebuie sa facem resize
	int index = hash(e);
	Node* current = table[index];
	Node* prev = nullptr;

	//parcurgem lista de la indexul respectiv
	while (current != nullptr) {
		if (current->value == e) {
			//daca nodul curent este primul nod din lista
			if (prev == nullptr) {
				table[index] = current->next;
			}
			//altfel, daca nodul curent nu este primul nod din lista
			else {
				prev->next = current->next;
			}
			delete current;
			totalElements--;
			return true;
		}
		prev = current;
		current = current->next;
	}

	return false;
}
// Complexity Best case: theta(1) Worst case: theta(capacity) Total: O(capacity)

bool SortedBag::search(TComp e) const {
	int index = hash(e);
	Node* current = table[index];
	while (current != nullptr) {
		if (current->value == e)
			return true;
		current = current->next;
	}
	return false;
}
// Complexity Best case: theta(1) Worst case: theta(capacity) Total: O(capacity)

int SortedBag::nrOccurrences(TComp e) const {
	int index = hash(e);
	int count = 0;
	Node* current = table[index];
	while (current != nullptr) {
		if (current->value == e)
			count++;
		current = current->next;
	}
	return count;
}
// Complexity Best case: theta(1) Worst case: theta(capacity) Total: O(capacity)

int SortedBag::size() const {
	return totalElements;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

bool SortedBag::isEmpty() const {
	return totalElements == 0;
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

SortedBagIterator SortedBag::iterator() {
	return SortedBagIterator(*this);
}
// Complexity Best case: theta(1) Worst case: theta(1) Total: theta(1)

SortedBag::~SortedBag() {
	for (int i = 0; i < capacity; ++i) {
		Node* current = table[i];
		while (current) {
			Node* temp = current;
			current = current->next;
			delete temp;
		}
	}
	delete[] table;
}
// Complexity Best case: theta(capacity) Worst case: theta(capacity) Total: theta(capacity)

