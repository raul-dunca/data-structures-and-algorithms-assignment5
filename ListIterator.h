#pragma once
#include "SortedIndexedList.h"
#include <vector>

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	int index;
	std::vector<Node> list_nodes;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


