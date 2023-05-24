/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file shelterBST.h -> @headerfile
 * @brief ShelterBST class variables and methods declaration
 */

#ifndef SHELTERBST_H
#define SHELTERBST_H

#include <string>
#include <vector>
#include <unordered_map>

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
  struct TreeNode* insert(struct TreeNode* &root, Pet *pet);
  struct TreeNode* search(struct TreeNode* root, std::string name);
  struct TreeNode* findParent(struct TreeNode* root, std::string name);
  struct TreeNode* findPredecessor(struct TreeNode* root, std::string name);
  struct TreeNode* deleteNode(struct TreeNode* root, std::string name);
  struct TreeNode* destroyTree(struct TreeNode* root);

  void searchHelper(struct TreeNode* &node1, struct TreeNode* &node2, std::string name);
  void inOrder(struct TreeNode* root);
  void postOrder(struct TreeNode* root);
  void preOrder(struct TreeNode* root);
  void copyHelper(TreeNode* root);
  
  int numberOfChildren(struct TreeNode* root, std::string name);
  int numberOfNodes(struct TreeNode* root);
  int numberOfInternalNodes(struct TreeNode* root);
  int numberOfNodesAtLevel(struct TreeNode* root, int level);
  int findHeight(struct TreeNode* root);
  
  bool isBalanced(struct TreeNode* root);
  
  void findPredecessorHelper(struct TreeNode* root, std::vector<std::string> &names);
  void preOrderHelper(struct TreeNode* root, std::vector<std::string> &names);
  void postOrderHelper(struct TreeNode* root, std::vector<std::string> &names);

  /** @note Methods END*/

  /** @note tests*/
  bool testSearch();
  bool testSearchB();
  bool testInsert();
  bool testFindParent();
  bool testFindPredecessor();
  bool testDeleteNode();
  bool testDestroyTree();
  bool testNumberOfChildren();
  bool testNumberOfNodes();
  bool testNumberOfInternalNodes();
  bool testHeight();
  bool testBalance();
  bool testNodesAtLevel();
  bool testInOrder();
  bool testPreOrder();
  bool testPostOrder();
  std::vector<bool> runAllTests(std::vector<bool> &testResults);
  /** @note tests END*/
  
public:
  /** @note Methods*/
  ShelterBST(); //constructor
  ~ShelterBST(); //destructor
  ShelterBST(const ShelterBST& other); //copy constructor
  ShelterBST& operator=(const ShelterBST& other);
  
  void inOrderDisplay(); 
  void preOrderDisplay(); 
  void postOrderDisplay(); 
  void insertPet(std::string name, int age);
  void findInorderPredecessor(std::string name);
  void findParent(std::string name);
  void searchPet(std::string name);
  void deleteNode(std::string name);
  void numberOfNodes();
  void numberOfInternalNodes();
  void numberOfNodesAtLevel(int level);
  void findHeight();
  void isBalanced();
  void destroyTree();
  /** @note Methods END*/

  void test();
};


#endif //SHELTER_BST
