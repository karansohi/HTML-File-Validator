/*Author: Karanbir Singh
This is the h and cpp file for the html code validation class*/

#include <iostream>
#include <string>

#ifndef VALIDATORCLASS_hpp
#define VALIDATORCLASS_hpp


using namespace std;

//Node class that will store our htmltags
class Node {
    private:
    string tag;
    Node *next;
public:
    Node() {
        next = nullptr;
    }
    Node(string data, Node *link = nullptr){
        tag = data;
        next = link;
    }
    friend class Validator;
};
//Validator class that will use nodes and build a linkedlist of strings
class  Validator{
    private:
        int size;
        Node *front, *end;
    public:
        Validator();
        ~Validator();
        void pushTag(string t);
        void popTag();
        string topTag();
        int stackSize();
        bool emptyStack();
        void checkElements();
};

Validator::Validator(){
    size = 0;
    front = nullptr;
    end = nullptr;
}
Validator::~Validator(){
    for(Node* temp; front != nullptr;){
                temp = front;
                front = front->next;
                delete temp;
                temp = nullptr;
            }
}

string Validator::topTag(){
    return front->tag;
}

int Validator::stackSize(){
    return size;
}

bool Validator::emptyStack(){
    if( size == 0 )
        return true;
    else
        return false;
}
void Validator::pushTag(string tg){
    if(front == nullptr){
        front = new Node(tg,nullptr);
        size++;
    }
    else{
        Node* curr = new Node(tg);
        Node* temp = front;
        front = curr;
        front->next = temp;
        size++;
    }
}
void Validator::popTag(){
    Node* curr = front;
    front = front->next;
    size--;
    delete curr;
}
void Validator::checkElements(){
    Node* temp = front;
    while( temp != nullptr){
        cout << temp->tag << endl;
        temp = temp->next;
    }
}
#endif

