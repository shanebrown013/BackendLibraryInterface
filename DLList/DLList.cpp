// implementation of the DLList class

#include "DLList.h"

DLList::DLList() : header(0), trailer(0) {
  header.next = &trailer;
  trailer.prev = &header;
}

DLList::DLList(const DLList& dll) : header(0), trailer(0) { //COPY CONSTRUCTOR
  header.next = &trailer;
  trailer.prev = &header;
	DLListNode* curr = dll.first_node();
	while(curr != dll.after_last_node()) {
		DLListNode* n = new DLListNode(curr->obj, trailer.prev, &trailer);
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

DLList::DLList(DLList&& dll) {  // move constructor
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

DLList::~DLList() { // destructor
  DLListNode* Temp;
  DLListNode* curr = first_node();
	while (!is_empty()) {
  	// Temp = curr->next;
    remove_first();
  	// delete curr;

  	// curr = Temp;
    // Temp = curr->next;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

DLList& DLList::operator=(const DLList& dll) { //COPY assignment
  header = 0;
  trailer = 0;
  if (this != &dll) {
    if (!is_empty()) {
  this->header.next = &trailer;
  this->trailer.prev = &header;
	DLListNode* curr = dll.first_node();
	while(curr != dll.after_last_node()) {
		DLListNode* n = new DLListNode(curr->obj, this->trailer.prev, &trailer);
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

DLList& DLList::operator=(DLList&& dll) {// move assignment operator
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

// return the pointer to the first node (header's next)
DLListNode* DLList::first_node() const {
  return header.next;
}

// return the pointer to the trailer
const DLListNode* DLList::after_last_node() const {
  return &trailer;
}

// return if the list is empty
bool DLList::is_empty() const {
  if (header.next == &trailer) {
    return true;
  }
  return false;
}

int DLList::first() const { // return the first object
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  return header.next->obj;
}

int DLList::last() const { // return the last object
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  return trailer.prev->obj;
}

void DLList::insert_first(int obj) { // insert to the first node
  DLListNode* n = new DLListNode(obj, &header, header.next);
  header.next->prev = n;
  header.next = n;
}

int DLList::remove_first() { // remove the first node
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  DLListNode* n = header.next;
  n->next->prev = &header;
  header.next = n->next;
  int object = n->obj;
  delete n;
  return object;
}

void DLList::insert_last(int obj) { // insert to the last node
  DLListNode* n = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = n;
  trailer.prev = n;
}

int DLList::remove_last() { // remove the last node
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  DLListNode* n = trailer.prev;
  n->prev->next = &trailer;
  trailer.prev = n->prev;
  int object = n->obj;
  delete n;
  return object;

}

void DLList::insert_after(DLListNode &p, int obj) {
  DLListNode* n = new DLListNode(obj, p.next->prev, p.next);
  n->prev->next = n;
  n->next->prev = n;
}

void DLList::insert_before(DLListNode &p, int obj) {
  DLListNode* n = new DLListNode(obj, p.prev, p.next->prev);
  n->prev->next = n;
  n->next->prev = n;
}

int DLList::remove_after(DLListNode &p) {
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  if (p.next == &trailer) {
    throw "ERROR: Remove Called on a Trailer.";
  }
  DLListNode* curr = header.next;
  while (curr->obj != p.obj) {
    curr = curr->next;
  }
  curr = curr->next;
  int object = curr->obj;
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  delete curr;
  return object;

}

int DLList::remove_before(DLListNode &p) {
  if (is_empty()) {
    throw "ERROR: Empty Doubly Linked List";
  }
  if (p.prev == &header) {
    throw "ERROR: Remove Called on a Header.";
  }
  DLListNode* curr = header.next;
  while (curr->obj != p.obj) {
    curr = curr->next;
  }
  curr = curr->prev;
  int object = curr->obj;
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  delete curr;
  return object;

}

ostream& operator<<(ostream& out, const DLList& dll) {
  if (dll.is_empty()) {
    out << "Empty list." << endl;
  }
  else {
  DLListNode* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    out << curr->obj << ", ";
    curr = curr->next;
  }
}
return out;
}
