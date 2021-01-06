#include "Library.h"
#include "TemplatedDLList.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <fstream>

using namespace std;

//Searches for a title in the database and returns vector of matching records
vector<Record> Library::search(string title) {
  vector<Record> vect;
  Record rec;
  string one, two, three, four, five;
  char firstLetter = title.at(0);
  firstLetter = toupper(firstLetter);
  int index = (int)firstLetter;
  index = index - 65;
  DLListNode<Record>* curr = book_db.at(index).first_node();
  cout << curr->obj.get_title() << endl;
    while (curr != book_db.at(index).after_last_node()) {
      if (title == curr->obj.get_title()) {
        one = curr->obj.get_title();
        two = curr->obj.get_author();
        three = curr->obj.get_ISBN();
        four = curr->obj.get_year();
        five = curr->obj.get_edition();
        rec.set_title(one);
        rec.set_author(two);
        rec.set_ISBN(three);
        rec.set_year(four);
        rec.set_edition(five);
        vect.push_back(rec);
      }
      curr = curr->next;
    }
  return vect;
}

//Imports records from a file.  Does not import duplicates.
// Return the number of records added to the database
int Library::import_database(string filename) {
  ifstream inFS;
  inFS.open(filename);
  if (!inFS.is_open()) {
    cout << "Error: File could not open." <<  endl;
    return 1;
  }
  ifstream innFS;
  innFS.open(filename);
  int count = 0;
  Record rec;
  Record recTemp;

  while (innFS >> recTemp) {
    string one, two, three, four, five;
    inFS >> ws; // skips the white space when using getline
    getline(inFS, one);
    getline(inFS, two);
    getline(inFS, three);
    getline(inFS, four);
    getline(inFS, five);
    rec.set_title(one);
    rec.set_author(two);
    rec.set_ISBN(three);
    rec.set_year(four);
    rec.set_edition(five);
    string bookTitle = rec.get_title();
    char firstLetter = bookTitle.at(0);
    firstLetter = toupper(firstLetter);
    int index = (int)firstLetter;
    index = index - 65;
    book_db.at(index).insert_last(rec);
    count++;
  }
return count;
}

//Exports the current database to a file
//Return the number of records exported
int Library::export_database(string filename) {
  ofstream onFS;
  onFS.open(filename);
  if (!onFS.is_open()) {
    cout << "Error: File could not open." << endl;
  }

  int count = 0;
  for (int i = 0; i < book_db.size(); i++) {
    DLListNode<Record>* curr = book_db.at(i).first_node();
    while (curr != book_db.at(i).after_last_node()) {
      onFS << curr->obj.get_title() << endl;
      onFS << curr->obj.get_author() << endl;
      onFS << curr->obj.get_ISBN() << endl;
      onFS << curr->obj.get_year() << endl;
      onFS << curr->obj.get_edition() << endl << endl;
      curr = curr->next;
      count++;
    }
  }
  return count;
}

void Library::print_database() {
  for (int i = 0; i < book_db.size(); i++) {
    DLListNode<Record>* curr = book_db.at(i).first_node();
    while (curr != book_db.at(i).after_last_node()) {
      cout << curr->obj.get_title() << endl;
      cout << curr->obj.get_author() << endl;
      cout << curr->obj.get_ISBN() << endl;
      cout << curr->obj.get_year() << endl;
      cout << curr->obj.get_edition() << endl << endl;
      curr = curr->next;
    }
  }
}

//add record to database, avoid complete duplicates
bool Library::add_record(Record book) {
  string bookTitle = book.get_title();
  char firstLetter = bookTitle.at(0);
  firstLetter = toupper(firstLetter);
  int index = (int)firstLetter;
  index = index - 65;
  // insert book
  DLListNode<Record>* curr = book_db.at(index).first_node();
  bool checkIfExists = false;
  while (curr != book_db.at(index).after_last_node()) {     // Check if book is already in
    if (book == curr->obj) {
      checkIfExists = true;
    }
    curr = curr->next;
  }
  if (checkIfExists == true) {
    return false;
  }
  else {
    book_db.at(index).insert_last(book);
    return true;
  }

}

//Deletes a record from the database
void Library::remove_record(Record book) {
  for (int i = 0; i < book_db.size(); i++) {
    DLListNode<Record>* curr = book_db.at(i).first_node();
    if (book == curr->obj) {
      book_db.erase(book_db.begin() + i, book_db.begin() + (i+1));
    }
    curr = curr->next;
  }
}

//Prompts user for yes or no and returns choice Y or N
char Library::prompt_yes_no() {
  string answer = "";
  cin >> answer;
  if (answer == "Y" || answer == "yes" || answer == "y" || answer == "Yes") {
    return 'Y';
  }
  else if (answer == "N" || answer == "no" || answer == "n" || answer == "No") {
    return 'N';
  }
  else {
    cout << "Error: wrong input, try again." << endl;
    prompt_yes_no();
  }

}

//Given a vector of menu options returns index of choice
int Library::prompt_menu(vector<string> vect) {
  int numChoice;
  cout << "Please select an option:" << endl;
  for (int i = 0; i < vect.size(); i++) {
    cout << i+1 << ". " << vect.at(i) << endl;
  }
  cout << "Enter number: ";
  cin >> numChoice;

  return (numChoice - 1);
}

//Prompts user for a new record
Record Library::prompt_record() {
  string one, two, three, four, five;
  Record recNew;
  cin.ignore();
  cout << "Enter the title: ";
  getline(cin, one);
  cout << "Enter the author: ";
  getline(cin, two);
  cout << "Enter the ISBN: ";
  getline(cin, three);
  cout << "Enter the year: ";
  getline(cin, four);
  cout << "Enter the edition: ";
  getline(cin, five);
  recNew.set_title(one);
  recNew.set_author(two);
  recNew.set_ISBN(three);
  recNew.set_year(four);
  recNew.set_edition(five);

  return recNew;
}

//Prompt for a valid title
string Library::prompt_title() {
  string userTitle = "";
  cout << "Enter a title: ";
  getline(cin, userTitle);

  return userTitle;
}

// Prompt for a valid string
string Library::prompt_string(string prompt) {
  string userString = "";
  cout << "Enter a string for the " << prompt << ": ";
  getline(cin, userString);

  return userString;
}
