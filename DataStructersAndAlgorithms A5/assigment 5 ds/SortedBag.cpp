#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    root = nullptr;
    rel = r;
    nrElements = 0;
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)

SortedBag::BSTNode::BSTNode(TComp val) {
    //functie pentru initializarea unui nod al arborelui binar de cautare
    info = val;
    left = nullptr;
	right = nullptr;
} 

// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)

void SortedBag::add(TComp e) {
	//Creeaza un nod curent care va fi folosit pentru a gasi pozitia unde trebuie adaugat noul element
    BSTNode** current = &root;

	//Parcurgem bag-ul cat timp nodul curent nu este null
    while (*current != nullptr) {

		// Compararea elementului e cu valoarea nodului curent folosind relatia rel
        if (rel(e, (*current)->info)) {
			current = &((*current)->left); //daca e este mai mic decat valoarea nodului curent, mergem in subarborele stang
        }

		//altfel daca e este mai mare sau egal cu valoarea nodului curent, mergem in subarborele drept
        else {
            current = &((*current)->right);
        }
    }

	// Daca nodul curent este null, inseamna ca am gasit pozitia unde trebuie adaugat noul element
    *current = new BSTNode(e);
    nrElements++;
}
// Complexity Best case: θ(1), Worst case: θ(capacity), Total: O(capacity)

bool SortedBag::remove(TComp e) {
	
    // Creeaza un nod curent si un nod parinte pentru a gasi nodul de sters
    BSTNode** current = &root;
    BSTNode* toDelete = nullptr;
    
    while (*current != nullptr && (*current)->info != e) {
        if (rel(e, (*current)->info)) {
            current = &((*current)->left);
        } else {
            current = &((*current)->right);
        }
    }
    
    if (*current == nullptr) return false;
    toDelete = *current;
    
	// Cazul 1, daca nodul are doi copii, gasim nodul minim din subarborele drept si il inlocuim cu nodul de sters
    if (toDelete->left && toDelete->right) {
        BSTNode** minNode = &(toDelete->right);
        while ((*minNode)->left != nullptr) {
            minNode = &((*minNode)->left);
        }
        toDelete->info = (*minNode)->info;
        toDelete = *minNode;
        *minNode = (*minNode)->right;
    } 
	// Cazul 2, daca nodul are un singur copil sau nu are niciun copil il inlocuim cu copilul sau il stergem direct
    else {
        if (toDelete->left != nullptr) {
            *current = toDelete->left;
        }
        else {
            *current = toDelete->right;
        }
    }
    
    delete toDelete;
    nrElements--;
    return true;
}
// Complexity Best case: θ(1), Worst case: θ(capacity), Total: O(capacity)

bool SortedBag::search(TComp e) const {
	// Cauta nodul cu valoarea e in arborele binar de cautare
    BSTNode* current = root;

	// Daca nodul curent este null, inseamna ca valoarea nu a fost gasita
    while (current != nullptr) {

		// Daca valoarea curenta este egala cu valoarea cautata, returneaza true
        if (current->info == e)
            return true;

		// Daca valoarea cautata este mai mica decat valoarea curenta, cauta in subarborele stang, altfel cauta in subarborele drept
        if (rel(e, current->info))
            current = current->left;
        else
            current = current->right;
    }
    return false;
}
// Complexity Best case: θ(1), Worst case: θ(capacity), Total: O(capacity)

int SortedBag::nrOccurrencesRec(BSTNode* node, TComp e) const {
	// Daca nodul este null, returneaza 0 (nu exista elementul in arbore)
    if (node == nullptr)
        return 0;

	// Verifica daca valoarea curenta este egala cu valoarea cautata
    int count = (node->info == e) * 1;

	// Recursiv, cauta in subarborele stang si drept pentru a numara aparitiile valorii e
    return count + nrOccurrencesRec(node->left, e) + nrOccurrencesRec(node->right, e);
}
// Complexity Best case: θ(1), Worst case: θ(capacity), Total: O(capacity)

int SortedBag::nrOccurrences(TComp e) const {
	// Verifica daca arborele este gol
    return nrOccurrencesRec(root, e);
}
// Complexity Best case: θ(1), Worst case: θ(capacity), Total: O(capacity)

int SortedBag::size() const {
	// Returneaza numarul de elemente din arbore
    return nrElements;
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)


bool SortedBag::isEmpty() const {
	// Verifica daca numarul de elemente este 0
    return nrElements == 0;
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)


SortedBag::~SortedBag() {
	//verificam daca radacina este null, daca da, nu avem nimic de sters
    if (root == nullptr)
        return;

	// Folosim un stack pentru a parcurge arborele in mod iterativ si a elibera memoria
    std::stack<BSTNode*> nodeStack;
    nodeStack.push(root);

	// Parcurgem arborele in mod iterativ, adaugand nodurile in stack
    while (!nodeStack.empty()) {
        BSTNode* node = nodeStack.top();
        nodeStack.pop();

        if (node->left)
            nodeStack.push(node->left);
        if (node->right)
            nodeStack.push(node->right);

        delete node;
    }
}
// Complexity Best case: θ(1), Worst case: θ(n), Total: O(n)


SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}
// Complexity Best case: θ(1) Worst case: θ(1) Total: θ(1)

void SortedBag::intersection(const SortedBag& b) {
	//keeps only the elements which appear in b as well
	//if an element appears multiple times in both SortedBags, it will be kept the minimum number of times(if it appears 3 times in one SortedBag and 5 times in the other, 3 occurences will be kept)
	//both bags have the same relation

    // Daca bag-ul este gol, nu facem nimic
    if (root == nullptr) {
        return;
    }

	// Creeaza un array pentru a stoca elementele care trebuie pastrate
    TComp* elementsToKeep = new TComp[nrElements];
    int keepCount = 0;

	// iteram prin elementele din bag ul curent folosind un iterator
    SortedBagIterator it = this->iterator();
	
	// Iteram prin toate elementele din bag-ul curent
    while (it.valid()) {
        TComp elem = it.getCurrent();
        int countThis = nrOccurrences(elem);
        int countB = b.nrOccurrences(elem);
        int minCount = std::min(countThis, countB);

		// daca elementul apare in ambele bag-uri, il adaugam in array-ul elementsToKeep
        for (int i = 0; i < minCount; i++) {
            elementsToKeep[keepCount++] = elem;
        }

		// Avansam iteratorul la urmatorul element
        while (it.valid() && it.getCurrent() == elem) {
            it.next();
        }
    }

	// Eliberam memoria pentru arborele curent si resetam radacina si numarul de elemente
    this->~SortedBag();
    root = nullptr;
    nrElements = 0;

	// Adaugam elementele pastrate inapoi in bag-ul curent
    for (int i = 0; i < keepCount; i++) {
        add(elementsToKeep[i]);
    }

	// Eliberam memoria alocata pentru elementsToKeep
    delete[] elementsToKeep;
}
// Complexity Best case: θ(capacity), Worst case: θ(capacity^2), Total: O(capacity^2)