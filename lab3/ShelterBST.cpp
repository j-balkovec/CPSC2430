/**
 * @author Jakob Balkovec
 * @file ShelterBST.cpp [Driver Code]
 * @note Source code for lab3
 * 
 * @brief This assigment focuses on using basic operations like:
 *   - Insertion
 *   - Traversals
 *   - Searching
 * On binary search trees (BST)
 * 
 * Those operations were implemented using a ShelterBst class that includes a struct for Pets and
 * A struct for the TreeNodes.  
 * 
 * @brief This file defines the public and private methods of the ShelterBST class
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "ShelterBST.h"

int const WIDTH = 4;

/** @name struct ShelterBST::TreeNode* ShelterBST::insert()
 * @brief Inserts a new node with a Pet object into the binary search tree.
 * 
 * @param root A pointer to the root of the binary search tree.
 * @param pet A pointer to the Pet object to be inserted into the binary search tree.
 * 
 * @return A pointer to the root of the binary search tree, after insertion.
 * 
 * @invariant This function assumes that the Pet objects in the tree are ordered by age.
 * @invariant No duplicates are being provided
 */

struct ShelterBST::TreeNode* ShelterBST::insert(struct TreeNode* root, Pet *pet) {
  /** @note if tree is empty create a new node*/
  if(root == nullptr) { 
    root = new TreeNode;
    root -> pet = pet;
    /** @note L and R are NULL if just created*/
    root -> right = nullptr;
    root -> left = nullptr;
  } 
  /** @note go left*/
  else if (pet -> age < root -> pet -> age) {
    root -> left = insert(root -> left, pet);
  }
  /** @note go right*/
  else if(pet -> age > root -> pet -> age) {
    root -> right = insert(root -> right, pet);
  }
  else {
    /** @note DUPLICATE*/
  }
  
  return root;
}

/** @name struct ShelterBST::TreeNode* ShelterBST::search()
 * @brief Searches for a node with a Pet object of the given age in the binary search tree.
 * 
 * @param root A pointer to the root of the binary search tree.
 * @param age The age of the Pet object to search for in the binary search tree.
 * 
 * @return A pointer to the node with the Pet object of the given age, or nullptr if it does not exist in the tree.
 * 
 * @invariant This function assumes that the Pet objects in the tree are ordered by age.
 */
struct ShelterBST::TreeNode* ShelterBST::search(struct TreeNode* root, int age) {
  /** @note if tree doesn't exist or if te age mateches the age of the pet in the root*/
  if(root == nullptr || root -> pet -> age == age) {
    return root;
  }
  /** @note go left if greater*/
  else if(age < root -> pet -> age) {
    return search(root -> left, age);
  }
  /** @note go right if less*/
  else{
    return search(root -> right, age);
  }
}

/** @name void ShelterBST::inOrder()
 * @brief Traverses the binary search tree in-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by age.
 */

void ShelterBST::inOrder(struct TreeNode* root) {
  if(root == nullptr) {
    return; /** @note do nothing*/
  }
  /** @note traverse*/
  else if(root != nullptr) {
    /** @note left-sub tree*/
    inOrder(root -> left);
    
    /** @note cout data*/   
    std::cout << "Name: " << root -> pet -> name << " " << "Age: " << root -> pet -> age << std::endl;
    
    /** @note right sub-tree*/
    inOrder(root -> right);
  }
}

/** @name void ShelterBST::postOrder()
 * @brief Traverses the binary search tree in post-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by age.
 */
void ShelterBST::postOrder(struct TreeNode* root) {
  if(root == nullptr) {
    return; /** @note do nothing*/
  }
  else if(root != nullptr) {
    /** @note left sub-tree*/
    postOrder(root -> left);
    
    /** @note right sub-tree*/
    postOrder(root -> right);
    
    /** @note cout last*/
    std::cout << "Name: " << root -> pet -> name << " " << "Age: " << root -> pet -> age << std::endl; 
  }
}

/** @name void ShelterBST::preOrder()
 * @brief Traverses the binary search tree in pre-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by age.
 */
void ShelterBST::preOrder(struct TreeNode* root) {
  if(root == nullptr) {
    return; /** @note do nothing*/
    
  }else if(root != nullptr){
    /** @note cout first*/
    std::cout << "Name: " << root -> pet -> name << " " << "Age: " << root -> pet -> age << std::endl;
    
    /** @note left sub-tree*/
    postOrder(root -> left);
    
    /** @note right sub-tree*/
    postOrder(root -> right);
  }
}

/** @name CONSTRUCTOR: ShelterBST::ShelterBST()
 * @brief Creates a new BST
 * @post A new tree is created
 */
ShelterBST::ShelterBST() {
  root = nullptr; //create a tree
}

/** @name void ShelterBST::insertPet()
 * @brief Inserts a new Pet object with the given name and age into the binary search tree.
 * @call: Calls the insert function to insert the newly dynamically allocated Pet object
 * 
 * @param name The name of the new Pet object to be inserted.
 * @param age The age of the new Pet object to be inserted.
 * 
 * @note This function assumes that the Pet objects in the tree are ordered by age.
 */
void ShelterBST::insertPet(std::string name, int age) {
  /** @note insert pet, allocate memory for the pet object*/
  root = insert(root, new Pet(name, age));
}

/** @name void ShelterBST::searchPet()
 * @brief Searches for a Pet object in the binary search tree with the given age.
 * @param age The age of the Pet object to be searched for.
 * @note This function assumes that the Pet objects in the tree are ordered by age.
 */
void ShelterBST::searchPet(int age) {
  struct TreeNode* result = search(root, age);
  std::cout << std::endl;
  if(result == nullptr) {
    std::cout << "Pet aged [" << age << "] years could not be found in the shelter!" << std::endl;
  } else {
    std::cout << "Pet Name: [" << result -> pet -> name << "] Age: [" << result -> pet -> age << "] found in the shelter!" << std::endl; 
  }
}

/** @name void ShelterBST::inOrderDisplay()
 * @brief Displays the contents of the binary search tree using in-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::inOrderDisplay() {
  std::cout << "\n[In-Order Traversal]";
  std::cout << std::endl << std::endl; 
  inOrder(root);
}

/** @name void ShelterBST::preOrderDisplay()
 * @brief Displays the contents of the binary search tree using pre-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::preOrderDisplay() {
  std::cout << "\n[Pre-Order Traversal]";
  std::cout << std::endl << std::endl;  
  preOrder(root);
}

/** @name void ShelterBST::postOrderDisplay()
 * @brief Displays the contents of the binary search tree using post-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::postOrderDisplay() {
  std::cout << "\n[Post-Order Traversal]";
  std::cout << std::endl << std::endl;
  postOrder(root);
}
