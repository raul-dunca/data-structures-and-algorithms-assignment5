#include <assert.h>

#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());

    list.add(10);
    list.add(7);
    list.add(8);
    list.add(12);
    list.add(10);
    list.add(10);
    

   // assert(list.search(6) == 0);
   // assert(list.search(7) == 1);
    //assert(list.search(10) == 2);
    //assert(list.search(12) == 3);

   
    ListIterator li = list.iterator();
    while (li.valid()) {
        TComp current = li.getCurrent();
        li.next();
    }
   
   
    assert(list.remove(2) == 10);
    li.first();
    while (li.valid()) {
        TComp current = li.getCurrent();
        li.next();
    }
    assert(list.remove(2) == 10);
    assert(list.remove(2) == 10);
    
    li.first();
    while (li.valid()) {
        TComp current = li.getCurrent();
        li.next();
    }
    assert(list.remove(0) == 7);
    assert(list.remove(0) == 8);
    assert(list.remove(0) == 12);
    li.first();
    while (li.valid()) {
        TComp current = li.getCurrent();
        li.next();
    }









    SortedIndexedList list1 = SortedIndexedList(relation1);
    SortedIndexedList list2 = SortedIndexedList(relation1);

    list2.add(10);
    list2.add(7);
    list2.add(8);
    list2.add(50);

    list1.add(10);
    list1.add(7);
    list1.add(8);
    list1.add(6);
    list1.add(12);
    assert(list1.removeALL(list2)==3);
    

    ListIterator li2 = list1.iterator();

    li2.first();
    while (li2.valid()) {
        TComp current1 = li2.getCurrent();
        li2.next();
    }
}

