#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;


//IF THE RELATION IS DIFF DO RIGHT TRAVERSAL (THE SAME SWITCH RIGHT AND LEFT)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->index = 0;
	Node* current = new Node;
	
	vector<Node> stack;
	current = this->list.root; //inorder traversal
	while (current != NULL)
	{
		stack.push_back(*current);
		current = current->left;
	}
	while (stack.size() != 0)
	{

		current = &stack[stack.size() - 1];
		stack.pop_back();
		this->list_nodes.push_back(*current);
		current = current->right;
		while (current != NULL)
		{
			stack.push_back(*current);
			current = current->left;
		}
	}
}
//Theta(n)


void ListIterator::first(){
	this->list_nodes.clear();
	this->index = 0;
	Node* current = new Node;
	Node n;
	vector<Node> stack;
	current = this->list.root;
	while (current != NULL)
	{
		stack.push_back(*current);
		current = current->left;
	}
	while (stack.size() != 0)
	{

		current = &stack[stack.size() - 1];
		stack.pop_back();
		this->list_nodes.push_back(*current);
		current = current->right;
		while (current != NULL)
		{
			stack.push_back(*current);
			current = current->left;
		}
	}
}
//Theta(n)

void ListIterator::next(){
	//if (this->index <0 or this->index>this->list_nodes.size() - 2)
	if (!this->valid())
		throw exception();
	else
	this->index++;
}
//Theta(1)

bool ListIterator::valid() const{
	if (this->list.isEmpty() == true)
		return false;
	if (this->index <0 or this->index>this->list_nodes.size()-1)
		return false;
	return true;
}
//Theta(1)

TComp ListIterator::getCurrent() const{
	if (this->valid())
		return this->list_nodes[this->index].info;
	else
		throw exception();
}
//Theta(1)

