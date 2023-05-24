/** DOCUMENTATION: 
 * 
 * @author Jakob Balkovec
 * @file ShelterBST.cpp [Source code]
 * @brief This is the source code file for my ShelterBST class.
 *        Defines all the private and public methods
 * @name Assignment 3
 */

#include <queue>
#include <string>
#include <iostream>
#include <vector>
#include "ShelterBST.h"
#include <unistd.h>
#include <stdexcept>

/** DOCUMENTATION: 
 * CONSTRUCTOR: @name ShelterBST::ShelterBST()
 * @brief 
 */
ShelterBST::ShelterBST() {
  root = nullptr; /** @note set root to NULL*/
}

/** DOCUMENTATION: 
 * DESTRUCTOR: @name ShelterBST::~ShelterBST()
 * @brief Handles the memory/ frees the resources allocated by the constructor
 * @call: calls the destroyTree() method to deallocate all the memory
 */
ShelterBST::~ShelterBST() {
  destroyTree(root); //call destroyTree
}

/** DOCUMENTATION:
 * COPYCONSTRUCTOR: @name ShelterBST::ShelterBST(const ShelterBST& other)
 * @brief Copy constructor for the ShelterBST class.
 * @param other The ShelterBST object to be copied.
 */
ShelterBST::ShelterBST(const ShelterBST& other) {
    root = nullptr;
    copyHelper(other.root);
}

/** DOCUMENTATION:
 * OPERATOR: @name ShelterBST& ShelterBST::operator=()
 * @brief Copy assignment operator for the ShelterBST class.
 * @param other The ShelterBST object to be copied.
 * @return The copied ShelterBST object.
 */
ShelterBST& ShelterBST::operator=(const ShelterBST& other) {
    if (this != &other) {
        destroyTree(root);
        root = nullptr;
        copyHelper(other.root);
    }
    return *this;
}

/** DOCUMENTATON:
 * PRIVATE: @name void ShelterBST::copyHelper() 
 * @brief Copies over all the Pets in a tree rooted at root to this tree.
 * @param root Pointer to the root of the tree to be copied
 */
void ShelterBST::copyHelper(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    insertPet(root->pet->name, root->pet->age);
    copyHelper(root->left);
    copyHelper(root->right);
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::insert() 
 * @brief Inserts a new node with a Pet object into the binary search tree.
 * @param root A pointer to the root of the binary search tree.
 * @param pet A pointer to the Pet object to be inserted into the binary search tree.
 * @return A pointer to the root of the binary search tree, after insertion.
 * @invariant This function assumes that the Pet objects in the tree are ordered by name.
 */
struct ShelterBST::TreeNode* ShelterBST::insert(struct TreeNode*& root, Pet *pet) {
  /** @note if tree is empty create a new node*/
  if(root == nullptr) {
    root = new TreeNode;
    root -> pet = pet;
    /** @note L and R are NULL if just creted*/
    root -> right = nullptr;
    root -> left = nullptr;
  }
  
  /** @note go left*/
  else if (pet -> name < root -> pet -> name) {
    root->left = insert(root->left, pet);
  }
  
  /** @note go right*/
  else if (pet -> name > root -> pet -> name) {
    root->right = insert(root->right, pet);
  }
  
  /** @note handle duplicates*/
  /** @bug TEST:*/
  else {
      TreeNode* existingPet = search(root, pet -> name);
      if (existingPet != nullptr) {
        std::cout << "\n[A pet with this name already exists in the BST]\n";
        return root;
    }
  }
  return root;
} 

/** DOCUMENTATION: 
 * PUBLIC: @name ShelterBST::insertPet()
 * @brief Inserts a new pet into the binary search tree
 * @param name Name of the pet to be inserted
 * @param age Age of the pet to be inserted
 * @return void-type
 */
void ShelterBST::insertPet(std::string name, int age) {
  root = insert(root, new Pet(name, age));
  /** @note handle memory... IN THE END*/
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::search() 
 * @brief Searches for a node with a Pet object of the given age in the binary search tree.
 * @param root A pointer to the root of the binary search tree.
 * @param name The name of the Pet object to search for in the binary search tree.
 * @return A pointer to the node with the Pet object of the given age, or nullptr if it does not exist in the tree. 
 * @invariant This function assumes that the Pet objects in the tree are ordered by name.
 */
struct ShelterBST::TreeNode* ShelterBST::search(struct TreeNode* root, std::string name) {
  if(root == nullptr || root -> pet -> name == name) {
    return root;
  }
  
  /** @note go left if greater*/
  else if(name < root -> pet -> name) {
    return search(root -> left, name);
  }
  
  /** @note go right if less*/
  else {
    return search(root -> right, name);
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::findParent()
 * @brief Finds the parent node of a given node in the binary search tree
 * @param root Root node of the tree
 * @param name Name of the node whose parent is to be found
 * @return Pointer to the parent node, or nullptr if no parent is found
 * @note This function is called recursively to search for the parent of the given node
 */
 /** @bug
  * Returns A is the parent of B when inserted in the following order -> B, A, C
 */
struct ShelterBST::TreeNode* ShelterBST::findParent(struct TreeNode* root, std::string name) {
  if(root == nullptr) {
    return nullptr; /** @note no tree*/
  }
  
  if(root -> pet -> name == name) {
    return root; /** @note the first node is the one we're looking for*/
    /** @note return nullptr*/
  }
  
  /** @note left side using a recursive approach*/
  if(name < root -> pet -> name && root -> left != nullptr) {
    if(root -> left -> pet -> name == name) {
      return root; 
    } else {
      return findParent(root -> left, name);
    }

  /** @note right side using a recursive approach*/
  }else if(name > root -> pet -> name && root -> right != nullptr) {
    if(root -> right -> pet -> name == name) {
      return root;
    } else {
      return findParent(root -> right, name);
    }
  }
  return nullptr;
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::searchPet()
 * @brief Searches for a pet with the given name in the binary search tree
 * @param name Name of the pet to search for
 * @return Pointer to the node containing the pet, or nullptr if the pet is not found
 */
void ShelterBST::searchPet(std::string name) {
  TreeNode* found = search(root, name);
  if(found == nullptr) {
    std::cout << "\n\n[[nullptr] was returned -> A Pet with the name " << found -> pet -> name << " is [NOT] in the BST]\n\n";
  } else {
    std::cout << "\n[A Pet with the name \"" << found->pet->name << "\" [IS] in the BST]\n";

  }
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::findParent() 
 * @brief Finds the parent node of a pet with the given name in the binary search tree
 * @param name Name of the pet whose parent node is to be found
 * @return Pointer to the parent node of the pet, or nullptr if the pet is not found or is the root node
 */
void ShelterBST::findParent(std::string name) {
  TreeNode* parent = findParent(root, name);
  if(parent == nullptr) {
    std::cout << "\n[[" << name << "] does not have a parent]\n";
  }
  std::cout << "\n[The Parent of: [" << name << "] is [" << parent -> pet -> name << "]]\n";
}

/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::preOrderHelper()
 * @brief Recursive helper function that psuhes valeus into a vector
 * @param root Pointer to the root node of the current subtree
 * @param names Vector of pet names representing the current subtree in in-order traversal
 * @remark These functions enable testing later on
 */
 void ShelterBST::preOrderHelper(struct TreeNode* root, std::vector<std::string> &names) {
  if(root == nullptr) {
    return;
  } else if(root != nullptr) {
    preOrderHelper(root -> left, names);
    preOrderHelper(root -> right, names);
    names.push_back(root -> pet -> name);
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::postOrderHelper()
 * @brief Recursive helper function that psuhes valeus into a vector
 * @param root Pointer to the root node of the current subtree
 * @param names Vector of pet names representing the current subtree in in-order traversal
 * @remark These functions enable testing later on
 */
void ShelterBST::postOrderHelper(struct TreeNode* root, std::vector<std::string> &names) {
  if(root == nullptr) {
    return;
  } else if(root != nullptr) {
    names.push_back(root -> pet -> name);
    postOrderHelper(root -> left, names);
    postOrderHelper(root -> right, names);
  }
}
/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::findPredecessorHelper()
 * @brief Recursive helper function for finding the predecessor of a pet with the given name in the binary search tree
 * @param root Pointer to the root node of the current subtree
 * @param names Vector of pet names representing the current subtree in in-order traversal
 */
void ShelterBST::findPredecessorHelper(struct TreeNode *root, std::vector<std::string> &names) {
  /** @brief modifiying the inOrder() traversal so it pushes the values into a vector
   *         from there we can find the predecessor as stated in the PDF File
   */
  
  if(root == nullptr) {
    return;
  } else if(root != nullptr) {
    findPredecessorHelper(root -> left, names);
    names.push_back(root -> pet -> name);
    findPredecessorHelper(root -> right, names);
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::findPredecessor()
 * @brief Finds the predecessor of a node in the BST
 * @param root The root of the BST
 * @param name The name of the node whose predecessor is to be found
 * @return A pointer to the predecessor node in the BST
 * @invariant This function assumes that the BST contains the node with the given name
 */
struct ShelterBST::TreeNode* ShelterBST::findPredecessor(struct TreeNode* root, std::string name) {
  //traverse in order, push values into a vector, find predecessor
  
  std::vector<std::string> namesInBST; /** @note empty vecotr*/
  findPredecessorHelper(root, namesInBST); /** @note pushback*/
  
  /** @note search for the predecessor*/
  std::string storedName;
  for(long unsigned int i = 0; i < namesInBST.size(); i++) {
    if(namesInBST[0] == name) {
      return nullptr; /** @note first element's predecessor in NULL*/
    }
    else if(namesInBST[i] == name) {
      storedName = namesInBST[i-1]; /** @note segfaulting here [i-1]*/
    }
  }
  TreeNode* preDecessorNode = search(root, storedName);
  
  return preDecessorNode;
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::findInorderPredecessor()
 * @brief Finds the in-order predecessor of the node with the given name.
 * @param name The name of the node whose in-order predecessor is to be found.
 * @return void-type
 */
void ShelterBST::findInorderPredecessor(std::string name) {
  TreeNode* node = findPredecessor(root, name); /** @note change back to name*/
  if(node == nullptr) {
    std::cout << "\n[\"" << name << "\" does [NOT] have a predecessor]\n";
    return;
  } else {
  std::cout << "\n[The Predecessor of [" << name << "] is: [" << node -> pet -> name << "]\n";
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name int ShelterBST::numberOfChildren()
 * @brief Counts the number of children of a given node with the given name.
 * @param root Pointer to the root node of the BST.
 * @param name Name of the pet whose children are to be counted.
 * @return The number of children of the node with the given name.
 * @note Returns 0 if there is no tree or if the node with the given name is not found.
 */
int ShelterBST::numberOfChildren(struct TreeNode* root, std::string name) {
  if(root == nullptr) {
    return 0; /** @note no tree*/
  }
  TreeNode* node = search(root, name);
  if(node == nullptr) {
    /** @note node not found*/
    return 0;
  }
  int numOfChildren = 0;
  if(node -> left != nullptr) {
    numOfChildren++;
  }
  if(node -> right != nullptr) {
    numOfChildren++;
  }  
  return numOfChildren;
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::deleteNode()
 * @brief Deletes a node with the given name from the tree
 * @param root A pointer to the root of the tree.
 * @param name The name of the node to delete.
 * @return A pointer to the root of the updated tree.
 */

/**
 * BUG: Segufaulting if I delete the predecessor before the root
 */
struct ShelterBST::TreeNode* ShelterBST::deleteNode(struct TreeNode* root, std::string name) {

  /** @note find predecessor if it has 2 children*/
  /** @note delete and link grandchild if only one child*/
  /** @note delete if no children*/

  /** @note parent is inacessible -> segafulting here*/

  int const NO_CHILDREN = 0;
  int const ONE_CHILD = 1;
  int const TWO_CHILDREN = 2;

  /** @note tree is empty*/
  if(root == nullptr) {
    return root;
  }

  TreeNode* toBeDeleted = search(root, name);

  if(toBeDeleted == nullptr) {
    return root; /** @note node not found*/
  }

  /** @note no children*/
  if(numberOfChildren(root, name) == NO_CHILDREN) {
    if(toBeDeleted == root) {
      delete toBeDeleted;
      return nullptr; //idk if thats right
    }
    TreeNode* parent = findParent(root, toBeDeleted -> pet -> name);
      if(toBeDeleted == parent -> left) {
        parent -> left = nullptr;
      } else {
        parent -> right = nullptr;
      }
      delete toBeDeleted;
  }

  else if(numberOfChildren(root, name) == ONE_CHILD && !toBeDeleted -> left) { /** @note != nullptr*/
    if(toBeDeleted == root) {
      TreeNode* temp = root -> right;
      delete root;
      return temp;
    }
    TreeNode* parent = findParent(root, toBeDeleted -> pet -> name);
    if(toBeDeleted == parent -> left) {
      parent -> left = toBeDeleted -> right;
    } else {
      parent -> right = toBeDeleted -> right;
    }
    delete toBeDeleted;
  }

  else if(numberOfChildren(root, name) == ONE_CHILD && !toBeDeleted -> right) {
    if(toBeDeleted == root) {
      TreeNode* temp = root -> right;
      delete root;
      return temp;
    }
    TreeNode* parent = findParent(root, toBeDeleted -> pet -> name);
    if(toBeDeleted == parent -> left) {
      parent -> left = toBeDeleted -> left;
    } else {
      parent -> right = toBeDeleted -> left;
    }
    delete toBeDeleted;
  }  

  else if(numberOfChildren(root, name) == TWO_CHILDREN) {
    TreeNode* predecessor = findPredecessor(root, toBeDeleted -> pet -> name);
    while(predecessor -> right != nullptr) {
      predecessor = predecessor -> right;
      toBeDeleted -> pet -> name = predecessor -> pet -> name;
      toBeDeleted -> left = deleteNode(toBeDeleted -> left, predecessor -> pet -> name);
    }
  }
  return root;
}

/** DOCUMENTATION: 
 * PRIVATE: @name struct ShelterBST::TreeNode* ShelterBST::destroyTree()
 * @brief Recursively deletes all nodes in the tree.
 * @return A null pointer.
 * @param root Pointer to the root of the tree.
 * @note This is a private member function.
 */
struct ShelterBST::TreeNode* ShelterBST::destroyTree(struct TreeNode* root) {
  /** @note using recursion to delete the tree*/
  /** @note base case*/
  if(root == nullptr) {
    return nullptr;
    
    /** @note recursive case*/
  } else {
    destroyTree(root -> left);
    destroyTree(root -> right);
    delete root -> pet;
    delete root;
    return nullptr;
  }
  return nullptr;
}

/** DOCUMENTATION:
 * PUBLIC: @name void ShelterBST::deleteNode()
 * @brief Deletes the node with the specified name from the BST
 * @param name The name of the pet in the node to be deleted.
 */
void ShelterBST::deleteNode(std::string name) {
  TreeNode* deleted = deleteNode(root, name);
  if(search(root, deleted -> pet -> name) == nullptr) {
    std::cout << "\nNode with the name: [" << name << "] was deleted]\n";
    } else {
      std::cout << "\n[Soemthing went wrong]\n";
    }
  }

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::destroyTree()
 * @brief Calls destroy tree to destroy and deallocated the memory used by the BST
 */
void ShelterBST::destroyTree() {
  root = destroyTree(root);
  if(root != nullptr) {
    std::cout << "\n[Something went wrong]\n";;
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::inOrder() 
 * @brief Traverses the binary search tree in-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by name.
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
    std::cout << "Name: [" << root -> pet -> name << "]   " << "Age: [" << root -> pet -> age << "]" << std::endl;
    
    /** @note right sub-tree*/
    inOrder(root -> right);
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::postOrder()
 * @brief Traverses the binary search tree in post-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by name.
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
    std::cout << "Name: [" << root -> pet -> name << "]   " << "Age: [" << root -> pet -> age << "]" << std::endl;
  }
}

/** DOCUMENTATION: 
 * PRIVATE: @name void ShelterBST::preOrder()
 * @brief Traverses the binary search tree in pre-order, printing the name and age of each Pet object.
 * @param root A pointer to the root of the binary search tree.
 * @invariant This function assumes that the Pet objects in the tree are ordered by name.
 */
void ShelterBST::preOrder(struct TreeNode* root) {
  if(root == nullptr) {
    return; /** @note do nothing*/
    
  }else if(root != nullptr){
    /** @note cout first*/
    std::cout << "Name: [" << root -> pet -> name << "]   " << "Age: [" << root -> pet -> age << "]" << std::endl;
    
    /** @note left sub-tree*/
    postOrder(root -> left);
    
    /** @note right sub-tree*/
    postOrder(root -> right);
  }
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::inOrderDisplay() 
 * @brief Displays the contents of the binary search tree using in-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::inOrderDisplay() {
  std::cout << "\n[In-Order Traversal]";
  std::cout << std::endl << std::endl; 
  inOrder(root);
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::preOrderDisplay()
 * @brief Displays the contents of the binary search tree using pre-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::preOrderDisplay() {
  std::cout << "\n[Pre-Order Traversal]";
  std::cout << std::endl << std::endl;  
  preOrder(root);
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::postOrderDisplay()
 * @brief Displays the contents of the binary search tree using post-order traversal.
 * @call: calls the corresponding private method
 */
void ShelterBST::postOrderDisplay() {
  std::cout << "\n[Post-Order Traversal]";
  std::cout << std::endl << std::endl;
  postOrder(root);
}

/** DOCUMENTATION: 
 * PRIVATE: @name int ShelterBST::numberOfNodes()
 * @brief Counts the number of nodes in the binary search tree rooted at the given node
 * @param root A pointer to the root node of the binary search tree
 * @return The number of nodes in the binary search tree rooted at the given node
 * @note This is a private member function
 */
int ShelterBST::numberOfNodes(struct TreeNode* root) {
  int leftSide = 0;
  int rightSide = 0;
  
  if(root == nullptr) {
    return 0; /** @note tree is empty*/
  }
  /** @note right side*/
  rightSide = numberOfNodes(root -> right);
  
  /** @note left side*/
  leftSide = numberOfNodes(root -> left);
  
  return 1 + leftSide + rightSide; /** @note recursive function call*/
}

/** DOCUMENTATION: 
 * PRIVATE: @name int ShelterBST::numberOfInternalNodes()
 * @brief Returns the number of internal nodes in the binary search tree.
 * @param root Pointer to the root node of the tree.
 * @return Integer representing the number of internal nodes in the tree.
 */
int ShelterBST::numberOfInternalNodes(struct TreeNode* root) {
  if(root == nullptr || (root -> left == nullptr && root -> right == nullptr)) {
    /** @note The tree doesn't exist or we reached a leaf node*/
    return 0; 
  }
  /** @note +1 cuz of root*/
  return 1 + numberOfInternalNodes(root -> left) + numberOfInternalNodes(root -> right); 
  /** @note recursive call*/
}

/** DOCUMENTATION: 
 * PRIVATE: @name int ShelterBST::numberOfNodesAtLevel()
 * @brief Counts the number of nodes at a given level in the binary search tree
 * @param root A pointer to the root node of the binary search tree
 * @param level An integer specifying the level at which to count the nodes
 * @return An integer specifying the number of nodes at the given level
 */

/** BUG:
 * Do I worry about parameter checking(level) -> validation
 * Idk if its working
 */
int ShelterBST::numberOfNodesAtLevel(TreeNode* root, int level) {
  if (root == nullptr) {
    return 0;
  } else if (level == 0) {
    return 1;
  } else {
    int count = 0;
    if (root->left && root->right) {
      count += numberOfNodesAtLevel(root->left, level - 1);
      count += numberOfNodesAtLevel(root->right, level - 1);
    } else if(root -> right && root -> left == nullptr) {
      count += numberOfNodesAtLevel(root -> right, level - 1);
    } else if(root -> left && root -> right == nullptr) {
      count += numberOfNodesAtLevel(root -> left, level - 1);
    }
    return count;
  }
}


/** DOCUMENTATION: 
 * PUBLIC: @name void Shelter::BSTnumberOfNodes()
 * @brief handles UI
 * @return void-type
 */
void ShelterBST::numberOfNodes() { 
  /** @note handle UI in main*/
  std::cout << "\n[The total number of nodes in the BST is: [" << numberOfNodes(root) << "]\n";
}

/** DOCUMENTATION: 
 * PUBLIC: @name void Shelter::BSTnumberOfInternalNodes()
 * @brief handles UI
 * @return void-type
 */
void ShelterBST::numberOfInternalNodes() {
  std::cout << "\n[The total number of internal nodes in the BST is: [" << numberOfInternalNodes(root) << "]]\n";
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::numberOfNodesAtLevel() 
 * @brief handles UI
 * @param level initger corrsponding to the level in a binary tree
 * @return void-type
 */
void ShelterBST::numberOfNodesAtLevel(int level) {
  int nodesAtLevel = numberOfNodesAtLevel(root, level);
  std::cout << "\n[The total number of nodes at level [" << level << "] is: [" << nodesAtLevel << "]]\n"; 
}

/** DOCUMENTATION: 
 * PRIVATE: @name int ShelterBST::findHeight()
 * @brief Calculates the height of the binary search tree starting from the given root node.
 * @param root A pointer to the root node of the binary search tree.
 * @return The height of the binary search tree. 
 * @note The height of the binary search tree is defined as the number of edges on the longest 
 * path from the root node to a leaf node in the tree.
 */
int ShelterBST::findHeight(struct TreeNode* root) {
  if (root == nullptr) {
    return 0;
  }
  int leftHeight = findHeight(root->left);
  int rightHeight = findHeight(root->right);
  return 1 + std::max(leftHeight, rightHeight); /** @note std::max() finds the maximum value in-between the two*/
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::isBalanced() 
 * @brief Check if the binary search tree is balanced.
 * @param root The root node of the binary search tree.
 * @return True if the binary search tree is balanced, false otherwise.
 */
bool ShelterBST::isBalanced(struct TreeNode* root) {
  /** @note find the height of each subtree recursively and compare -> call findHeight with subtrees as params
   * can't differ by more than one
   */
  
    if (root == nullptr) {
        return true;
    }
    int leftHeight = findHeight(root->left); /** @note L subtree*/
    int rightHeight = findHeight(root->right); /** @note R subtree*/
    if (abs(leftHeight - rightHeight) > 1) { /** @note using abs because it cant be negative */
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right); /** @note true if right and left subtree are balanced*/
}

/** DOCUMENTATION: 
 * PUBLIC: @name void ShelterBST::findHeight() 
 * @brief Handles UI
 * @return void-type
 */
void ShelterBST::findHeight() {
  std::cout << "\n[The height of the tree is: [" << findHeight(root) << "]\n"; 
}

/** DOCUMENTATION:
 * PUBLIC: @name void ShelterBST::isBalanced() 
 * @brief Handles UI
 * @return void-type
 */
void ShelterBST::isBalanced() {
  bool balanced = isBalanced(root);
  
  if(balanced) {
    std::cout << "\n[BST is balanced]\n";
  } else {
    std::cout << "\n[BST is [NOT] balanced]\n";
  }
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testSearch()
 * @brief Tests the search() function by checking if it returns nullptr for non-existent values.
 * @return Returns true if the search() function correctly returns nullptr for non-existent values, false otherwise.
 * @note Test 1A: Tests for non-existent values
 * @post If the value is not found in the BST, search() should return nullptr.
 * @note Assumes that user does not enter spaces for names.
*/
bool ShelterBST::testSearch() { //?1

  /** @note 
   *  - assuming user doesnt enter spaces for names
   *  - might not work idk yet
  */
  TreeNode* root = nullptr;

  TreeNode* node1 = search(root, "12");
  TreeNode* node2 = search(root, "18");
  TreeNode* node3 = search(root, "11");
  TreeNode* node4 = search(root, "4");
  TreeNode* node5 = search(root, "3");

  std::vector<TreeNode*> nodes;
  nodes.push_back(node1);
  nodes.push_back(node2);
  nodes.push_back(node3);
  nodes.push_back(node4);
  nodes.push_back(node5);

  for(auto node : nodes) { //== to for each loop in python (<3)
    if(node != nullptr) {
      std::cout << "\n *** TEST1 [Expected [nullptr] but got something else] *** \n";
      return false;
    }
  }
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testSearchB()
 * @brief Private function to test search() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testSearchB() { //?2
  TreeNode* root = nullptr;

  /** @note insert nodes*/
  root = insert(root, new Pet("D", 3));
  root = insert(root, new Pet("C", 5));
  root = insert(root, new Pet("R", 2));
  root = insert(root, new Pet("A", 1));

  TreeNode* exists = search(root, "D");
  TreeNode* exists2 = search(root, "R");
  if(exists == nullptr) {
    std::cout << "\n*** TEST2 [Expected [" << root << "] but got [nullptr]] *** \n";
    return false;
  } else if(exists -> pet -> name != "D") {
    std::cout << "\n*** TEST2 [Expected [\"D\"] but got " << exists -> pet -> name <<" *** \n";
  }

  if(exists2 == nullptr) {
    std::cout << "\n*** TEST2 [Expected [" << root << "] but got [nullptr]] *** \n";
    return false;
  } else if(exists2 -> pet -> name != "R") {
    std::cout << "\n*** TEST2 [Expected [\"\"] but got " << exists2 -> pet -> name <<" *** \n";
  }  

  /** @note deallocate*/
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testInsert() 
 * @brief Private function to test insert() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.m 
 * @return 
 */
bool ShelterBST::testInsert() { //?3
  TreeNode* root = nullptr;

  /** @note insert nodes*/
  root = insert(root, new Pet("D", 1));
  root = insert(root, new Pet("B", 2));
  root = insert(root, new Pet("A", 3));
  root = insert(root, new Pet("C", 4));
  root = insert(root, new Pet("F", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("E", 7));
  
  /** @note expected tree
        D
      /   \
     B     F
    / \    / \
   A   C  E   G         
  */

  if(root -> pet -> name != "D") { //A
    std::cout << "\n*** TEST2[A] [Expected [D] but got [" << root -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> right -> pet -> name != "F") { //B
    std::cout << "\n*** TEST2[B] [Expected [F] but got [" << root -> right -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> right -> left -> pet -> name != "E") { //C
    std::cout << "\n*** TEST2[C] [Expected [E] but got [" << root -> right -> left -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> right -> right -> pet -> name != "G") { //D
    std::cout << "\n*** TEST2[D] [Expected [G] but got [" << root -> right -> right -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> left -> pet -> name != "B") { //E
    std::cout << "\n*** TEST2[E] [Expected [B] but got [" << root -> left -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> left -> left -> pet -> name != "A") { //F
    std::cout << "\n*** TEST2[F] [Expected [A] but got [" << root -> left -> left -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> left -> right -> pet -> name != "C") { //G
    std::cout << "\n*** TEST2[G] [Expected [C] but got [" << root -> left -> right -> pet -> name << "]] ***\n";
    return false;
  }

  if(root -> left -> left -> left != nullptr) { //H
    std::cout << "\n*** TEST2[H] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> left -> left -> right != nullptr) { //I
    std::cout << "\n*** TEST2[I] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> left -> right -> left != nullptr) { //J
    std::cout << "\n*** TEST2[J] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> left -> right -> right != nullptr) { //K
    std::cout << "\n*** TEST2[K] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> right -> right -> right != nullptr) { //L
    std::cout << "\n*** TEST2[L] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> right -> right -> left != nullptr) { //M
    std::cout << "\n*** TEST2[M] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> right -> left -> right != nullptr) { //N
    std::cout << "\n*** TEST2[N] [Unexpected node found] ***\n";
    return false;
  }

  if(root -> right -> left -> left != nullptr) { //O
    std::cout << "\n*** TEST2[O] [Unexpected node found] ***\n";
    return false;
  }

  /** @note deallocate*/
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testFindParent()
 * @brief Private function to test findParent() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testFindParent() { //?4
  TreeNode* root = nullptr;
  Pet* pet1 = new Pet("C", 5);
  root = insert(root, pet1);

  Pet* pet2 = new Pet("B", 3);
  root = insert(root, pet2);

  Pet* pet3 = new Pet("D", 8);
  root = insert(root, pet3);

  Pet* pet4 = new Pet("J", 12);
  root = insert(root, pet4);

  Pet* pet5 = new Pet("A", 17);
  root = insert(root, pet5);

  TreeNode* resultOne = findParent(root, "D");
  if (resultOne->pet->name != "C") {
    return false; /** @test failed*/
    std::cout << "\n*** TEST4 [Expected \"C\" but got \"" << resultOne -> pet -> name << "\"] *** \n"; 
  }

  if (resultOne == nullptr) {
    std::cout << "\n*** TEST4 [Expected " << findParent(root, "C") << " but got [nullptr]] *** \n";
    return false; /** @test failed*/
  }

  destroyTree(root);
  return true; /** @test failed*/
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testFindPredecessor()
 * @brief Private function to test findPredecessor() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testFindPredecessor() { //?5
  TreeNode* root = nullptr;
  Pet* pet1 = new Pet("C", 5);
  root = insert(root, pet1);

  Pet* pet2 = new Pet("B", 3);
  root = insert(root, pet2);

  Pet* pet3 = new Pet("D", 8);
  root = insert(root, pet3);

  Pet* pet4 = new Pet("J", 12);
  root = insert(root, pet4);

  Pet* pet5 = new Pet("A", 17);
  root = insert(root, pet5);

  std::vector<std::string> names;
  findPredecessorHelper(root, names); 

  if (names.size() != 5 || names[0] != "A" || names[1] != "B" || names[2] != "C" || names[3] != "D" || names[4] != "J") {
    std::cout << "\n*** TEST5 [Expected <\"C\" \"B\" \"D\" \"J\" \"A\"> but got ";
    for(auto name : names) { //for name in names
      std::cout << "\"" << name << "\" ";
    }
    std::cout << ">] ***\n";
    return false; /** @test failed*/
  }

  TreeNode* predecessor = findPredecessor(root, "C");
  
  if(predecessor -> pet -> name != "B") {
    std::cout << "\n*** TEST5 [Expected \"B\" but got \"" << predecessor -> pet -> name << "\"] ***\n"; 
    return false;
  }
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testDeleteNode()
 * @brief Private function to test deleteNode() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testDeleteNode() { //?6
  TreeNode* root = nullptr;
  root = insert(root, new Pet("cat", 1));
  root = insert(root, new Pet("dog", 2));
  root = insert(root, new Pet("fish", 3));

  root = deleteNode(root, "dog");

  if (search(root, "dog") != nullptr) {
    std::cout << "\n*** TEST6 [Expected [nullptr] but got [" << search(root, "dog") << "]]\n ***"; 
    return false;
  }

  root = deleteNode(root, "cat");

  if (search(root, "cat") != nullptr) {
    std::cout << "\n*** TEST6 [Expected [nullptr] but got [" << search(root, "cat") << "]]\n ***"; 
    return false;
  }

  root = deleteNode(root, "fish");
  
  if(root != nullptr) {
    std::cout << "\n*** TEST6 [Expected [nullptr] but got [" << root << "]] ***\n";
    return false;
  }
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testDestroyTree()
 * @brief Private function to test destroyTree() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testDestroyTree() { //?7
  TreeNode* root = nullptr;
  root = insert(root, new Pet("D", 3));
  root = insert(root, new Pet("B", 2));
  root = insert(root, new Pet("A", 2));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("F", 2));
  root = insert(root, new Pet("G", 2));
  root = insert(root, new Pet("E", 2));

  root = destroyTree(root);

  if (root != nullptr) {
    std::cout << "\n*** TEST7 [Expected [nullptr] but got [" << root << "]] ***\n"; 
    return false;
  }
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testNumberOfChildren() 
 * @brief Private function to test numberOfChildren() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testNumberOfChildren() { //?8
  TreeNode* root = nullptr;
  root = insert(root, new Pet("D", 3));
  root = insert(root, new Pet("B", 2));
  root = insert(root, new Pet("A", 2));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("F", 2));
  root = insert(root, new Pet("G", 2));
  root = insert(root, new Pet("E", 2));
  root = insert(root, new Pet("Z", 2));
  
  int EQnumChildrenOne = 0;
  int EQnumChildrenTwo = 1;
  int EQnumChildrenThree = 2;

  int numChildrenRoot = numberOfChildren(root, "D"); //has 2 children
  if (numChildrenRoot != EQnumChildrenThree) {
    std::cout << "\n*** TEST8 [Expected [" << EQnumChildrenThree << "] but got [" << numChildrenRoot << "]] ***\n";
    return false;
  }

  int numChildrenLeaf = numberOfChildren(root, "C"); //has zero children
  if (numChildrenLeaf != EQnumChildrenOne) {
    std::cout << "\n*** TEST8 [Expected [" << EQnumChildrenOne << "] but got [" << numChildrenLeaf << "]] ***\n";
    return false;
  }

  int numChildrenHanging = numberOfChildren(root, "G"); //has one child
  if (numChildrenHanging != EQnumChildrenTwo) {
    std::cout << "\n*** TEST8 [Expected [" << EQnumChildrenThree << "] but got [" << numChildrenHanging << "]] ***\n";
    return false;
  }
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testNumberOfNodes() 
 * @brief Private function to test numberOfNodes() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testNumberOfNodes() { //?9
  TreeNode* root = nullptr;

  /** @note the tree is degenerate*/
  root = insert(root, new Pet("A", 1));
  root = insert(root, new Pet("B", 2));
  root = insert(root, new Pet("C", 3));
  root = insert(root, new Pet("D", 4));
  root = insert(root, new Pet("E", 5));
  root = insert(root, new Pet("F", 6));
  root = insert(root, new Pet("G", 7));
  root = insert(root, new Pet("H", 8));
  root = insert(root, new Pet("I", 9));
  root = insert(root, new Pet("J", 10));
  root = insert(root, new Pet("K", 11));
  root = insert(root, new Pet("L", 12));
  root = insert(root, new Pet("M", 13));
  root = insert(root, new Pet("N", 14));
  root = insert(root, new Pet("O", 15));
  root = insert(root, new Pet("P", 16));
  root = insert(root, new Pet("R", 17));
  root = insert(root, new Pet("S", 18));
  root = insert(root, new Pet("T", 19));
  root = insert(root, new Pet("U", 20));
  root = insert(root, new Pet("V", 21));
  root = insert(root, new Pet("Z", 22));
  root = insert(root, new Pet("Q", 23));

  int EQnumNodes = 23;
  int numNodes = numberOfNodes(root);

  if (numNodes != EQnumNodes) {
    std::cout << "\n*** TEST9 [Expected [" << EQnumNodes << "] but got [" << numNodes << "]] ***\n";
    return false;
  }
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testNumberOfInternalNodes()
 * @brief Private function to test numberOfInternalNodes() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testNumberOfInternalNodes() { //?10
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("Z", 7));

  int EQinternalNodes =  3;
  int internalNodes = numberOfInternalNodes(root);

  if(EQinternalNodes != internalNodes) {
    std::cout << "\n*** TEST10 [Expected [" << EQinternalNodes << "] but got [" << internalNodes << "]] ***\n";
    return false;
  }

  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testHeight() 
 * @brief Private function to test findHeight() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not. 
 */
bool ShelterBST::testHeight() { //?11
  TreeNode* root = nullptr;

  /** @note the tree is degenarate/sparse*/

  root = insert(root, new Pet("A", 1));
  root = insert(root, new Pet("B", 2));
  root = insert(root, new Pet("C", 3));
  root = insert(root, new Pet("D", 4));
  root = insert(root, new Pet("E", 5));
  root = insert(root, new Pet("F", 6));
  root = insert(root, new Pet("G", 7));
  root = insert(root, new Pet("H", 8));
  root = insert(root, new Pet("I", 9));
  root = insert(root, new Pet("J", 10));
  root = insert(root, new Pet("K", 11));
  root = insert(root, new Pet("L", 12));
  root = insert(root, new Pet("M", 13));
  root = insert(root, new Pet("N", 14));
  root = insert(root, new Pet("O", 15));
  root = insert(root, new Pet("P", 16));
  root = insert(root, new Pet("Q", 17));
  root = insert(root, new Pet("R", 18));
  root = insert(root, new Pet("S", 19));
  root = insert(root, new Pet("T", 20));
  root = insert(root, new Pet("U", 21));
  root = insert(root, new Pet("V", 22));
  root = insert(root, new Pet("W", 23));
  root = insert(root, new Pet("X", 24));
  root = insert(root, new Pet("Y", 25));
  root = insert(root, new Pet("Z", 26));

  int EQheight = 26;
  int height = findHeight(root);

  if(EQheight != height) {
    std::cout << "\n*** TEST11 [Expected [" << EQheight << "] but got [" << height << "]] *** \n";
    return false;
  }
  destroyTree(root);
  return true;  
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testBalance() 
 * @brief Private function to test isBalanced() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testBalance() { //?12
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("Z", 7));

  bool EQbalance = true;
  bool balance = isBalanced(root);

  if(EQbalance != balance) {
    /** @note boolalpha -> prints true and flase isnstead of 1 and 0*/
    std::cout << std::boolalpha << "\n *** TEST12 [Expected [" << EQbalance << "] but got [" << balance << "]] ***\n";
    return false;
  }
  destroyTree(root);
  return true;    
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testNodesAtLevel()
 * @brief Private function to test nodesAtLevel() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testNodesAtLevel() { //?13
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("R", 13));
  root = insert(root, new Pet("Z", 7));

  int EQnodesAtLevelZero = 1; //root
  int EQnodesAtLevelOne = 2; //root children
  int EQnodesAtLevelTwo = 4; //full -> perfect tree, splits to two more
  int EQnodesAtLevelThree = 1; //Z

  int nodesAtLevelZero = numberOfNodesAtLevel(root, 0);
  int nodesAtLevelOne = numberOfNodesAtLevel(root, 1);
  int nodesAtLevelTwo = numberOfNodesAtLevel(root, 2);
  int nodesAtLevelThree = numberOfNodesAtLevel(root, 3);

  if(EQnodesAtLevelZero != nodesAtLevelZero) {
    std::cout << "\n*** TEST13[A] [Expected [" << EQnodesAtLevelZero << "] but got [" << nodesAtLevelZero << "]] ***\n";
    return false;
  }

  if(EQnodesAtLevelOne != nodesAtLevelOne) {
    std::cout << "\n*** TEST13[B] [Expected [" << EQnodesAtLevelOne << "] but got [" << nodesAtLevelOne << "]] ***\n";
    return false;
  }

  if(EQnodesAtLevelTwo != nodesAtLevelTwo) {
    std::cout << "\n*** TEST13[C] [Expected [" << EQnodesAtLevelTwo << "] but got [" << nodesAtLevelTwo << "]] ***\n";
    return false;
  }

  if(EQnodesAtLevelThree != nodesAtLevelThree) {
    std::cout << "\n*** TEST13[D] [Expected [" << EQnodesAtLevelThree << "] but got [" << nodesAtLevelThree << "]] ***\n";
    return false;
  }      

  destroyTree(root);
  return true;   
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testInOrder()
 * @brief Private function to test inOrder() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testInOrder() { //?14
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("Z", 7));

  std::vector<std::string> names;
  findPredecessorHelper(root, names);

  std::vector<std::string> EQ = {"B", "C", "D", "F", "G", "J", "Z"};

  if(names == EQ) { // == operator defined int the vector class (no need to iterate)
    return true;
  } else {
    for(auto i = 0; i < (int)names.size(); i++) {
      if(names[i] != EQ[i]) {
        std::cout << "\n*** TEST14 [Expected [" << EQ[i] << "] but got [" << names[i] << "]] ***\n";
        return false;
      }
    }
  }
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testPreOrder()
 * @brief Private function to test preOrder() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testPreOrder() { //?15
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("Z", 7));
  
  std::vector<std::string> names;
  preOrderHelper(root, names);

  std::vector<std::string> EQ = {"B", "D", "C", "G", "Z", "J", "F"};

  if(names == EQ) { // == operator defined int the vector class (no need to iterate)
    return true;
  } else {
    for(auto i = 0; i < (int)names.size(); i++) {
      if(names[i] != EQ[i]) {
        std::cout << "\n*** TEST14 [Expected [" << EQ[i] << "] but got [" << names[i] << "]] ***\n";
        return false;
      }
    }
  }
  destroyTree(root);
  return true;
}

/** DOCUMENTATION:
 * PRIVATE: @name bool ShelterBST::testPostOrder()
 * @brief Private function to test postOrder() method of ShelterBST class.
 * @return Returns a boolean value indicating whether the test has passed or not.
 */
bool ShelterBST::testPostOrder() { //?16
  TreeNode* root = nullptr;
  root = insert(root, new Pet("F", 1));
  root = insert(root, new Pet("C", 2));
  root = insert(root, new Pet("J", 3));
  root = insert(root, new Pet("B", 4));
  root = insert(root, new Pet("D", 5));
  root = insert(root, new Pet("G", 6));
  root = insert(root, new Pet("Z", 7));
  
  std::vector<std::string> names;
  postOrderHelper(root, names); 
  
  std::vector<std::string> EQ = {"F", "C", "B", "D", "J", "G", "Z"}; //Z

  if(names == EQ) { // == operator defined int the vector class (no need to iterate)
    return true;
  } else {
    for(auto i = 0; i < (int)names.size(); i++) {
      if(names[i] != EQ[i]) {
        std::cout << "\n*** TEST16 [Expected [" << EQ[i] << "] but got [" << names[i] << "]] ***\n";
        return false;
      }
    }
  }
  destroyTree(root);
  return true;
}

/** DOCUMENT:
 * PRIVATE: @name std::vector<bool> ShelterBST::runAllTests()
 * @brief Runs all tests on the ShelterBST object and returns a map of the test results.
 * @return An unordered map with the test results. The keys are strings representing the test names,
 * and the values are booleans indicating whether each test passed (true) or failed (false).
 */
std::vector<bool> ShelterBST::runAllTests(std::vector<bool> &testResults) {
  testResults.push_back(testSearch());
  testResults.push_back(testSearchB());
  testResults.push_back(testInsert()); 
  testResults.push_back(testFindParent());
  testResults.push_back(testFindPredecessor());
  testResults.push_back(testDeleteNode());
  testResults.push_back(testDestroyTree());
  testResults.push_back(testNumberOfChildren());
  testResults.push_back(testNumberOfNodes());
  testResults.push_back(testNumberOfInternalNodes());
  testResults.push_back(testHeight());
  testResults.push_back(testBalance()); 
  testResults.push_back(testNodesAtLevel()); 
  testResults.push_back(testInOrder());
  testResults.push_back(testPreOrder()); 
  testResults.push_back(testPostOrder());
  
  return testResults;
}

/** DOCUMENTATION:
 * PUBLIC: @name void ShelterBST::test()
 * @brief Runs tests for all the funcntions
 */
void ShelterBST::test() {
  using std::vector;
  #define PASS true //macro preprocessor directive
  #define FAIL false
  std::string const TEST = "*** TEST ";
  std::string const PASSED = "  PASSED ***";
  std::string const FAILED = "  - FAILED ###";
  std::string const PASSED_2 = " PASSED ***";
  std::string const FAILED_2 = " - FAILED ###";
  long int const PAUSE = 1000000;

  vector<bool> testValues;
  std::cout << "\n\n*** RUNNING ALL TESTS *** ";
  std::cout << std::flush; //flush the buffer or else usleep doesn't work
  usleep(PAUSE);
  runAllTests(testValues);
  std::cout << std::endl << std::endl;
  for(auto i = 0; i < (int)testValues.size(); i++) {
    if(testValues[i] == PASS && i < 9) { /** @bug fail and pass*/
      std::cout << TEST << i+1 << PASSED << std::endl;

    } else if(testValues[i] == FAIL && i < 9) {
      std::cout << TEST << i+1 << FAILED << std::endl;

    } else if(testValues[i] == PASS && i > 9) {
      std::cout << TEST << i+1 << PASSED_2 << std::endl;

    } else if(testValues[i] == FAIL && i > 9) {
      std::cout << TEST << i+1 << FAILED_2 << std::endl;
    }
  }
}
