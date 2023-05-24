/**
 * @file Lab1.cpp [Driver Code]
 * @brief The purpose of this lab is to work with recursion and big O notation
 * We will make an implementation of a Pascals triangle which is used to
 * find the coeficients of a binomial expression
*/

#include <iostream>
#include <iomanip> //for setw()
#include <chrono>

using namespace std::chrono;

int const WIDTH = 2;

/**
 * @brief Creates an iterative implementation of Pascal's triangle.
 * @param degree Degree of the polynomial.
 * @return A 2D array representing Pascal's triangle.
 * @remark The caller of this function is responsible for freeing the memory
 */
int** iterativePascal(int degree) {
    int** triangle = new int*[degree+1];
    for (auto j = 0; j <= degree; j++) {
        triangle[j] = new int[j+1];
        triangle[j][0] = 1;
        for (auto k = 1; k < j; k++) {
            triangle[j][k] = triangle[j-1][k-1] + triangle[j-1][k];
        }
        triangle[j][j] = 1;
    }
    return triangle;
}

/**
 * @brief Computes a binomial coefficient using Pascal's triangle.
 * @param n The degree of the polynomial.
 * @param i The index of the coefficient.
 * @return The binomial coefficient.
 */
int bico(int n, int i) {
    int** triangle = iterativePascal(n);
    int result = triangle[n][i];
    for (auto j = 0; j <= n; j++) {
        delete[] triangle[j];
    }
    delete[] triangle;
    return result;
}

/**
 * @brief Computes a binomial coefficient recursively.
 * @param degree Degree of the polynomial.
 * @param index Index of the coefficient.
 * @return The binomial coefficient.
 */
int recursiveBico(int degree, int index) {
    if (index == 0 || index == degree) {
        return 1;
    }
    else {
        return recursiveBico(degree-1, index-1) + recursiveBico(degree-1, index);
    }
}

/**
 * @brief Creates a recursive implementation of Pascal's triangle.
 * @param degree Degree of the polynomial.
 * @return A 2D array representing Pascal's triangle.
 * @remark The caller of this function is responsible for freeing the memory
 */
int** recursivePascal(int degree) {
    int** triangle = new int*[degree+1];
    for (auto i = 0; i <= degree; i++) {
        triangle[i] = new int[i+1];
        for (auto j = 0; j <= i; j++) {
            triangle[i][j] = recursiveBico(i, j);
        }
    }
    return triangle;
}

/**
 * @brief Deletes a Pascal's triangle.
 * @param triangle The Pascal's triangle to delete.
 * @param degree Degree of the polynomial.
 */
void deleteTriangle(int** triangle, int degree) {
    for (auto i = 0; i <= degree; i++) {
        delete[] triangle[i];
    }
    delete[] triangle;
}

/**
 * @brief Prints the Pascla's triangle
 * @param n Degree of the polinomial
 * @param i Index
 */
void printPascal(int n, int i) {
    int** triangle = iterativePascal(n);
    std::cout << "The Pascal Triangle up to degree " << n << " is:" << std::endl << std::endl;
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= j; k++) {
          std::cout << std::setw(WIDTH) << triangle[j][k] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    deleteTriangle(triangle, n);
}

/**
 * @brief Prints the Pascla's triangle
 * @param n Degree of the polynomial
 * @param i Index
 */
void printRecursivePascal(int n, int i) {
    int** triangle = recursivePascal(n);
    std::cout << "The Pascal Triangle up to degree " << n << " is:" << std::endl << std::endl;
    for (auto j = 0; j <= n; j++) {
      for (auto k = 0; k <= j; k++) {
          std::cout << std::setw(WIDTH) << triangle[j][k] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    deleteTriangle(triangle, n);
}

/**
 * @brief Prints Lab 1 title
 */
void title1() {
  std::cout << "\n\n************* Lab 1 Iterative *************\n\n";
}

/**
 * @brief Prints Lab 2 title
 */
void title2() {
  std::cout << "\n\n************* Lab 2 Recursive *************\n\n";
}
/**
 * @brief Gets the input form the user
 * @param n Degree of the polinomial
 * @param i Index
 */
void getInput(int &n, int &i) {
    std::cout << "Enter the degree of the binomial: ";
    std::cin >> n;
    std::cout << "Enter the index of the coefficient you want to obtain: ";
    std::cin >> i;

    while(i > n) {
      std::cout << "The coefficient is invalid!\n";
      std::cout << "Re-enter the coefficient you want to obtain: ";
      std::cin >> i;
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the coeficient the user requested
 * @param n Degree of the polinomial
 * @param i Index
 */
void printCoeficient(int n, int i) {
    std::cout << "The coefficient at index [" << i << "] is: [" << bico(n, i) << "]" << std::endl;
    std::cout << std::endl << std::endl;
}
int main() {
  std::cout << std::endl << std::endl;

    // int n = 0; 
    // int i = 0;

    // getInput(n, i); //gets input

  ///@brief function calls lab1
    // title1();
    // printPascal(n, i);
    // printCoeficient(n, i);
  ///@brief function calls lab1

  ///@brief function calls lab2
    // title2();
    // printPascal(n, i);
    // printCoeficient(n, i);
  ///@brief function calls lab2

    ///@brief Time measuremnets
    auto start = high_resolution_clock::now();
    recursiveBico(30,15);
    auto stop = high_resolution_clock::now();

    auto duration = stop - start;
    auto duration_ns = duration_cast<nanoseconds>(duration);

    std::cout << "Time in nanoseconds: " << duration_ns.count() << std::endl;
    ///@brief Time measuremnets
    return EXIT_SUCCESS;
}
