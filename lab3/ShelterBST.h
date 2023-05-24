/**
 * @author Jakob Balkovec
 * @file shelterBST.h -> @headerfile
 * @brief ShelterBST class variables and methods declaration
 */

#include <string>

#ifndef SHELTERBST_H
#define SHELTERBST_H

/**
 * @class ShelterBST that defined the TreeNodes and the Pet instances
 */
class ShelterBST {
private: 
  
  /** @struct Pet, used to store the age and the naem of a pet in a shelter */
  struct Pet {
    std::string name;
    int age;
    Pet(std::string name = "", int age = 0) : name(name), age(age) {} //Constructor
  };
  
  /** @struct TreeNode, used to implement a tree
   * @members: 
   * Pet *pet -> pointer to a Pet object
   * TreeNode *left -> left child
   * TreeNode *right -> right child
   * 
   * @note noth develop in a new subtree if left or right != NULL
   */
  struct TreeNode {
    struct Pet *pet;
    struct TreeNode *left;
    struct TreeNode *right;
  };
  
  /** @note BST base*/
  struct TreeNode *root;
  
  /** @note Methods*/
  struct TreeNode* insert(struct TreeNode* root, Pet *pet);
  struct TreeNode* search(struct TreeNode* root, int age);
  void inOrder(struct TreeNode* root);
  void postOrder(struct TreeNode* root);
  void preOrder(struct TreeNode* root);
  /** @note Methods END*/
  
public:
  /** @note Methods*/
  ShelterBST(); //constructor
  void insertPet(std::string name, int age);
  void searchPet(int age);
  void inOrderDisplay(); //call private
  void preOrderDisplay(); //call private
  void postOrderDisplay(); //call private
  /** @note Methods END*/
};

#endif //SHELTERBST_H
