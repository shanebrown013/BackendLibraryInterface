//implementation of record class

#include "Record.h"
#include <string>
#include <iostream>

using namespace std;

string Record::get_title() const {
  return title;
}

string Record::get_ISBN() const {
  return ISBN;
}

string Record::get_author() const {
  return author;
}

string Record::get_year() const {
  return year;
}

string Record::get_edition() const {
  return edition;
}

void Record::set_title(string _title) {
  title = _title;
}

void Record::set_ISBN(string _ISBN) {
  ISBN = _ISBN;
}

void Record::set_author(string _author) {
  author = _author;
}

void Record::set_year(string _year) {
  year = _year;
}

void Record::set_edition(string _edition) {
  edition = _edition;
}

// Input operator
istream& operator>>(istream& is, Record& rec) {
  string one, two, three, four, five;
  is >> ws; // skips the white space when using getline
  getline(is, one);
  getline(is, two);
  getline(is, three);
  getline(is, four);
  getline(is, five);
  rec.set_title(one);
  rec.set_author(two);
  rec.set_ISBN(three);
  rec.set_year(four);
  rec.set_edition(five);
  return is;

}

// Output operator
ostream& operator<<(ostream& os, Record& rec) {
  os << rec.get_title() << endl;
  os << rec.get_author() <<endl;
  os << rec.get_ISBN() << endl;
  os << rec.get_year() << endl;
  os << rec.get_edition() << endl;

  return os;
}

// Comparison operators
bool operator==(const Record& r1, const Record& r2) {
  if (r1.get_title() == r2.get_title() && r1.get_author() == r2.get_author() && r1.get_ISBN() == r2.get_ISBN()) {
    return true;
  }
  return false;
}
