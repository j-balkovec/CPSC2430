#include <iostream>
#include <queue>
#include <stack>

//{
// Tree node structure
//}
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//{
// Recursive Deapth First Search  
//}
void DFS(TreeNode* root) {
    if (root == nullptr)
        return;

    std::cout << root->val << " ";
    DFS(root->left);
    DFS(root->right);
}

// {
// Iterative Breadth First Search
// }
void BFS(TreeNode* root) {
  std::cout << "[ ";
    if (root == nullptr)
        return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        std::cout << current->val << " ";

        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
    std::cout << "]";
}

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);

  //{
    //      Tree:
    //        1
    //      /   \
    //     2     3
    //    / \   / \
    //   4   5 6   7
  //}

  std::cout << "\n[dfs]: [ ";
  DFS(root);
  std::cout << "]" << std::endl;

  std::cout << "\n[bfs]: ";
  BFS(root);
  std::cout << std::endl << std::endl;

  return EXIT_SUCCESS;
}
