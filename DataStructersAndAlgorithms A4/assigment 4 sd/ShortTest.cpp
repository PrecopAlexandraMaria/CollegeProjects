#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

	//Test addAll
	SortedBag sb2(relation1);
	sb2.add(1);
	sb2.add(2);
	sb2.add(3);
	sb2.add(4);
	sb2.add(5);

	assert(sb2.size() == 5);

	SortedBagIterator it2 = sb2.iterator();
	
	SortedBag sb3(relation1);
	sb3.add(6);
	sb3.add(7);

	assert(sb3.size() == 2);
	it2.addAll(sb3);
	assert(sb2.size() == 7);
}

