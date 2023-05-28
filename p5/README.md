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

