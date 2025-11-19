#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->capacity = 10;
    this->nodes = new DLLANode[capacity];
    this->rel = r;
    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->totalElements = 0;

    for (int i = 0; i < capacity - 1; ++i) {
        nodes[i].next = i + 1;
    }
    nodes[capacity - 1].next = -1;
}
//Complexity BC = theta(n), WC = theta(n), Total = theta(n)

void SortedBag::resize() {
	// Resize the array of nodes to double its current capacity

    int newCapacity = 2 * capacity;
	DLLANode* newNodes = new DLLANode[newCapacity]; // allocate new memory

    for (int i = 0; i < capacity; ++i) {
		newNodes[i] = nodes[i]; // copy existing nodes
    }

    for (int i = capacity; i < newCapacity - 1; ++i) {
		newNodes[i].next = i + 1; // link new nodes
    }

	newNodes[newCapacity - 1].next = -1; // last node points to -1
	delete[] nodes; // free old memory
    nodes = newNodes;
    firstEmpty = capacity;
    capacity = newCapacity;
}
// Complexity BC = theta(n), WC = theta(n), Total = theta(n)

int SortedBag::allocate() {
    //return the position of the first empty, if there are no empty, resize
    if (firstEmpty == -1) {
		resize();
    }

    int newElem = firstEmpty;
    firstEmpty = nodes[firstEmpty].next;
    return newElem;
}
// Complexity BC = theta(1), WC = theta(n), Total = O(n)

void SortedBag::free(int pos) {
	// Free a node and add it back to the free list

    nodes[pos].next = firstEmpty;
    firstEmpty = pos;
}
// Complexity BC = theta(1), WC = theta(1), Total = theta(1)

void SortedBag::add(TComp e) {
	// Check if the element already exists in the bag

    int current = head;
    while (current != -1 && nodes[current].info != e) {
        current = nodes[current].next;
    }

	// If the element already exists, increment its frequency
    if (current != -1) {
        nodes[current].frequency++;
    }
    else {

		// If the element does not exist, create a new node
        int newNode = allocate();
        nodes[newNode].info = e;
        nodes[newNode].frequency = 1;
        nodes[newNode].next = -1;
        nodes[newNode].prev = -1;

		if (head == -1) { 
            // if the bag is empty set head and tail to the new node

            head = tail = newNode;
        }
		else if (!rel(nodes[head].info, e)) { 
            // if the new element is smaller than the head set it as the new head

            nodes[newNode].next = head;
            nodes[head].prev = newNode;
            head = newNode;
        }
		else { 
            // if the new element is larger than the head, find the correct position to insert it

            int current = head;
            while (current != -1 && rel(nodes[current].info, e)) {
                current = nodes[current].next;
            }
			if (current == -1) { 
                // if the new element is larger than all elements, set it as the new tail

                nodes[tail].next = newNode;
                nodes[newNode].prev = tail;
                tail = newNode;
            }
            else {
                int prev = nodes[current].prev;
                nodes[newNode].next = current;
                nodes[newNode].prev = prev;
                if (prev != -1) nodes[prev].next = newNode;
                nodes[current].prev = newNode;
                if (current == head) head = newNode;
            }
        }
    }
    totalElements++;
}
// Complexity BC=theta(1) WC=theta(n) Total=O(n)

bool SortedBag::remove(TComp e) {
	// Check if the element exists in the bag
    int current = head;
    while (current != -1 && nodes[current].info != e) {
        current = nodes[current].next;
    }

	// If the element does not exist, return false
    if (current == -1) return false;

    nodes[current].frequency--;
    totalElements--;

	// If the frequency of the element becomes zero, remove it from the list
    if (nodes[current].frequency == 0) {
        int prev = nodes[current].prev;
        int next = nodes[current].next;

        if (prev != -1) nodes[prev].next = next;
        else head = next;

        if (next != -1) nodes[next].prev = prev;
        else tail = prev;

        free(current);
    }

    return true;
}
// Complexity BC=theta(1) WC=theta(n) Total=O(n)

bool SortedBag::search(TComp e) const {
    int current = head;
    while (current != -1) {
        if (nodes[current].info == e) 
            return true;
        current = nodes[current].next;
    }
    return false;
}
// Complexity BC=theta(1) WC=theta(n) Total=O(n)

int SortedBag::nrOccurrences(TComp e) const {
    int current = head;
    while (current != -1) {
        if (nodes[current].info == e) 
            return nodes[current].frequency;
        current = nodes[current].next;
    }
    return 0;
}
// Complexity BC=theta(1) WC=theta(n) Total=O(n)


int SortedBag::size() const {
    return totalElements;
}
// Complexity BC=theta(1) WC=theta(1) Total=theta(1)

bool SortedBag::isEmpty() const {
    return totalElements == 0;
}
//Complexity BC=theta(1) WC=theta(1) Total=theta(1)

SortedBagIterator SortedBag::iterator() const{
    return SortedBagIterator(*this);
}
// Complexity BC=theta(1) WC=theta(1) Total=theta(1)

SortedBag::~SortedBag() {
	delete[] nodes;
}
// Complexity BC=theta(1) WC=theta(1) Total=theta(1)

int SortedBag::removeAllOccurences(TComp e) {
    //removes all occurences of a given element from SprtedBag
    //returns the number of elements removed

	int current = head;
	int count = 0;
	while (current != -1) {
		if (nodes[current].info == e) {
			count += 1;
			remove(e);
			current = head; // reset current to head after removing
		}
		
        current = nodes[current].next;
	}
	return count;
}