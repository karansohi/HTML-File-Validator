/*Author : Karanbir Singh
This is the test program for the html file validator
The file is read character by character and if a tag is found it is stored in a string which will eventually be stored in our stack of linkedlist strings.
IF a closing tag is found then the result string will be matched with the top of our stack and if they match the stack will pop out that tag
In the end if the stack is empty it means all the opening tag have found the closing tags and our html file is valid
 2.0 --> Updated version with checking of non closing tags
*/
//Terminal Command : g++ -pedantic -Wall -Wextra -std=c++14 TestValidator.cpp -o TestValidator
#include <iostream>
#include <string>
#include <fstream>
#include "ValidatorClass.hpp"

using namespace std;

bool validateTag(string tag);
void checkHtmlFile(string fileName);
bool checkSingleTag(string tag);
int main(){
    checkHtmlFile("Validhtml.txt");
    //checkHtmlFile("Validhtml2.txt");
    return 0;
}

/*function that will read the file, check tags, store opening tags and pop them out if they match with the closing tags **/
void checkHtmlFile(string fileName){
    cout << "Validating file: " <<fileName << endl;
    Validator tagStack;
    ifstream htmlFile;
    htmlFile.open(fileName);
    string htmlTag = "";
    char c;
    bool closingTag = false; // this boolean variables will tell us wether we have a opening or closing tag
    
    while(!htmlFile.eof()){
        htmlFile>>c;//reading file character by character
        if( c == '<'){ // if any char is equal to < we might have a html tag
            /* read chars from start to end and if it exceeds 9( longest html tag aka "blockquote" ) then it is not a tag*/
            while(c != '>'){
                htmlFile>>c;
                if( c == '/' && c!= '>'){
                    closingTag = true;
                }
                else if(c != ' ' && c!= '>'){
                    htmlTag+=c;
                }
            }
            //if the tag is valid and it is not a closing tag it will be pushed into the stack
            if(validateTag(htmlTag) == true && closingTag == false){
                tagStack.pushTag(htmlTag);
            }
            //if it is a talid tag and is a closing tag we will check the top of the stack and if they are equal we will simply push it out
            else if (validateTag(htmlTag) == true && htmlTag == tagStack.topTag()){
                tagStack.popTag();
            }
            //if none of the above are true means that either we have a misplaced tag or a false tag so it is better to display it to the user
            else if (validateTag(htmlTag) == false && checkSingleTag(htmlTag) == false){
                cout << "This tag : <" << htmlTag << "> is not valid as an html tag" << endl;
            }
        }
        htmlTag = "";
        closingTag = false;
    }
    //the file will be valid file only if all the elements from the stack have been pushed out
    if(tagStack.emptyStack() == true)
        cout << "The inserted file is a valid html file" << endl;
    else
        cout << "The inserted file is not a valid html file please check for any unclosed tags " << endl;
    htmlFile.close();
}

//function that will check a string with a give array of valid tags and tell wether it is valid or not
bool validateTag(string tag){
    
    string tagArray [10] = {"html",  "head",  "body",  "p",  "br",  "li",  "h1",  "h2" , "ul",  "ol"};
    bool validity = false;
    for(int i = 0; i< 10; i++)
    {
        if(tag ==  tagArray[i])
        {
            validity = true;
            break;
        }
    }
    return validity;
}

//checking if the tag is a single tag, if so it does not need to be pushed into the stack since it will not have a closing
bool checkSingleTag(string tag){
    string tagArray [16] = {"area", "base", "br", "col", "command", "hr", "embedded", "img", "input", "meta", "keygen", "link", "param", "source", "track", "wbr"};
    for(int i = 0; i < 16; i++){
        if(tag == tagArray[i]){
            return true;
            break;
        }
    }
    return false;
}
