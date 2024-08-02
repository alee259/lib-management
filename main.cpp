#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "library.cpp"
using namespace std;

int main()
{
    lNode* library[3]; //library strucutre
    pNode* people[2]; //person data strucutre
    string filename, filename2; //filenames ofr library and person
    cout << "Enter library data filename: "; //input those filenames
    cin >> filename;
    cout << "Enter personnel data filename: ";
    cin >> filename2;

    makeLibrary(library, filename); //calling functions to make library and person linked lists and to fill in static arrays
    makePeople(people, filename2);
    
    char yn('n'); //if user wants to go again
    int choice(0); //which menu the user chooses
    do
    {
        cout << "-------------------------------\n"; //ui
        cout << "\t     Menu\n";
        cout << "-------------------------------\n";
        cout << "1. Search for book\n";
        cout << "2. Rent a book\n";
        cout << "3. Return a book\n";
        cout << "4. Show information\n";
        cout << "5. Show all books\n";
        cout << "6. Exit\n\n";

        cout << "Select 1-6: "; //io for choice
        cin >> choice;

        switch (choice) //switch to direct user choice into correct function
        {
        case 1:
            menuOne(library);
            break;
        case 2:
            menuTwo(library, people);
            break;
        case 3:
            menuThree(library, people);
            break;
        case 4:
            menuFour(people, library);
            break;
        case 5:
            menuFive(library);
            break;
        case 6:
            cout << "Exiting...";
            exit(0);
            break;

        default:
            break;
        }

        cout << "\nAgain? (y/n) ";
        cin >> yn;

    } while (yn == 'y');


    deleteLLists(library, people); //delete all our linked lists

}