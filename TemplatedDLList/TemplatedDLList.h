// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList() : header(T()), trailer(T()) { //default constructor
    header.next = &trailer;
    trailer.prev = &header;
  }

  DLList(const DLList<T>& dll) : header(T()), trailer(T()) { //COPY CONSTRUCTOR
    header.next = &trailer;
    trailer.prev = &header;
  	DLListNode<T>* curr = dll.first_node();
  	while(curr != dll.after_last_node()) {
  		DLListNode<T>* n = new DLListNode<T>(curr->obj, trailer.prev, &trailer);
  		if (header.next == nullptr && trailer.prev == nullptr) { // starting the linked list
  			header.next = n;
  			trailer.prev = n;
  		}
  		else { // adding to the tail
        trailer.prev->next = n;
        n->prev = trailer.prev;
        trailer.prev = n;
  		}
  		curr = curr->next;
  	}
  }

  DLList(DLList<T>&& dll) {  // move constructor
    if (dll.is_empty()) {
      header.next = &dll.header;
      trailer.prev = &dll.trailer;
      dll.header.next = &trailer;
      dll.trailer.prev = &header;

    }
    header.next = dll.header.next;
    trailer.prev = dll.trailer.prev;
    header.next->prev = &header;
    trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }

  ~DLList() { // destructor
    DLListNode<T>* Temp;
    DLListNode<T>* curr = first_node();
  	while (curr != &trailer) {
    	Temp = curr->next;
    	delete curr;
    	curr = Temp;
    }
    header.next = &trailer;
    trailer.prev = &header;
  }

  DLList<T>& operator=(const DLList<T>& dll) { //COPY assignment
    header = 0;
    trailer = 0;
    if (this != &dll) {
      if (!is_empty()) {
    this->header.next = &trailer;
    this->trailer.prev = &header;
  	DLListNode<T>* curr = dll.first_node();
  	while(curr != dll.after_last_node()) {
  		DLListNode<T>* n = new DLListNode<T>(curr->obj, this->trailer.prev, &trailer);
  		if (header.next == nullptr && trailer.prev == nullptr) { // starting the linked list
  			this->header.next = n;
  			this->trailer.prev = n;
  		}
  		else { // adding to the tail
        this->trailer.prev->next = n;
        n->prev = this->trailer.prev;
        this->trailer.prev = n;
  		}
  		curr = curr->next;
  	}
  }
  }
    return *this;
  }

  DLList<T>& operator=(DLList<T>&& dll) { // move assignment operator
    if (dll.is_empty()) {
      if (!this->is_empty()) {
        this->~DLList();
      }
      header.next = &dll.header;
      trailer.prev = &dll.trailer;
      dll.header.next = &trailer;
      dll.trailer.prev = &header;
    }
      header.next = dll.header.next;
      trailer.prev = dll.trailer.prev;
      header.next->prev = &header;
      trailer.prev->next = &trailer;

      dll.header.next = &dll.trailer;
      dll.trailer.prev = &dll.header;
      return *this;
  }

  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; }

  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }

  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }

  T first() const { // return the first object
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    return header.next->obj;
  }

  T last() const { // return the last object
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    return trailer.prev->obj;
  }

  void insert_first(T obj) { // insert to the first node
    DLListNode<T>* n = new DLListNode<T>(obj, &header, header.next);
    header.next->prev = n;
    header.next = n;
  }

  T remove_first() { // remove the first node
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    DLListNode<T>* n = header.next;
    n->next->prev = &header;
    header.next = n->next;
    T object = n->obj;
    delete n;
    return object;
  }

  void insert_last(T obj) { // insert to the last node
    DLListNode<T>* n = new DLListNode<T>(obj, trailer.prev, &trailer);
    trailer.prev->next = n;
    trailer.prev = n;
  }

  T remove_last() { // remove the last node
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    DLListNode<T>* n = trailer.prev;
    n->prev->next = &trailer;
    trailer.prev = n->prev;
    T object = n->obj;
    delete n;
    return object;

  }

  void insert_after(DLListNode<T> &p, T obj) {
    DLListNode<T>* n = new DLListNode<T>(obj, p.next->prev, p.next);
    n->prev->next = n;
    n->next->prev = n;
  }

  void insert_before(DLListNode<T> &p, T obj) {
    DLListNode<T>* n = new DLListNode<T>(obj, p.prev, p.next->prev);
    n->prev->next = n;
    n->next->prev = n;
  }

  T remove_after(DLListNode<T> &p) {
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    if (p.next == &trailer) {
      throw "ERROR: Remove Called on a Trailer.";
    }
    DLListNode<T>* curr = header.next;
    while (curr->obj != p.obj) {
      curr = curr->next;
    }
    curr = curr->next;
    T object = curr->obj;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    return object;

  }

  T remove_before(DLListNode<T> &p) {
    if (is_empty()) {
      throw "ERROR: Empty Doubly Linked List";
    }
    if (p.prev == &header) {
      throw "ERROR: Remove Called on a Header.";
    }
    DLListNode<T>* curr = header.next;
    while (curr->obj != p.obj) {
      curr = curr->next;
    }
    curr = curr->prev;
    T object = curr->obj;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    return object;

  }

};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll) {
  if (dll.is_empty()) {
    out << "Empty list." << endl;
  }
  else {
  DLListNode<T>* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    out << curr->obj << ", ";
    curr = curr->next;
  }
}
return out;
}


#endif
