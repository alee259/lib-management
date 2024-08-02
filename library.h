#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

class Book //book parent class for book genre
{
    private:
    int code; //code of book
    string title; //title of book
    int avai; //number of books available
    int rented; //number of books rented
    public:
    Book() : code(0), title("NULL"), avai(0), rented(0) {} //constructors
    Book(int code, string title, int avai, int rented)
    {
        this -> code = code;
        this -> title = title;
        this -> avai = avai;
        this -> rented = rented;

    }
    void setCode(int code) {this -> code = code;} //setters
    void setAvai(int avai) {this -> avai = avai;}
    void setRented(int rented) {this -> rented = rented;}
    void setTitle(string title) {this -> title = title;}
    int getCode() const{return code;} //getters
    int getAvai() const{return avai;}
    int getRented() const{return rented;}
    string getTitle() const{return title;}
    string getTitle2() { //special getter to get the title without underscores
        string modTitle = title;
        for (char& ch : modTitle) {
            if (ch == '_') {
                ch = ' ';
            }
        }
        return modTitle;
    }
    virtual void setAge(int age) = 0; //virtual member functions for child classes
    virtual int getAge() = 0;
    virtual void setPublish(string publish) = 0;
    virtual string getPublish() = 0;
    virtual void setPDate(int math) = 0;
    virtual int getPDate() = 0;

};

class ChildBook : public Book //childrens book class
{
    private:
    int age; //book age
    public:
    ChildBook(){} //constructors
    ChildBook(int code, string title, int avai, int rented, int age) : Book(code, title, avai, rented){
        this -> age = age;
    }
    void setAge(int age) override {this -> age = age;} //ovverriding the virutal functions from the parent class (setters, getters)
    int getAge() override {return age;}
    void setPublish(string publish) override {}
    string getPublish() override {return "";}
    void setPDate(int pdate) override {}
    int getPDate() override { return 0; }
 
};
class CompBook : public Book //computer book class
{
    private:
    string publish; //publisher of book
    public:
    CompBook(){} //ovverriding the virutal functions from the parent class (setters, getters)
    CompBook(int code, string title, int avai, int rented, string publish) : Book(code, title, avai, rented){
        this -> publish = publish;
    }
    void setAge(int age) override {}
    int getAge() override {return 0;}
    void setPublish(string publish) override {this -> publish = publish;}
    string getPublish() override {return publish;}
    void setPDate(int pdate) override {}
    int getPDate() override { return 0; }

};

class Novel : public Book //novel class
{
    private:
    int pdate; //books publishing date
    public:
    Novel(){} //ovverriding the virutal functions from the parent class (setters, getters)
    Novel(int code, string title, int avai, int rented, int pdate) : Book(code, title, avai, rented){
        this -> pdate = pdate;
    }
    void setAge(int age) override {}
    int getAge() override {return 0;}
    void setPublish(string publish) override {}
    string getPublish() override {return "";}
    void setPDate(int pdate) override {this -> pdate = pdate;}
    int getPDate() override { return pdate; }
 
};

class Person //parent class for students/teachers
{
    private:
    int id; //id for person
    string name; //person name
    int nBook; //number of books each person has

    public:
    Person() {} //constructors
    Person(int id, string name, int nBook){
        this -> id = id;
        this -> name = name;
        this -> nBook = nBook;
    }
    int getID() const{return id;} //getters
    string getName() const{return name;}
    int getNBook() const{return nBook;}
    void setID(int id) {this -> id = id;} //setters
    void setName(string name) {this -> name = name;}
    void setNBOOK(int nBook) {this -> nBook = nBook;}

    virtual void settCodes(int tcode, int nt) = 0; //virtual functions for child classes 
    virtual int gettCodes(int nt) = 0;
    virtual void setsCodes(int scode, int ns) = 0; 
    virtual int getsCodes(int ns) = 0;

};

class Student : public Person //student child class
{
    private:
    int sCodes[2]; //array of book codes each student has
    public:
    Student() {} //constructors
    Student(int id, string name, int nBook, int inSCodes[]) : Person(id, name, nBook) {
        for (int i = 0; i < 2; i++) //first initialize array to 0
        {
            sCodes[i] = 0;
        }
        
        
        if (nBook > 0) //now we change the array to the actual codes if there are any
        {
           for (int i = 0; i < nBook; i++)
            {
                sCodes[i]  = inSCodes[i];
            }
        }
    }
    void setsCodes(int scode, int ns) override {sCodes[ns] = scode;} //ovverriding virtual functions
    int getsCodes(int ns) override {return sCodes[ns];}
    void settCodes(int tcode, int nt) override {}
    int gettCodes(int nt) override {return 0;}

};

class Teacher : public Person //teacher child class
{
    private:
    int tCodes[3]; //array of book codes each teacher has
    public:
    Teacher() {}
    Teacher(int id, string name, int nBook, int inTCodes[]) : Person(id, name, nBook) {
        for (int i = 0; i < 3; i++) //first initialize array to 0
        {
            tCodes[i] = 0;
        }

        if (nBook > 0) //now we change the array to the actual codes if there are any
        {
           for (int i = 0; i < nBook; i++)
            {
                tCodes[i]  = inTCodes[i];
            }
        }
    }
    void settCodes(int tcode, int nt) override {tCodes[nt] = tcode;} //ovverriding virtual functions
    int gettCodes(int nt) override {return tCodes[nt];}
    void setsCodes(int scode, int ns) override {}
    int getsCodes(int ns) override {return 0;}
};

class lNode //node for library linked list
{
    private:
    Book* book; //the book in the library (each node has one book)
    lNode* link; //link to next node for linked list
    public:
    lNode() : book(0), link(NULL) {} //constructors
    lNode(Book* book, lNode* link) {
        this -> book = book;
        this -> link = link;
    }
    void setBook(Book* book) {this -> book = book;} //setters and getters
    Book* getBook() {return book;}
    void setLink(lNode* link){ this -> link = link;}
    lNode* getLink() const {return link;}

};

class pNode //node for person data linked list
{
    private:
    Person* person; //the person on the node of the linked list
    pNode* link; //link to next node for linked list
    public:
    pNode() : person(0), link(NULL) {} //constructors
    pNode(Person* person, pNode* link) {
        this -> person = person;
        this -> link = link;
    }
    void setPerson(Person* person) {this -> person = person;} //setters and getters
    Person* getPerson() {return person;}
    void setLink(pNode* link){ this -> link = link;}
    pNode* getLink() const {return link;}

};

lNode* addLList(Book* book, int id, lNode* head);

void makeLibrary(lNode* library[], string filename);

pNode*  addpList(Person* person, int id, pNode* head);

void makePeople(pNode* people[],string filename);

void menuOne(lNode* library[]);

bool rent(int id, string title, lNode* library[], pNode* person);

void menuTwo(lNode* library[], pNode* people[]);

int returnBook(int id, int code, lNode* library[], pNode* person);

void menuThree(lNode* library[], pNode* people[]);

void findBook(lNode* library[], int id);

void menuFour(pNode* people[], lNode* library[]);

void menuFive(lNode* library[]);

void deleteLLists(lNode* library[], pNode* people[]);
