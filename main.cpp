#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Contact.h"
#include "ContactList.h"

using namespace std;

void displayMenu() { 
  cout << "\n\n********************************************" << endl
        << "Main Menu\n" << endl
        << "Enter the letter for the desired menu option:" << endl
        << "   C - Get count" << endl
        << "   L - Load contacts from file" << endl
        << "   S - Search contacts" << endl
        << "   P - Print contacts" << endl
        << "   X - Exit\n" << endl;
}
 
void contactMenu() { 
  cout << "Enter an option for contact:" << endl
        << "   A - Edit address" << endl
        << "   B - Edit date of birth" << endl
        << "   E - Edit email address" << endl
        << "   N - Edit name" << endl
        << "   P - Edit phone numbers" << endl
        << "   R - Return to main menu" << endl
        << "   D - Delete\n" << endl;
}

char getChoice() { 
  char userChoice;
  cin >> userChoice;
  return toupper(userChoice);  
}

void displayContactCount(ContactList& list) { 
  cout << "There are " << list.getCount() << " contacts" << endl;
}
 
void loadContactsFromFile(ContactList& list) { 
  string filename;
  cout << "Enter a filename: " << endl;
  cin >> filename;
  
  if (list.loadContactsFromFile(filename)) {
    cout << "Contacts successfully loaded." << endl;
  } else {
    cout << "Failed to load contacts from file." << endl;
  }
}

void searchContacts(ContactList& list) {
  string searchTerm;
  string userChoice;
  char contactChoice;
  int index;
  vector<int> validSearchResults;
  
  cout << "Enter a search term:" << endl;
  cin >> searchTerm;
  
  validSearchResults = list.findContactsByName(searchTerm);
  
  if (validSearchResults.empty()) {
    cout << "No results found." << endl;
    return;
  }
  
  cout << "Found " << validSearchResults.size() << " result(s):" << endl;
  
  for (int i = 0; i < validSearchResults.size(); i++) { 
    index = validSearchResults.at(i);
    cout << (i+1) << ". " << list.getContact(index)->getName() << endl;
  }

  cout << "\nEnter an option:" << endl
       << "   P - Print contacts" << endl
       << "   or a Contact number to view/edit" << endl
       << "   R - Return to main menu\n" << endl;

  cin >> userChoice;

  if (userChoice == "R" || userChoice == "r") {  
    return;
  }
  
  if (userChoice == "P" || userChoice == "p") { 
    list.printContacts(validSearchResults);
    return;
  }
  
  try {
    index = stoi(userChoice) - 1;
  } catch (invalid_argument& e) {
    cout << "Invalid input. Please enter a valid contact number." << endl;
    return;
  }
  
  if (index < 0 || index >= validSearchResults.size()) {
    cout << "Invalid input. Please enter a valid contact number." << endl;
    return;
  }
  
  // Valid input, retrieve the contact from the list
  Contact* contact = list.getContact(validSearchResults[index]);

  // Display the contact's information
  cout << "\nName: " << contact->getName() << endl;
  cout << "Phone number: " << contact->getPhoneNumber() << endl;
  cout << "Email address: " << contact->getEmailAddress() << endl;
  cout << "Address: " << contact->getAddress() << endl;

  // Ask user if they want to update this contact's information
  cout << "\nDo you want to update this contact's information? (Y/N)" << endl;
  string updateChoice;
  cin >> updateChoice;

  // Check user's choice and update contact information if necessary
  if (updateChoice == "Y" || updateChoice == "y") {
    updateContactInformation(*contact);
  } else {
    cout << "\nReturning to main menu." << endl;
  }
}