# Radix Sort

Radix Sort is a non-comparative sorting algorithm that sorts integers by processing individual digits or groups of digits. It works by distributing the elements into different buckets based on their radix (base) and then repeatedly sorting the elements by each digit. This process is repeated until all digits have been considered, resulting in a fully sorted array.

## Time Complexity

The time complexity of Radix Sort depends on the number of digits `d` and the number of elements `n` in the array.

- Python:
  - Best Case: O(d * n)
  - Average Case: O(d * n)
  - Worst Case: O(d * n)
  
- JavaScript:
  - Best Case: O(d * n)
  - Average Case: O(d * n)
  - Worst Case: O(d * n)

- C++:
  - Best Case: O(d * n)
  - Average Case: O(d * n)
  - Worst Case: O(d * n)

## Space Complexity

The space complexity of Radix Sort is determined by the size of the input array `n`.

- Python:
  - Space Complexity: O(n)

- JavaScript:
  - Space Complexity: O(n)

- C++:
  - Space Complexity: O(n)


Feel free to modify the code as per your needs. All code was ran in VSCode with necessary extensions.

### Side Note:
  C++ offers templates, allowing algorithms to be written without specific data types, enabling parsing of any type into the
  algorithm. This is because C++ generates specialized code at compile-time. In contrast, Python and JavaScript are interpreted
  languages with dynamic typing, where variable types are determined at runtime based on values assigned to them. This
  flexibility allows Python and JavaScript to handle various data types but may sacrifice some performance optimizations
  compared to C++.
  
# Breadth-First Search [(BFS)](https://en.wikipedia.org/wiki/Breadth-first_search)

Breadth-First Search **(BFS)** is usually graph traversal algorithm (I implemented it on a BST) that explores all the branches of a tree in breadth-first order, visiting all the children of a branch before moving on to the next level. It uses a queue data structure to keep track of the nodes to visit.

## Time Complexity

The time complexity of BFS depends on the number of vertices `V` and the number of edges `E` in the graph.

- C++:
  - Time Complexity: O(V + E)

## Space Complexity

The space complexity of BFS is determined by the maximum number of vertices that can be in the queue at any given time, which depends on the size of the graph.

- C++:
  - Space Complexity: O(V)


# Depth-First Search [(DFS)](https://en.wikipedia.org/wiki/Depth-first_search)

Depth-First Search **(DFS)** is usually a graph traversal algorithm (I implemented it on a BST) that explores all the branches of a graph by going as deep as possible before backtracking. It uses a stack data structure to keep track of the nodes to visit.

## Time Complexity

The time complexity of DFS depends on the number of vertices `V` and the number of edges `E` in the graph.

- C++:
  - Time Complexity: O(V + E)

## Space Complexity

The space complexity of DFS is determined by the maximum number of vertices that can be in the stack at any given time, which depends on the size of the graph.

- C++:
  - Space Complexity: O(V)


# Trie

A [Trie](https://en.wikipedia.org/wiki/Trie), also known as a prefix tree, is a tree-like data structure that stores a collection of strings. It is particularly useful for efficient string searching and prefix matching. Each node in the trie represents a prefix or a complete word, and the children of a node represent the possible characters that can follow that prefix.

## Time Complexity

The time complexity of various operations in a Trie depends on the length of the strings `L` and the number of strings `N` stored in the trie.

- Insertion:
  - Time Complexity: O(L)

- Search:
  - Time Complexity: O(L)

- Delete:
  - Time Complexity: O(L)

## Space Complexity

The space complexity of a Trie is determined by the number of nodes in the trie and the length of the strings.

- C++:
  - Space Complexity: O(N * L)

Please note that the time and space complexity mentioned above are approximate and may vary based on implementation details. I didn't really care about the time/space complexity since my only goal was to implement it.


