#ifndef main_h
#define main_h
#include <iostream>
#include <ostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <optional>
#include <sstream>
#include "Book.h"
#include "BST.hpp"

//BST for searching and sorting books when inserting, deleting
BST bookTree = BST();

void trimLine(std::string& userInput)
{
    userInput.erase(0, userInput.find_first_not_of(" "));
    userInput.erase(userInput.find_last_not_of(" ") + 1);
}

void addBook()
{
    //book object's attributes
    std::string title;
    std::string author;
    std::string isbn;
    std::string qty_available;
    std::cin.ignore(256, '\n');
    //check if isbn is valid first.
    std::cout << "\nEnter book ISBN:";
    std::getline(std::cin, isbn);
    trimLine(isbn);
    
    if(isISBNvalid(isbn))
    {
        std::cout << "\nEnter book title:";
        std::getline(std::cin, title);
        //error handling for first letter of title lower case which affects the sorting as it has a higher ascii value.
        trimLine(title);
        while(!isTitleFirstLetterCapital(title))
        {
            std::cout << "\nThe title should begin with a capital letter, please try again.\n";
            std::cout << "\nEnter book title:";
            std::getline(std::cin, title);
            trimLine(title);
        }
        std::cout << "\nEnter book author(s) (separate with ';'):";
        std::getline(std::cin, author);
        trimLine(author);
        
        
        std::cout << "\nEnter book quantity:";
        std::getline(std::cin, qty_available);
        trimLine(qty_available);
    
        //loops until input is a digit
        while(!isQtyDigit(qty_available))
        {
            std::cout << "\nQty entered must be an integer!\n";
            std::cout << "\nEnter book quantity:";
            std::getline(std::cin, qty_available);
            trimLine(qty_available);
        }
        
        //add to BST
        Book newBookToAddToDataStructure(title, author, isbn, qty_available);
        bookTree[newBookToAddToDataStructure.getTitle()] = newBookToAddToDataStructure;
        
    } else
    {
        std::cout << "\nISBN is not Valid!\n";
    }
}

void removeBook()
{
    //book object's attributes
    std::string title;
    
    std::cout << "\nEnter book title to remove: ";
    std::cin.ignore(256, '\n');//avoid input skipping error due to new line
    std::getline(std::cin, title);
    
    if(bookTree[title].getTitle() == "")
    {
        std::cout << "\nThis book does not exist to begin with!\n";
    }
    else
    {
        bookTree.remove(title);
        std::cout << "\n" << title << " Successfully removed from stock. Ensure there is none left on the shelves.\n";
    }
}


void removeDamagedBook()
{
    //book object's attributes
    std::string title;
    
    std::cout << "\nEnter book title to remove: ";
    std::cin.ignore(256, '\n'); //avoid input skip error
    std::getline(std::cin, title);
    //create a temporary object to avoid repetitively searching through the tree for this book's attributes.
    Book foundBook = bookTree[title];
    
    if(foundBook.getTitle() == "")
        std::cout << "\nThis book does not exist to begin with!\n";
    else
    {
        if(foundBook.getQty() == 0)
        //Can't have minus books
            std::cout << "\nThis book is out of stock!";
        else
        {
            foundBook.damagedBook();
            std::cout << "\nSuccessfully removed one of " << title << " from stock.\nThere is now " << foundBook.getQty() << " in stock left.";
            //-1 quantity
            bookTree[title] = foundBook;
        }
    }
}

void partialSearch(std::string userInput)
{
    
    //loops until input is made
    while(userInput == "" || userInput == " ")
    {
        std::cout << "\nInput something please!\n";
        std::cout << "\nEnter book title to search: ";
        std::getline(std::cin, userInput);
    }
    
    bookTree.partialSearch(userInput);
}

bool search(std::string userInput)
{
    if(bookTree[userInput].getTitle() == "")
    {
        std::cout << "\nThere was no match for this search\n";
        return false;
    }
    else
    {
        bookTree[userInput].toString();
        return true;
    }
}

void prompt()
{
    std::string userInput;
    
    std::cout << "\n----------------------------\n"
    << "THE LIBARY MANAGEMENT SYSTEM"
    << "\n----------------------------";
    
    std::cout << "\nEnter one of the following options:"
    << "\n1 to View All Books A-Z"
    << "\n2 to View All Books Z-A"
    << "\n3 to Search a Book by it's Title"
    << "\n4 to Partial Search Book(s) by Title"
    << "\n5 to Add New Book"
    << "\n6 to Remove Book From Shelves"
    << "\n7 to Remove a Single Damaged Book."
    << "\n8 to Exit"
    << "\n>_ ";
    std::cin >> userInput;
    
    //turn user input into int
    int userInputToInt = atoi(userInput.c_str());
    switch(userInputToInt)
    {
        case 1:
        {
            bookTree.display_A_Z();
            prompt();
            break;
        }
        case 2:
        {
            bookTree.display_Z_A();
            prompt();
            break;
        }
        case 3:
        {
            std::cout << "\nEnter book title to search: ";
            std::cin.ignore(256, '\n');
            std::getline(std::cin, userInput);
            //trim right and left spaces
            trimLine(userInput);

            search(userInput);
            prompt();
            break;
        }
        case 4:
        {
            std::cout << "\nEnter book title to search: ";
            std::cin.ignore(256, '\n');
            std::getline(std::cin, userInput);
            //trim right and left spaces
            trimLine(userInput);

            partialSearch(userInput);
            prompt();
            break;
        }
        case 5:
        {
            addBook();
            prompt();
            break;
        }
        case 6:
        {
            removeBook();
            prompt();
            break;
        }
        case 7:
        {
            removeDamagedBook();
            prompt();
            break;
        }
        case 8:
        {
            exit(0);
            break;
        }
        default:
        {
            std::cerr << "\n***\nPlease Enter One of The Options ( 1 - 6 )\n***\n";
            prompt();
        }
    }
}

void loadData(char* filename)
{
    //************************ LOAD DATA **************************
    std::ifstream file(filename);
    int counter = 0;
    std::string newLine;
    
    //storing each book object's attributes.
    std::string tmpTitle;
    std::string tmpAuthor;
    std::string tmpIsbn;
    std::string tmpQty;
    
    if (file.is_open()) {
        
        while (std::getline(file, newLine, '\t')) {
            
            switch(counter)
            {
                //title
                case 0:
                {
                    //remove 'end line' at the end of each line.
                    size_t pos = 0;
                    while ((pos = newLine.find("\n", pos)) != std::string::npos)
                    {
                        newLine.erase(pos, 1);
                    }
                    tmpTitle = newLine;
                    Book newBookToAddToDataStructure;
                    
                    //blank title means it is the end of books in the txt file.
                    if(newBookToAddToDataStructure.getTitle() == "")
                    {
                        break;
                    }
                    break;
                }
                    //author
                case 1:
                {
                    tmpAuthor = newLine;
                    break;
                }
                    //isbn
                case 2:
                {
                    tmpIsbn = newLine;
                    break;
                }
                    //qty
                case 3:
                {
                    //All prior loops collected data into object
                    tmpQty = newLine;
                    Book newBookToAddToDataStructure(tmpTitle, tmpAuthor, tmpIsbn, tmpQty);
                    //add to tree for sorting
                    if(tmpTitle != "")
                    bookTree[newBookToAddToDataStructure.getTitle()] = newBookToAddToDataStructure;
                    //reset attributes for next book
                    counter = -1;
                    tmpTitle = "";
                    tmpAuthor = "";
                    tmpIsbn = "";
                    tmpQty = "";
                    break;
                }
            }
            counter++;
        }
        file.close();
    }
    //******************* END OF LOAD DATA **************************
}
#endif
