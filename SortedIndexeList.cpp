#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	this->relation = r;
	this->len = 0;
	this->root = NULL;
}
//Theta(1)


int SortedIndexedList::size() const {
	return this->len;
}
//Theta(1)

bool SortedIndexedList::isEmpty() const {
	if (this->size() == 0)
		return true;
	else
	return false;
}
//Theta(1)

TComp SortedIndexedList::getElement(int i) const{
	ListIterator it{ *this };
	if (i <0 or i>it.list_nodes.size() - 1)
	{
		throw exception();
	}
	while (it.index != i)
	{
		it.next();
	}
	return it.getCurrent();
}
//Theta(i)

TComp SortedIndexedList::remove(int i) {
	ListIterator it{ *this };
	it.first();
	Node* actual = new Node;
	Node* previous = new Node;
	previous = this->root;
	actual = this->root;
	TComp elem;
	elem = this->getElement(i);
	if (i<0 or i>it.list_nodes.size() - 1)
	{
		throw exception();
	}
	else
	{
		if (this->search(elem) == -1)
			throw exception();
		else
		{
			if (this->size() == 1)
			{
				this->root = NULL;
				this->len--;
				return elem;
			}
			while (actual != NULL) //finding
			{
				if (actual->info == elem)
				{
					break;
				}
				else
				{
					if (this->relation(actual->info, elem) == true)
					{
						previous = actual;
						actual = actual->right;
					}
					else
					{
						previous = actual;
						actual = actual->left;
					}
				}

			}
			if (actual->left == NULL and actual->right == NULL)   //no childs => just delete it
			{
				if (this->relation(actual->info, previous->info) == true)
				{
					previous->left = NULL;
					this->len--;
					return actual->info;
				}
				else
				{
					previous->right = NULL;
					this->len--;
					return actual->info;
				}

			}
			else
			{
				if (actual->left == NULL)   //one child => move the child up 
				{
					Node newnode;
					newnode.info = actual->info;
					actual->info = actual->right->info;
					actual->left = NULL;
					actual->right = actual->right->right;
					this->len--;
					return newnode.info;
				}
				else
				{
					if (actual->right == NULL)
					{
						Node newnode;
						newnode.info = actual->info;
						actual->info = actual->left->info;
						actual->right = NULL;
						actual->left = actual->left->left;
						this->len--;
						return newnode.info;
					}
					else
					{
							// 2 childs 


						Node* minimum = new Node;
						previous = actual;
						minimum = actual->right;

						while (minimum->left != NULL)
						{
							previous = minimum;
							minimum = minimum->left;
						}
						//						std::swap(actual->left, maximum->left);
						//						std::swap(actual->right, maximum->right);
						std::swap(actual->info, minimum->info);        

						//minmum= min of the right tree of actual
						//actual=the node to be deleted
						//previous= parent of minimum

						//and again delete the minimum node properly(it cant have 2 childrens)

						if (minimum->left == NULL and minimum->right == NULL)
						{
							if (previous == actual)
							{
								previous->right = NULL;
								this->len--;
								return minimum->info;
							}
								previous->left = NULL;
							
							this->len--;
							return minimum->info;
						}
						else
						{
							if (minimum->left == NULL)
							{
								Node newnode;
								newnode.info = minimum->info;
								minimum->info = minimum->right->info;
								minimum->left = NULL;
								minimum->right = minimum->right->right;
								this->len--;
								return newnode.info;
							}
							else
							{
								if (minimum->right == NULL)
								{
									Node newnode;
									newnode.info = minimum->info;
									minimum->info = minimum->left->info;
									minimum->right = NULL;
									minimum->left = minimum->left->left;
									this->len--;
									return newnode.info;
								}
							}

						}
					}
				}
			}
		}

	}
}
//O(log n)

int SortedIndexedList::search(TComp e) const {
	ListIterator it{ *this };
	it.first();
	while (it.valid())
	{
		if (it.getCurrent() == e)
			return it.index;
		it.next();
	}
	return -1;

	/*Node* actual = new Node;
	actual = this->root;
	ListIterator it{ *this };
	bool found=false;

	if (this->root == NULL)
	{
		return -1;
	}
	else
	{
		while (actual != NULL)
		{
			if (actual->info == e)
			{
				found = true;
				break;
			}
			else
			{
				if (this->relation(actual->info, e) == true)
				{
					actual = actual->right;
				}
				else
				{
					actual = actual->left;
				}
			}

		}
		if (found == true)
		{
			for (int i = 0; i < it.list_nodes.size(); i++)
				if (it.list_nodes[i].info == e)
					return i;
		}
		else
			return -1;

	}*/
}
//O(n)

void SortedIndexedList::add(TComp e) {
	Node* actual = new Node;
	actual = this->root;
	Node* previous = new Node;
	previous = NULL;
	if (this->root == NULL)  //first node
	{
		Node* inserted = new Node;
		inserted->info = e;
		inserted->left = NULL;
		inserted->right = NULL;
		this->root = inserted;
		this->len++;
	}
	else
	{
		while (true)
		{
			if (actual == NULL)   //if the relation is true go left otherwise go right if its null add it to that position(save the previous)
			{
				Node* inserted = new Node;
				inserted->info = e;
				inserted->left = NULL;
				inserted->right = NULL;
				this->len++;
				if (this->relation(inserted->info, previous->info) == true) 
				{
					previous->left = inserted;
				}
				else
				{
					previous->right = inserted;
				}
				break;
			}
			if (this->relation(actual->info,e)==true)
			{
				previous = actual;
				actual = actual->right;
			}
			else
			{
				previous = actual;
				actual = actual->left;

			}

		}
	}
}
//O(log n)

int SortedIndexedList::removeALL(SortedIndexedList& list)
{
	int k = 0;
	int removed = 0;
	ListIterator it{ list };
	while (it.valid())
	{
		k=this->search(it.getCurrent());
		if (k != -1)
		{
			this->remove(k);
			removed++;
		}
		it.next();
	}
	return removed;
}
//O(m * log n)
ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}
//Theta(1)

