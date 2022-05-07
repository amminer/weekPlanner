#pragma once

#include "LinkedList.h"

/* Amelia Miner
 * 04/09/22
 * cs 202 section 003
 * program #: 1
 * file: LinkedList.cpp
 * PURPOSE: Node, linear linked list,
 *	and circular linked list class templates.
 */

/*								NODE								*/
//		constructors, destructors, op overloads, and their helpers
template<typename T>
Node<T>::Node(void)
	: prev(nullptr), next(nullptr), data(nullptr) {}

template<typename T>
Node<T>::Node(const T& new_data)
	: prev(nullptr), next(nullptr), data(nullptr)
{ set_data(new_data); } //using helper may not be necessary?
template<typename T>
void Node<T>::set_data(const T& new_data)
{
	if(data)
		delete data;
	data = new T{new_data};
	return;
}

template<typename T>
Node<T>::Node(Node<T>& src)
	: prev(src.prev), next(src.next), data(nullptr)
{
	*this = src;
}
template<typename T>
Node<T>& Node<T>::operator=(Node<T>& rhs)
{
	if (this != &rhs){
		set_data(rhs.get_data());
	}
	return *this; //in case of chained assignments
}

template<typename T>
Node<T>::~Node(void)
{
	if (data)
		delete data;
}

//				public member functions
template<typename T>
Node<T>*& Node<T>::get_next(void)
{ return next; }
template<typename T>
Node<T>* Node<T>::get_next(void) const
{ return next; }

template<typename T>
Node<T>*& Node<T>::get_prev(void)
{ return prev; }
template<typename T>
Node<T>* Node<T>::get_prev(void) const
{ return prev; }

template<typename T>
void Node<T>::set_next(Node* new_next)
{
	next = new_next;
	return;
}

template<typename T>
void Node<T>::set_prev(Node* new_prev)
{
	prev = new_prev;
	return;
}

template<typename T>
T& Node<T>::get_data(void) const
{ return *data; }

template<typename T>
T*& Node<T>::get_data_ptr(void)
{ return data; }
template<typename T>
T* Node<T>::get_data_ptr(void) const
{ return data; }

/*								LLL								*/
//		constructors, destructors, op overloads, and their helpers
template<typename T>
LLL<T>::LLL(void)
	: head(nullptr), tail(nullptr) {}

template<typename T>
LLL<T>::~LLL(void)
{ if (head) remove_all(head); }
template<typename T>
void LLL<T>::remove_all(Node<T>* to_del)
{
	auto next_del = to_del->get_next();
	delete to_del;
	if (next_del)
		remove_all(next_del);
}

template<typename T>
LLL<T>::LLL(const LLL<T>& src)
	: head(nullptr), tail(nullptr)
{
	*this = src;
}
template<typename T>
const LLL<T>& LLL<T>::operator=(const LLL<T>& rhs)
{
	if (&rhs != this)
		copy_all(rhs.head, head, tail, nullptr);
	return *this;
}

template<typename T>
void LLL<T>::copy_all(Node<T>* src, Node<T>*& dest, Node<T>*& dest_tail, Node<T>* last_dest)
{
	if (!src)
		return;
	else{
		dest = new Node<T>(*src);
		dest->set_prev(last_dest);
		dest_tail = dest;
		copy_all(src->get_next(), dest->get_next(), dest_tail, dest);
	}
}

//				public member functions & their private helpers
template<typename T>
bool LLL<T>::is_empty(void) const
{ return !head; }

template<typename T>
size_t LLL<T>::length(void) const
{ return count_nodes(head); }
template<typename T>
size_t LLL<T>::count_nodes(Node<T>* list) const
{
	if (list == tail)
		return 1;
	else
		return 1 + count_nodes(list->get_next());
}

template<typename T>
T& LLL<T>::at(size_t index) const
{
	if (index < (size_t)0 or index >= length())
		throw out_of_range("index out of bounds!");
	else
		return find_at_index(head, index);
}
template<typename T>
T& LLL<T>::find_at_index(Node<T>* list, size_t index) const
{
	if (index == (size_t)0)
		return list->get_data();
	else
		return find_at_index(list->get_next(), index-1);
}

template<typename T>
void LLL<T>::push_back(const T& new_data)
{
	Node<T>* new_node = new Node<T>(new_data);
	if (!head){
		head = new_node;
		tail = new_node;
	}
	else
		push_back(head, new_node);
}
template<typename T>
void LLL<T>::push_back(Node<T>* list, Node<T>* new_node)
{
	if (list == tail){
		list->set_next(new_node);
		new_node->set_prev(list);
		tail = new_node;
	}
	else
		push_back(list->get_next(), new_node);
}

template<typename T>
void LLL<T>::insert_sorted(const T& new_data)
{
	Node<T>* new_node = new Node<T>(new_data);
	if (!head){
		head = new_node;
		tail = new_node;
	}
	else
		insert_sorted(head, new_node);
}
template<typename T>
void LLL<T>::insert_sorted(Node<T>* list, Node<T>* new_node)
{
	//TODO testing
	//should maybe overload Node::operator< but this works
	if (new_node->get_data() < list->get_data()){ //insert before list
		if (list == head){							//case new head
			head = new_node;
		}
		else{										//case new sandwiched
			list->get_prev()->set_next(new_node);
		}
		new_node->set_next(list);	//both new head and new sandwiched
		list->set_prev(new_node);
	}
	else if (list == tail){ //insert after list;	  case new tail
		tail = new_node;
		list->set_next(new_node);
		new_node->set_prev(list);
	}
	else{ //recurse
		insert_sorted(list->get_next(), new_node);
	}
}

template<typename T>
T* LLL<T>::lookup(const T& key) const
{
	T* ret = nullptr;
	if (head)
		if (Node<T>* ret_node = find_node(head, key); ret_node)
			ret = ret_node->get_data_ptr();
	return ret;
}
template<typename T>
Node<T>* LLL<T>::find_node(Node<T>* list, const T& key) const
{
	if (list->get_data() == key)
		return list;
	else if (list == tail)
		return nullptr;
	else
		return find_node(list->get_next(), key);
}

template<typename T>
bool LLL<T>::remove(const T& to_remove)
{ 
	bool ret = false;
	if (head)
		if (Node<T>* found_node = find_node(head, to_remove); found_node){
			ret = true;
			remove_node(found_node);
		}
	return ret;
}
template<typename T>
void LLL<T>::remove_node(Node<T>* to_del)
{
	if (to_del == head){			//case (head, len>1) or (head, len=1)
		if (head != tail)			//subcase len>1
			head->set_prev(nullptr);
		else						//subcase len=1
			tail = nullptr;
		head = to_del->get_next();
	}
	else if (to_del == tail){		//case tail, len>1
		tail = to_del->get_prev();
		tail->set_next(nullptr);
	}
	else{							//case sandwiched, len>1
		if (to_del->get_next())	//next.prev = this.prev
			to_del->get_next()->set_prev(to_del->get_prev());
		if (to_del->get_prev()) //prev.next = this.next
			to_del->get_prev()->set_next(to_del->get_next());
	}
	delete to_del;					//all cases
}

template<typename T>
void LLL<T>::display(bool indices) const
{
	if (head)
		display(head, 0, indices);
}

template<typename T>
void LLL<T>::display(Node<T>* list, size_t this_index, bool indices) const
{
	if (!list)
		return;
	else{
		if (indices){
			cout << this_index+1 << ":\n";
		}
		cout << list->get_data() << '\n';
		display(list->get_next(), this_index+1, indices);
	}
}
