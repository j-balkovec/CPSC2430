/**
 * @file Lab1.cpp [Driver Code]
 * @brief The purpose of this lab is to work with nested for-loops
 * We will make an implementation of a Pascals triangle which is used to
 * find the coeficients of a binomial expression
*/

#include <iostream>
#include <iomanip> //for setw()

int const WIDTH = 2;

/**
 * @brief Handles the memory for the pascals triangle, as well as gets the value from it
 * @param n Degree of the polinomial
 * @param i Index
 * @return result, which is the coeficient at the index
 */
int bico(int n, int i) {
    int** triangle = new int*[n+1]; //1Dimension
    for (auto j = 0; j <= n; j++) {
        triangle[j] = new int[j+1]; //Second dimension
        triangle[j][0] = 1; //first value in triangle
        for (auto k = 1; k < j; k++) {
            triangle[j][k] = triangle[j-1][k-1] + triangle[j-1][k]; //getting the values in the triangle
        }
        triangle[j][j] = 1; //last value in triangle
    }
    int result = triangle[n][i]; //getting the coeficent at index
    for (auto j = 0; j <= n; j++) {
        delete[] triangle[j]; //deallocate the first dimension
    }
    delete[] triangle; //dealocate last dimension
    return result;
}


/**
 * @brief Prints the Pascla's triangle
 * @param n Degree of the polinomial
 * @param i Index
 */
void print_pascal(int n, int i) {
    std::cout << "The Pascal Triangle up to degree " << n << " is:" << std::endl << std::endl;
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= j; k++) {
          std::cout << std::setw(WIDTH) <<bico(j, k) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void title() {
  std::cout << "\n\n************* PASCAL'S TRIANGLE *************\n\n";
}

/**
 * @brief Gets the input form the user
 * @param n Degree of the polinomial
 * @param i Index
 */
void get_input(int &n, int &i) {
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
void print_coeficient(int n, int i) {
    std::cout << "The coefficient at index [" << i << "] is: [" << bico(n, i) << "]" << std::endl;
    std::cout << std::endl << std::endl;
}
int main() {
  std::cout << std::endl << std::endl;
  /// @brief variable declarations
    int n = 0; //degree of the polinomial
    int i = 0; //index
  /// @brief variable declarations

  ///@brief function calls
    get_input(n, i); //gets input
    title(); //prints title
    print_pascal(n, i); //prints the triangle
    print_coeficient(n, i);
  ///@brief function calls


    return EXIT_SUCCESS;
}