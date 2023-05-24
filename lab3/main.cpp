/**
 * @author Jakob Balkovec
 * @file main.cpp [Driver Code]
 * @note Driver code for lab3
 * 
 * @brief This assigment focuses on using basic operations like:
 *   - Insertion
 *   - Traversals
 *   - Searching
 * On binary search trees (BST)
 * 
 * Those operations were implemented using a ShelterBst class that includes a struct for Pets and
 * A struct for the TreeNodes.  
 */

#include <iostream>
#include <string>
#include "ShelterBST.h"

#pragma message("[" __FILE__"] " "Last compiled on [" __DATE__ "] at [" __TIME__"]")


/** void fillTree()
 * @brief Fills the binary search tree with test data.
 * Creates an array of pet names and an array of ages, and then inserts them into the binary search tree using the insertPet function.
 * This function is intended to be used for testing purposes to quickly populate the tree with data.
 * @param tree The binary search tree to fill with test data.
 */
void fillTree(ShelterBST &tree) {
  /** 
   * @note random names I pulled of the web
   * @link https://www.southernliving.com/most-popular-pet-names-rover-6829769
   */
  std::string petNames[] = {"Budo", "Luna", "Char", "Maxy", "Coop", 
                            "Milo", "Rock", "Bitt", "Bark", "Lucy", 
                            "Rexy", "Zeus", "Rose", "Ruby", "Loop"};
  
  /** @note numbers are randomized so it's not a Linked List*/
  int numbers[] = {8, 4, 2, 1, 3, 6, 5, 7, 12, 10, 9, 11, 14, 13, 15}; 
  
  for(int i = 0; i <= 14; i++) { /** @note Age, Name[Test Values]*/
    std::string name = petNames[i];
    int age = numbers[i];
    tree.insertPet(name, age);
  }
}

/** @name void displayTraversal()
 * @brief Displays the different traversals of the binary search tree.
 * @param tree the binary search tree to be traversed and displayed
 */
void displayTraversal(ShelterBST &tree) {
  /** @note In-Order Traversal*/
  tree.inOrderDisplay();
  
  /** @note Post-Order Traversal*/
  tree.postOrderDisplay();
  
  /** @note Pre-Order Traversal*/
  tree.preOrderDisplay();
}


/** @name void searchTree()
 * @brief Searches for pets in the ShelterBST tree.
 * @param tree The ShelterBST tree object.
 */
void searchTree(ShelterBST &tree) {
  /** @note Sucessful search*/
  tree.searchPet(10);
  
  /** @note Un-Sucessfull search*/
  tree.searchPet(100);
}

/** @name main() 
 * @brief Main function that creates an instance of ShelterBST and performs operations on it.
 * @return EXIT_SUCESS upon successful execution.
 */
int main() {
  ShelterBST bst; /** @note create a ShelterBST instance*/
  
  /** @note add values*/
  fillTree(bst);
  
  /** @note print 3 traversals*/
  displayTraversal(bst);
  
  /** @note search in tree*/
  searchTree(bst);

  return EXIT_SUCCESS;
}
