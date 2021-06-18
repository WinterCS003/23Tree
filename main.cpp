/******************************************************************
 * AUTHOR   : Jaemok C. Lee & Bowen Liu
 * LAB #07  : 2-3 Trees
 * CLASS    : CS 008 Data Structures
 * SECTION  : 6:30p - 8:35
 * DUE DATE : 05/22/2021
 ******************************************************************/
#include <iostream>

#include "b-tree.h"
  
/***********************************************************
* menu()
*_________________________________________________________
* Allows user to modify and print tree.
*_________________________________________________________
* PRE-CONDITIONS
*   none
*
* POST-CONDITIONS
*   creates a tree that the user can modify and print.
***********************************************************/
void menu();
  
/***********************************************************
* Display()
*_________________________________________________________
* Allows user to see all possible actions on tree
*_________________________________________________________
* PRE-CONDITIONS
*   none
*
* POST-CONDITIONS
*   prints options to screen
***********************************************************/
void display();

int main() {
  std::cout << "------------------------" << std::endl;
  std::cout << "AUTHOR   : Jaemok C. Lee & Bowen Liu\n"
            << "LAB #07  : 2-3 Trees\n"
            << "CLASS    : CS 008 Data Structures\n"
            << "SECTION  : 6:30p - 8:35\n"
            << "DUE DATE : 05/22/2021\n";
  std::cout << "------------------------\n\n";
  
  menu();
}

/**********************************************************
 *
 * FUNCTION menu
 *_________________________________________________________
 * This function receives nothing and allows the user to
 * choose actions on the tree
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print user choices to the screen
 ***********************************************************/
void menu(){
  display();
  
  int choice = -1;

  Tree t1;
  while(choice != 7){
    std::cout << "Please make a choice(6 for menu and 7 to quit): ";
    std::cin >> choice;
    std::cout << std::endl;
    int insert;
    switch(choice){
      case 1:
        std::cout << "Value to Insert: ";
        std::cin >> insert;
        std::cout << std::endl;
        t1.insert(insert);
        std::cout << std::endl;
        break;
      case 2:
        std::cout << "Value to delete: ";
        std::cin >> insert;
        std::cout << std::endl;
        t1.remove(insert);
        std::cout << std::endl;
        break;
      case 3:
        t1.InOrderDisplay();
        std::cout << std::endl;
        break;
      case 4:
        t1.PreOrderDisplay();
        std::cout << std::endl;
        break;
      case 5: 
        t1.PostOrderDisplay();
        std::cout << std::endl;
        break;
      case 6:
        display();
        break;
      case 7:
        std::cout << "Good Bye..." << std::endl;
        break;
      default:
        std::cout << "Invalid Choice" << std::endl;
        display();
    } 
  }
}

/**********************************************************
 *
 * FUNCTION display
 *_________________________________________________________
 * This function displays all possible user choices to the
 * screen
 *_________________________________________________________
 * PRE-CONDITIONS
 *   none
 *
 * POST-CONDITIONS
 *   This function will print all possible user choices to
 *   the console.
 ***********************************************************/
void display(){
  std::cout << "------------------------" << std::endl;
  std::cout << "2-3 Tree" << std::endl;
  std::cout << "Please Choose a Function:" << std::endl;
  std::cout << "1) Insert\n"  
            << "2) Delete\n"
            << "3) In Order Display\n" 
            << "4) Pre Order Display\n"
            << "5) Post Order Display\n"
            << "6) Menu\n"
            << "7) Exit\n";
  std::cout << "------------------------" << std::endl;
}
