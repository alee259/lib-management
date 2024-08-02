#include "library.h"
using namespace std;

lNode* addLList(Book* book, int id, lNode* head) 
//this function is to add a node to one of the library linked lists, taking in the code of the book, the book data class itself, and the head of the list
{
    lNode* target = NULL; //the node we want to add
    lNode* ptr = NULL; //our current node
    lNode* prev =  NULL; //the previous node

    target = new lNode(book, NULL); //creating the node we want to add

    if (head == NULL) //if this is the first node we can just change the head to the target node
    {
        head = target;
            
    }else if (id < head->getBook()->getCode()) //if the new node has a smaller id than the leading node we can insert it infront of the existing head
    {
        target->setLink(head);
        head = target;
    }else{ //if the id of the new node is larger, then we can just insert it between the two nodes that are above and below it
        for (ptr = head; ptr->getLink() != NULL && (ptr->getBook()->getCode() < id); ptr = ptr->getLink()) //finding the node that would go right before target node
				prev = ptr; 

		if (id < ptr->getBook()->getCode()) //if the node goes inbetween two nodes
		{
            target->setLink(prev->getLink());
            prev->setLink(target);
		}

		if (ptr->getLink() == NULL && ptr->getBook()->getCode() > id)//if node goes 2nd to last
		{
			prev->setLink(target);
			target->setLink(ptr);
		}
		else if (ptr->getLink() == NULL) //if node goes at end of list
		{
			ptr->setLink(target);
		}
        
    }

    return head; //returning head of the linked list

}

void makeLibrary(lNode* library[], string filename) //this function is the read in the target data to feed into the function that makes the linked list nodes
{
    lNode* headC = NULL;  //heads of each linked list
    lNode* headCM = NULL;
    lNode* headN = NULL;
    ifstream infile;
    infile.open(filename); //opening filestream
    if (infile.fail()) //make sure file opens successfully
    {
        cout << "Input file opening failed." << endl; //error message
        exit(1);
    }

    int count(0); //number of lines in file
    string line; 

    while (!infile.eof()) //counting lines in file
    {
        getline(infile, line);
        count ++;
    }

    infile.clear(); //reset file reader
    infile.seekg(0,ios::beg);

    for (int i = 0; i < count; i++) //need to check each line so we loop for the number of lines in the file
    {
        int id(0); //book code
        int avai, rented, age, pdate; //other book data
        string title, publish;
        infile >> id; //taking in id
        if (id > 1000 && id < 2001) //determines which type of book based on the id, inputs the corresponding data and finally adds the new target data as a node to the linked list
        {
            infile  >> title >> age >> avai >> rented;
            Book* data = new ChildBook(id, title, avai, rented , age); //creating the book class with new data
            headC = addLList(data, id, headC); //adding the node with the created data
        }else if (id > 2000 && id < 3001)
        {
            infile  >> title >> publish >> avai >> rented;
            Book* data = new CompBook(id, title, avai, rented, publish); //creating the book class with new data
            headCM = addLList(data, id, headCM); //adding the node with the created data
        }else if (id > 3000 && id < 4001)
        {
            infile  >> title >> pdate >> avai >> rented;
            Book* data = new Novel(id, title, avai, rented, pdate); //creating the book class with new data
            headN = addLList(data, id, headN); //adding the node with the created data
        }
    }

    library[0] = headC; //placing the heads of the linked list into the static array
    library[1] = headCM;
    library[2] = headN;
    
}

pNode*  addpList(Person* person, int id, pNode* head)
//this function is to add a node to one of the person linked lists, taking in the id of the person, the person data class itself, and the head of the list
{
    pNode* target = NULL; //the node we want to add
    pNode* ptr = NULL; //our current node
    pNode* prev =  NULL; //the previous node

    target = new pNode(person, NULL); //creating the node we want to add

    if (head == NULL) //if this is the first node we can just change the head to the target node
    {
        head = target;
            
    }else if (id < head->getPerson()->getID())  //if the new node has a smaller id than the leading node we can insert it infront of the existing head
    {
        target->setLink(head);
        head = target;
    }else{ //if the id of the new node is larger, then we can just insert it between the two nodes that are above and below it
        for (ptr = head; ptr->getLink() != NULL && (ptr->getPerson()->getID() < id); ptr = ptr->getLink()) //finding the node that would go right before target node
				prev = ptr;

		if (id < ptr->getPerson()->getID()) //if the node goes inbetween two nodes
		{ 
            target->setLink(prev->getLink());
            prev->setLink(target);
		}

		if (ptr->getLink() == NULL && ptr->getPerson()->getID() > id) //if node goes 2nd to last
		{
			prev->setLink(target);
			target->setLink(ptr);
		}
		else if (ptr->getLink() == NULL) //if node goes at end of list
		{
			ptr->setLink(target);
		}
        
    }

    return head; //returning head of list
}


void makePeople(pNode* people[],string filename)
{
    pNode* headS = NULL; //heads of each linked list
    pNode* headT = NULL;

    ifstream infile;
    infile.open(filename);
    if (infile.fail()) //make sure file opens successfully
    {
        cout << "Input file opening failed." << endl; //error message
        exit(1);
    }

    int count(0); //number of lines in file
    string line;

    while (!infile.eof()) //counting lines in file
    {
        getline(infile, line);
        count ++;
    }

    infile.clear(); //reset file reader
    infile.seekg(0,ios::beg);

    for (int i = 0; i < count; i++) //need to check each line so we loop for the number of lines in the file
    {
        int id, nBook; //person id and number of books
        string name; //name of person
        int sCodes[2], tCodes[3]; //arrays to hold codes of the books each person has
        infile >> id; ///read in id
        if (id >  0 && id < 101) //determines which type of person  based on the id, inputs the corresponding data and finally adds the new target data as a node to the linked list
        {
            infile >> name >> nBook;
            if (nBook > 0)
            {
                for (int i = 0; i < nBook; i++)
                {
                    infile >>  tCodes[i];

                }
            }
            Person* data = new Teacher( id, name, nBook, tCodes);  //creating the person class with new data
            headT = addpList(data, id, headT); //adding the node with the created data

            
        }else if (id > 100 && id < 301)

        {
            infile >> name >> nBook;
            if (nBook > 0)
            {
                for (int i = 0; i < nBook; i++)
                {
                    infile >>  sCodes[i];

                }
            }
            Person* data = new Student( id, name, nBook, sCodes); //creating the person class with new data
            headS = addpList(data, id, headS); //adding the node with the created data
        }
    }

    people[0] = headT; //adding heads of the linked lists to the static array
    people[1] = headS;
    
}

void menuOne(lNode* library[]) //1st menu option to select a book and find its info, taking in just the library data
{
    int id; //book id
    string title; //book title
    cout << "\nEnter Code: "; //io
    cin >> id;
    cout << "Enter Title: ";
    cin >> title;

    cout << endl;
    if (id > 1000 && id < 2001) //determines type of book based on the id
    {
        
        lNode* temp = library[0]; //set this temp head to the head of the correct linked list of books that are of the type we need
        while(temp!= NULL) //loop through linked list
        {
            if (id == temp->getBook()->getCode()) //if we find the id of the book we want
            {
                try //exception handling if the book code and title don't match
                {
                    if (id == temp->getBook()->getCode() && title == temp->getBook()->getTitle()) //if they do match
                    {
                        cout << title << "(" << id << ") exists" << endl; //output data we want
                        cout << "Category: Children's Book" << endl;
                        cout << "Age: " << temp->getBook()->getAge() << endl;
                        cout << temp->getBook()->getAvai() << " Available, " << temp->getBook()->getRented() << " Rented" << endl;                   
                    }else{ 
                        throw(id); //throw exception if they don't match
                    }
                
                }
                catch(int x) //catch in case exception is thrown
                {
                    cout << "Title and Code pair is not found\n";
                } 
            }
            
            
            temp = temp->getLink(); //increment temp to the next node on the list

        }

    }else if (id > 2000 && id < 3001)
    {
        lNode* temp = library[1]; //set this temp head to the head of the correct linked list of books that are of the type we need
        while(temp!= NULL) //loop through linked list
        {
            if (id == temp->getBook()->getCode())  //if we find the id of the book we want
            {
                try //exception handling if the book code and title don't match
            {
                if (id == temp->getBook()->getCode() && title == temp->getBook()->getTitle()) //if they do match
                {
                    cout << title << "(" << id << ") exists" << endl; //output data we want
                    cout << "Category: Computer Book" << endl;
                    cout << "Publisher: " << temp->getBook()->getPublish() << endl;
                    cout << temp->getBook()->getAvai() << " Available, " << temp->getBook()->getRented() << " Rented" << endl;                   
                }else{
                    throw(id); //throw exception if they don't match
                }
                
            }
                catch(int x) //catch in case exception is thrown
                {  
                    cout << "Title and Code pair is not found";
                    return;
                } 
            }
            temp = temp->getLink(); //increment temp to the next node on the list
        }
        
    }else if (id > 3000 && id < 4001)
    {
        lNode* temp = library[2]; //set this temp head to the head of the correct linked list of books that are of the type we need
        while(temp!= NULL) //loop through linked list
        {
            if (id == temp->getBook()->getCode()) //if we find the id of the book we want
            {
                try //exception handling if the book code and title don't match
                {
                    if (id == temp->getBook()->getCode() && title == temp->getBook()->getTitle()) //if they do match
                    {
                        cout << title << "(" << id << ") exists" << endl; //output data we want
                        cout << "Category: Novel" << endl;
                        cout << "Publish Date: " << temp->getBook()->getPDate() << endl;
                        cout << temp->getBook()->getAvai() << " Available, " << temp->getBook()->getRented() << " Rented" << endl;                   
                    }else{
                        throw(id); //throw exception if they don't match
                    }
                    
                }
                catch(int x) //catch in case exception is thrown
                {
                    cout << "Title and Code pair is not found";
                } 
            }
            temp = temp->getLink(); //increment temp to the next node on the list

        }
        
    }
    
}

bool rent(int id, string title, lNode* library[], pNode* person) //this is to rent a book out to a person, handles the updating of the data
{
    for (int i = 0; i < 3; i++) //first we need to find the right book to rent, and since we weren't given an ID we need to search every node, and therefore every linked list in library
    {
        lNode* temp = library[i]; //head of linked list, will move down static array
        while (temp != NULL) //loop through the linked list in the static array
        {
            if (temp->getBook()->getTitle() == title) //if we do get a match
            {
                try //exception handling for if the book has no available copies left
                {
                    if (temp->getBook()->getAvai() == 0) //making sure there are books available
                    {
                        throw(0); //throw exception if there aren't any left
                    }
                    temp->getBook()->setRented(temp->getBook()->getRented()+1); //increment books available and rented out
                    temp->getBook()->setAvai(temp->getBook()->getAvai()-1);
                    if (id > 0 && id < 101) //now we need to edit the codes of the books the person has rented out, this tells if the id is a student or teacher id
                    {
                        
                        person->getPerson()->settCodes(temp->getBook()->getCode(),person->getPerson()->getNBook()); //changing for teachers

                    }else if (id > 100 && id < 301)
                    {
                        person->getPerson()->setsCodes(temp->getBook()->getCode(),person->getPerson()->getNBook()); //changing for students

                    }
                    person->getPerson()->setNBOOK(person->getPerson()->getNBook()+1);//add number of books the person has rented out
                    return true; //return true if works
                    
                }
                catch(int x) //catching the exception and returning a false since no books are left
                {
                    cout << "There are no copies of this book remaining.";
                    return false;
                }
                
            }
            temp = temp->getLink(); //increment down linked list
        }
        
    }
    return false; //something went wrong if we got here
    
}

void menuTwo(lNode* library[], pNode* people[]) //this is to take in the book we want to rent and the person renting it, then outputting the result of the renting process
{
    int id(0); //id of person
    string title("NULL"); //name of book

    cout << "\nEnter your id: "; //io
    cin >> id;
    cout << "Enter book title: ";
    cin >> title;
    cout << endl;

    if (id >  0 && id < 101) //is person student or teacher
    {
        pNode* temp = people[0]; //set to teacher linked list
        char yn('n'); //confirmation character
        while (temp != NULL) //looping through linked list to find our person
        {
            if (id == temp->getPerson()->getID()) //when we find the person
            {
                cout << "You are " << temp->getPerson()->getName() << "."; //output
                try
                {
                    if (temp->getPerson()->getNBook() == 3) //if person has 3 books already we throw an exception
                    {
                        throw(3); //throwing exception
                    }
                    
                    cout << " You rented " << temp->getPerson()->getNBook() << " books.\n";//output
                    cout << "Do you want to rent '" << title << "' (y/n)?"; //confimation
                    cin >> yn;
                    if (yn == 'y') //if they confirm
                    { 
                        bool success(false); //making a bool to check for successful rent processing
                        success = rent(id, title, library, temp); //calling function to check for rent processing
                        if (success == true) //if success output success message
                        {
                            cout << "***** Rent successful. Check your info!\n";
                        }else if (success == false) //if false then something went wrong
                        {
                            cout << "Something went wrong. Try again\n";
                        }            
                        
                    }else{
                        break; //if they dont confirm we just exit the loop and return to main menu
                    }
                    
                }
                catch(int x)
                {
                    cout << "\nYou have already rented three books.\n";
                    return;
                }
                

            }
            temp = temp->getLink(); //increment linked list
        }
        
    }else if (id  > 100 && id < 301) //if we have a student
    {
        pNode* temp = people[1]; //set to student linked list

        //everything below is the same as the if branch above

        char yn('n'); 
        while (temp != NULL)
        {
            if (id == temp->getPerson()->getID())
            {
                cout << "You are " << temp->getPerson()->getName() << ".";
                try
                {
                    if (temp->getPerson()->getNBook() == 2) //only difference: maximum of two books allowed
                    {
                        throw(3);
                    }
                    
                    cout << " You rented " << temp->getPerson()->getNBook() << " books.\n";
                    cout << "Do you want to rent '" << title << "' (y/n)? ";
                    cin >> yn;
                    if (yn == 'y')
                    { 
                        bool success(false);
                        success = rent(id, title, library, temp);
                        if (success == true)
                        {
                            cout << "***** Rent successful. Check your info!\n";
                        }else if (success == false)
                        {
                            cout << " Something went wrong. Try again\n";
                        }            
                        
                    }else{
                        break;
                    }
                    
                }
                catch(int x)
                {
                    cout << "\nYou have already rented two books.\n";
                    return;
                }
                

            }
            temp = temp->getLink();
        } 
    }
}

int returnBook(int id, int code, lNode* library[], pNode* person) //this is to return a book from a person, handles the updating of the data
{
    if (code > 1000 && code < 2001) //this determines the book genre based on the id
    {
        lNode* temp = library[0]; //set this temp head to the head of the correct linked list of books that are of the type we need
        char yn('n'); //confirmation character
        while (temp != NULL) //loop through the linked list in the static array
        {
            if (code == temp->getBook()->getCode()) //when we actually find the book we are looking for
            {
                cout << "Do you want to return '" << temp->getBook()->getTitle() << "' (y/n)? "; //output
                cin >> yn; //confirmation input
                if (yn == 'n')
                {
                    return 1; //if they say no then we just return with a 1 instead of 0 
                }
                temp->getBook()->setRented(temp->getBook()->getRented()-1); //updating rented and available books
                temp->getBook()->setAvai(temp->getBook()->getAvai()+1);
                if (id > 0 && id < 101) //if the person is a teacher then we havea  different number of times we need to loop so we detemrine the person type
                {
                    for (int i = 0; i < 3; i++) //loop to update array of book codes
                    {
                        if (person->getPerson()->gettCodes(i) == code) //when we find the book we need to return 
                        {
                            person->getPerson()->settCodes(0,i); //replace with 0
                        }
                        
                    }

                }else if (id > 100 && id < 301) //loop to update array of book codes
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (person->getPerson()->getsCodes(i) == code) //when we find the book we need to return
                        {
                            person->getPerson()->setsCodes(0,i); //replace with 0
                        }
                        
                    }
                }
                person->getPerson()->setNBOOK(person->getPerson()->getNBook()-1); //updating number of books
                return 0; //return a success
            }
            
            temp = temp->getLink(); //increment down linked list
        }
        return 1; //if we got here something went wrong

    //all other elif branches are the same except they are for different elements in the library static array 

    }else if (code > 2000 && code < 3001)
    {
        lNode* temp = library[1];
        char yn('n');
        while (temp != NULL)
        {
            if (code == temp->getBook()->getCode())
            {
                cout << "Do you want to return '" << temp->getBook()->getTitle() << "' (y/n)? ";
                cin >> yn;
                if (yn == 'n')
                {
                    return 1;
                }
                temp->getBook()->setRented(temp->getBook()->getRented()-1);
                temp->getBook()->setAvai(temp->getBook()->getAvai()+1);
                if (id > 0 && id < 101)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (person->getPerson()->gettCodes(i) == code)
                        {
                            person->getPerson()->settCodes(0,i);
                        }
                        
                    }

                }else if (id > 100 && id < 301)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (person->getPerson()->getsCodes(i) == code)
                        {
                            person->getPerson()->setsCodes(0,i);
                        }
                        
                    }
                }
                person->getPerson()->setNBOOK(person->getPerson()->getNBook()-1);
                return 0;
            }
            
            temp = temp->getLink();
        }
        return 1;
    }else if (code > 3000 && code < 4001)
    {
        lNode* temp = library[2];
        char yn('n');
        while (temp != NULL)
        {
            if (code == temp->getBook()->getCode())
            {
                cout << "Do you want to return '" << temp->getBook()->getTitle() << "' (y/n)? ";
                cin >> yn;
                if (yn == 'n')
                {
                    return 1;
                }
                temp->getBook()->setRented(temp->getBook()->getRented()-1);
                temp->getBook()->setAvai(temp->getBook()->getAvai()+1);
                if (id > 0 && id < 101)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        if (person->getPerson()->gettCodes(i) == code)
                        {
                            person->getPerson()->settCodes(0,i);
                        }
                        
                    }

                }else if (id > 100 && id < 301)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (person->getPerson()->getsCodes(i) == code)
                        {
                            person->getPerson()->setsCodes(0,i);
                        }
                        
                    }
                }
                person->getPerson()->setNBOOK(person->getPerson()->getNBook()-1);
                return 0;
            }
            
            temp = temp->getLink();
        }
        return 1;
    }
    return 1; //if we got here smthng is wrong
    
    
}

void menuThree(lNode* library[], pNode* people[]) //prepares and inputs data to send to the returnBook function, also outputs results of the returnBook function
{
    int id(0), bCode(0); //variables for person id and the book code to return
    cout << "\nEnter youd id: "; //io
    cin >> id;
    cout << "Enter book code to return: ";
    cin >> bCode;
    cout << endl;

    if (id >  0 && id < 101) //detemines person type based on id
    {
        pNode* temp = people[0]; //sets temp to the head of a linked list based on person's id
        while (temp != NULL) //loop through the linked list
        {
            if (id == temp->getPerson()->getID()) //when we actually find the id we are looking for 
            {
                try //exception handling for if the person has no books to return or actually has the book they want to return
                {
                    int success(1); //status checker for if returnBook succeeded
                    bool check(false); //check for if person has books
                    if (temp->getPerson()->getNBook() != 0) //if the person has actual books we check those books
                    {
                        for (int i = 0; i < 3; i++) //loop for number of max books to check codes array
                        {
                            if (temp->getPerson()->gettCodes(i) == bCode) //if we find the book code we need
                            {
                                check = true; //no error, we can continue code
                            }
                        }
                    }
                    if (check == false) //now if we don't find the book code we need
                    {
                        throw(0); //throw an exception
                    }
                    success = returnBook(id, bCode, library, temp); //returning the book and receiving a status
                    if (success == 1) //if something no bueno happened
                    {
                        cout << "Return terminated. \n"; //output
                        return;
                    }else if (success == 0) //if all good
                    {
                        cout << "***** Return successful. Check your info!\n"; //output
                        return;
                    }
                    
                }
                catch(int x) //catching the exception 
                {
                    cout << "You have not rented this book before.\n"; //output
                    return;
                }
            }
            
            temp = temp->getLink(); //incrementing down the linked list
        }
    
    // other elif branch is the same except it is given the head of the student list rather than the teacher one
    }else if (id  > 100 && id < 301)
    {
        pNode* temp = people[1];
        while (temp != NULL)
        {
            if (id == temp->getPerson()->getID())
            {
                try
                {
                    int success(1);
                    bool check(false);
                    if (temp->getPerson()->getNBook() != 0)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            if (temp->getPerson()->getsCodes(i) == bCode)
                            {
                                check = true;
                            }
                        }
                    }
                    if (check == false)
                    {
                        throw(0);
                    }
                    success = returnBook(id, bCode, library, temp);
                    if (success == 1)
                    {
                        cout << "Return terminated. \n";
                        return;
                    }else if (success == 0)
                    {
                        cout << "***** Return successful. Check your info!\n";
                        return;
                    }
                    
                }
                catch(int x)
                {
                    cout << "You have not rented this book before.\n";
                    return;
                }
            }
            
            
            temp = temp->getLink();
        } 
    }

}

void findBook(lNode* library[], int id) // finding the book we need to output the id and other information based on the id
{
    if (id > 1000 && id < 2001) //determine book tyoe by id
    {
        
        lNode* temp = library[0]; //setting temp to the head of the list of the corresponding linked list based on the id
        while(temp!= NULL)
        {
            if (id == temp->getBook()->getCode()) //when we find the book
            {
                cout << temp->getBook()->getTitle() << "(" << id << ")" << " - age: " << temp->getBook()->getAge() << endl; //output
            }
            temp = temp->getLink(); //increment down the linked list

        }

    //all other conditional brances are the same except they output slightly different data (publisher, publishing date instead of age) and are incrementing down diff linked lists

    }else if (id > 2000 && id < 3001)
    {
        lNode* temp = library[1];
        while(temp!= NULL)
        {
            if (id == temp->getBook()->getCode())
            {
                cout << temp->getBook()->getTitle() << "(" << id << ")" << " - Publisher: " << temp->getBook()->getPublish() << endl;

            }
            temp = temp->getLink();
        }
        
    }else if (id > 3000 && id < 4001)
    {
        lNode* temp = library[2];
        while(temp!= NULL)
        {
            if (id == temp->getBook()->getCode())
            {
                cout << temp->getBook()->getTitle() << "(" << id << ")" << " - Publish Date: " << temp->getBook()->getPDate() << endl;

            }
            temp = temp->getLink();
        }
        
    }
}

void menuFour(pNode* people[], lNode* library[]) //this is for finding a person and displaying their information and books rented
{
    int id; //id of person
    string name; //name of person
    cout << "\nEnter your id: "; //io
    cin >> id;
    cout << "Enter you name: ";
    cin >> name;

    if (id >  0 && id < 101) //determining if person is student or teacher
    {
        pNode* temp = people[0]; //set temp node to the head of the corresponding linked list based on id

        while (temp != NULL) //loop through linked list
        {
            if (id == temp->getPerson()->getID()) //when we find the right person
            {
                int nBooks = temp->getPerson()->getNBook(); //storing number of books since we will need it multiple times, saves typing
                cout << "\nYou rented " << nBooks << " books.\n"; //output
                if (nBooks > 0) //if this person has books rented
                {
                    for (int i = 0; i < 3; i++) //loop for max number of possible books
                    {
                        if (temp->getPerson()->gettCodes(i) != 0) //when we find a book code we display it
                        {
                            cout << "* "; //output
                            findBook(library, temp->getPerson()->gettCodes(i)); //calling function to display book info
                        }
                    }
                }
            }
            temp = temp->getLink(); //increment down linked list
        }
        
    //elif branch is same as if branch, only difference is max of two books rented and student linked list used

    }else if (id  > 100 && id < 301)
    {
        pNode* temp = people[1]; 
        while (temp != NULL)
        {
            if (id == temp->getPerson()->getID())
            {
                int nBook = temp->getPerson()->getNBook();
                cout << "\nYou rented " << nBook << " books.\n";
                if (nBook > 0)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (temp->getPerson()->getsCodes(i) != 0)
                        {
                            cout << "* ";
                            findBook(library, temp->getPerson()->getsCodes(i)); 
                        }
                    }
                    
                }
                
            }
            temp = temp->getLink();
        } 
    }
}

void menuFive(lNode* library[]) //this is just to display all book information
{
    cout << "=====================================================================" << endl; //output
    cout << "\t\t\t   Children Books\n";
    cout << "=====================================================================" << endl;

    cout << "Code" << setw(15) << "Title" << setw(15) << "Age" << setw(15) <<  "Available   " <<  "Rented" << endl; //output

    lNode* temp = library[0]; //head of linked list inside static array
       
    while (temp !=  NULL) //loop through linked list
    {
        Book* book = temp->getBook(); //the book we are displaying info abt
        cout << setw(7) <<left << book->getCode() //output
                  << setw(25) << left << book->getTitle2()
                  << setw(20) << left << setw(5) << book->getAge()
                  << setw(5) << right << book->getAvai()
                  << setw(10) << right << book->getRented() << endl;
        temp = temp->getLink(); //increment down linked list
    }
    
    cout << "=====================================================================" << endl; //output
    cout << "\t\t\t   Computer Books\n";
    cout << "=====================================================================" << endl;
    cout << "Code" << setw(15) << "Title" << setw(22) << "Publisher" <<  "\t\tAvailable   " <<  "Rented" << endl; //output


    lNode* temp2 = library[1]; //head of linked list inside static array
       
    while (temp2 !=  NULL) //loop through linked list
    {
        Book* book = temp2->getBook();  //the book we are displaying info abt
        cout << setw(7) << left << book->getCode() //output
                  << setw(25) << left << book->getTitle2()
                  << setw(20) << left << book->getPublish()
                  << setw(8) << right << book->getAvai()
                  << setw(10) << right << book->getRented() << endl;        
        temp2 = temp2->getLink(); //increment down linked list
    }

    cout << "=====================================================================" << endl; //output
    cout << "\t\t\t\tNovels\n";
    cout << "=====================================================================" << endl;
    cout << "Code" << setw(15) << "Title" << setw(17) << "Date" << setw(15) <<  "\t  Available  " <<  "Rented" << endl; //output

        
    lNode* temp3 = library[2]; //head of linked list inside static array
       
    while (temp3 !=  NULL) //loop through linked list
    {
        Book* book = temp3->getBook(); //the book we are displaying info abt
        cout << setw(7) << left << book->getCode() //output
                  << setw(25) << left << book->getTitle2()
                  << setw(10) << left << book->getPDate()
                  << setw(5) << right << book->getAvai()
                  << setw(10) << right << book->getRented() << endl;         
        temp3 = temp3->getLink();  //increment down linked list
    }
    
}

void deleteLLists(lNode* library[], pNode* people[]) //this function just deletes all the linked lists
{
    for (int i = 0; i < 3; i++)
    {
        lNode* head = library[i];
        lNode* ptr = NULL;
        while (head != NULL)
        {
            ptr = head->getLink();
            delete head;
            head = ptr;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        pNode* head = people[i];
        pNode* ptr = NULL;
        while (head != NULL)
        {
            ptr = head->getLink();
            delete head;
            head = ptr;
        }
    }

}