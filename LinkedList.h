#pragma once 

#include <iostream> //display contents of nodes

using namespace std;

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:		2
 * FILE:			LinkedList.h
 * PURPOSE: 		Node and linear doubly linked list
 *					class templates
 */

template<typename T>
class Node
{
	public:
		Node(void);
 		Node(const T& new_data);
		Node<T>(Node<T>& src);
		Node<T>& operator=(Node<T>& rhs);
		~Node(void);

		//getters, setters; self explanatory
		Node<T>*& get_next(void);
		Node<T>* get_next(void) const;
		Node<T>*& get_prev(void);
		Node<T>* get_prev(void) const;
		T& get_data(void) const;
		T*& get_data_ptr(void);
		T* get_data_ptr(void) const;
		void set_next(Node<T>* n);
		void set_prev(Node<T>* n);
		void set_data(const T& new_data);
	private:
		Node* prev;
		Node* next;
		T* data;
};

//linear doubly linked list
template<typename T>
class LLL
{
	public:
		LLL(void);
		~LLL(void);
		LLL(const LLL& src);
		const LLL& operator=(const LLL& rhs);

		bool is_empty(void) const; //returns whether list has nodes
		size_t length(void) const; //returns size of list
		T& at(size_t index) const; //throws std::outofbounds if index is "
		void push_back(const T& new_data); //adds to back of list
		void insert_sorted(const T& new_data); //inserts into list using operator< on node.data
		T* lookup(const T& key) const; //returns null if not found
		bool remove(const T& to_remove); //returns whether successful
		void display(bool indices=false) const; //displays all node contents
	private:
		Node<T>* head;
		Node<T>* tail;

		size_t count_nodes(Node<T>* list) const; //called by length(); counts nodes
		T& find_at_index(Node<T>* list, size_t index) const; //called by at()
		//called by copy constructor
		void copy_all(Node<T>* src, Node<T>*& dest, Node<T>*& dest_tail, Node<T>* last_dest);
		void remove_all(Node<T>* to_del); //called by destructor
		void push_back(Node<T>* list, Node<T>* new_node); //called by public push_back()
		void insert_sorted(Node<T>* list, Node<T>* new_node); //called by public insert_sorted()
		Node<T>* find_node(Node<T>* list, const T& key) const; //called by lookup()
		void remove_node(Node<T>* to_del); //called by remove(), remove_all()
		//called by public display
		void display(Node<T>* list, size_t this_index, bool indices=false) const;
};

#include "LinkedList.tpp" //or else linker errors
