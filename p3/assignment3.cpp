/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file assignment3.cpp [Driver Code]
 * @note Driver code for A3
 * 
 * @brief This assigment focuses on using multiple operations regarding BST like:
 *   - Insertion
 *   - Traversals
 *   - Searching
 *   - Deletion
 * 
 * Those operations were implemented using a ShelterBST class that includes a struct for Pets and
 * A struct for the TreeNodes.  
 */

#include <string>
#include <iostream>
#include "ShelterBST.h"
#include <vector>
#include <limits>

#pragma message("[" __FILE__"] " "Last compiled on [" __DATE__ "] at [" __TIME__"]")


/** @name OPID (opeartion ID)
 * @enum for the switch statement
 * @brief Every operation has a numerical value
 */
enum OPID {
           ID_1 = 1,
           ID_2 =2,
           ID_3 = 3,
           ID_4 = 4,
           ID_5 = 5,
           ID_6 = 6,
           ID_7 = 7,
           ID_8 = 8,
           ID_9 = 9,
           ID_10 = 10,
           ID_11 = 11,
           ID_12 = 12,
           ID_13 = 13,
           ID_14 = 14,
           ID_15 = 15,
           ID_16 = 16
};

/** @name printTitle()
 * @brief The function prints the title
 * @remark Handles UI
 * @return void-type
 */
void printTitle() {
  std::cout << "\n\n*** Welcome to the BST assigment. *** \n\n";
  std::cout << "Please select one of the following?\n\n";
}

/** @name printMenu()
 * @brief The function prints a menu for the user
 * @remark Handles UI
 * @return void-type
 */
void printMenu() {
  std::cout << "\n\n"
            << "[1]   In-Order Traversal\n"
            << "[2]   Pre-Order Traversal\n"
            << "[3]   Post-Order Traversal\n"
            << "[4]   Insert a Pet\n"
            << "[5]   Find the Predecessor\n"
            << "[6]   Find the Parent\n"
            << "[7]   Search for a Pet\n"
            << "[8]   Delete a Node\n"
            << "[9]   Number of Nodes\n"
            << "[10]  Number of Internal Nodes\n"
            << "[11]  Number of Nodes per Level\n"
            << "[12]  Get the Heigth\n"
            << "[13]  BST Balance\n"
            << "[14]  Destroy BST\n"
            << "[15]  Quit\n"
            << "[16]  Run-Tests\n"; 
  return;
}

/** @name goodbye()
 * @brief The function prompts the user goodbye
 * @remark Handles UI
 * @return void-type
 */
void goodbye() {
  std::cout << "\n\nGoodbye!\n\n";
}

/** @name getInput()
 * @brief The function prompts the user to enter a number corresponding to the menu
 * @return int choice (0 < choice < 8)
 */
int getInput() {
  int const MIN = 1;
  int const MAX = 17;
  int choice = 0;
  std::cout << "\n[Enter]: ";
  
  while (true) {
    try {
      std::cin >> choice;
      if (std::cin.fail()) { //std::cin.fail() if the input is not an intiger returns true
        /// @link https://cplusplus.com/forum/beginner/2957/
        
        std::cin.clear(); // clear error flags
        std::cin.ignore(10000, '\n'); // ignore up to 10000 characters or until a newline is encountered
        throw std::invalid_argument("[Invalid input]");
      }
      else if (choice < MIN || choice > MAX) {
        throw std::out_of_range("[Input out of range. Please enter an integer between 1 and 16]");
      }
      else {
        return choice;
      }
    }
    catch (const std::exception& error) {
      std::cout << error.what() << std::endl;
      std::cout << "[Re-enter]: ";
    }
  }
}

/** @name getName()
 * @brief Prompts the user to enter a name
 * @param name passed by reference
 * @return std::string name
 */
std::string getName(std::string &name) {
  std::cout << "[Enter Name]: ";
  while (true) {
    try {
      std::cin >> name;
      if (std::cin.fail()) {
        throw std::runtime_error("[Invalid input. Please enter a valid name]");
      }
      return name;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
}

/** @name getAge()
 * @brief Prompts the user to enter an age
 * @param age passed by reference
 * @return int age
 */
int getAge(int &age) {
  std::cout << "\n[Enter Age]: ";
  while (true) {
    try {
      std::cin >> age;
      if (std::cin.fail() || age < 0) {
        throw std::runtime_error("[Invalid input. Please enter a positive integer]");
      }
      return age;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "\n[Enter Age]: ";
    }
  }
}

/** @name getLevel()
 * @brief Prompts the user to enter a level
 * @param level passed by reference
 * @return int level
 */
int getLevel(int &level) { /** @note should I check for user input here -> ???*/
  std::cout << "\n[Enter Level]: ";
  while (true) {
    try {
      std::cin >> level;
      if (std::cin.fail()) { //std::cin.fail() if the input is not an intiger returns true
        /// @link https://cplusplus.com/forum/beginner/2957/
        
        std::cin.clear(); // clear error flags
        std::cin.ignore(10000, '\n'); // ignore up to 10000 characters or until a newline is encountered
        throw std::invalid_argument("[Invalid input]");
      }else {
        return level;
      }
    }
    catch (const std::exception& error) {
      std::cout << error.what() << std::endl;
      std::cout << "[Re-enter]: ";
    }
  }
}

int main(int argc, char **argv) {

  /** DECLARATIONS: */
  ShelterBST tree;
  std::string name = "";
  int age = 0;
  int level = 0;
  
  /** DECLARATIONS: */
  printTitle();
  while(true) {
    printMenu();
    switch(getInput()) {
    case OPID::ID_1: {
      /** @note in-order*/
      tree.inOrderDisplay();
      break;
    }
      
    case OPID::ID_2: {
      /** @note pre-order*/
      tree.preOrderDisplay();
      break;
    }
      
    case OPID::ID_3: {
      /** @note post-order*/
      tree.postOrderDisplay();
      break;
    }
      
    case OPID::ID_4: {
      /** @note insert a pet*/
      tree.insertPet(getName(name), getAge(age));
      break;
    }
      
    case OPID::ID_5: {
      /** @note find predecessor*/
      tree.findInorderPredecessor(getName(name));
      break;
    }
      
    case OPID::ID_6: {
      /** @note find parent*/
      tree.findParent(getName(name));
      break;
    }
      
    case OPID::ID_7: {
      /** @note search for a pet*/
      tree.searchPet(getName(name));
      break;
    }
      
    case OPID::ID_8: {
      /** @note delte a node*/
      tree.deleteNode(getName(name));
      break;
    }
      
    case OPID::ID_9: {
      /** @note number of nodes in BST*/
      tree.numberOfNodes();
      break;
    }
      
    case OPID::ID_10: {
      /** @note  number of internal nodes*/
      tree.numberOfInternalNodes();
      break;
    }
      
    case OPID::ID_11: {
      /** @note number of nodes @ level*/
      tree.numberOfNodesAtLevel(getLevel(level));
      break;
    }
      
    case OPID::ID_12: {
      /** @note get height*/
      tree.findHeight();
      break;
    }
      
    case OPID::ID_13: {
      /** @note is the BST balanced*/
      tree.isBalanced();
      break;
    }
      
    case OPID::ID_14: {
      /** @note destroy the tree*/
      tree.destroyTree();
      break;
    }
      
    case OPID::ID_15: {
      /** @note quit*/
      tree.destroyTree();
      goodbye();
      exit(EXIT_FAILURE);
      break;
    }
      
    case OPID::ID_16: {
      /** @note run tests*/
      tree.test();
      break;
    }
      
    default: {
      /** @note do nothing...*/
    }
    }
  }
  return EXIT_SUCCESS;
}
