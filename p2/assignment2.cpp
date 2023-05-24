/**
 * @author Jakob Balkovec
 * @file main.cpp [Driver code]
 * @brief This assignment focuses on using recursion to solve various
 *        problems given in the description [pdf]
 * @name Assignment 2
 */

#include <iostream> //std::cin, std::cout
#include <stdexcept> //try catch throw blocks
#include <string> // std::string lib for decToBase2()
#include <limits> //limts for int overflow
#include <cmath> //std::sqrt()
#include <unistd.h> //usleep
#include <csignal> //signal handler
#include <cassert> //assert library
#include <unordered_map> //for testing

//g++ -std=c++11 -pedantic -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow -Wformat=2 -Wfloat-equal -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wdouble-promotion -Wformat-signedness -Wformat-truncation=2 -Wno-unused-result -Wcast-align -Wcast-qual -Wpadded -Wredundant-decls -Winline -Wvla -Woverloaded-virtual -Wold-style-cast -Wsign-promo -Wnon-virtual-dtor -Wmissing-include-dirs -Wdisabled-optimization -Wstack-protector -fstack-protector-strong -Wno-error=strict-overflow -O3 assignment2.cpp -o prog

/**
 * @brief 
 * PIMPED: OUT: COMPILATION: FLAGS: 
 * g++ -std=c++11 -pedantic -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wshadow 
 * -Wformat=2 -Wfloat-equal -Wduplicated-cond -Wlogical-op
 * -Wnull-dereference -Wdouble-promotion -Wformat-signedness -Wformat-truncation=2 
 * -Wno-unused-result -Wcast-align -Wcast-qual -Wpadded -Wredundant-decls -Winline 
 * -Wvla -Woverloaded-virtual -Wold-style-cast -Wsign-promo -Wnon-virtual-dtor 
 * -Wmissing-include-dirs -Wdisabled-optimization -Wstack-protector 
 * -fstack-protector-strong assignment2.cpp -o prog
 */

#pragma message("[" __FILE__"] " "Last compiled on [" __DATE__ "] at [" __TIME__"]")

int const CONVERGE = 18; //ramanujan const for the series
long int const PAUSE = 1000000; //usleep() const

/**
 * @enum for numbers of tests per runTest[n]() call
 */
enum Tests {
  TEST1NUM = 8,
  TEST2NUM = 6, 
  TEST3NUM = 6, 
  TEST4NUM = 7, 
  TEST5NUM = 10 
};

/**
 * @invariant The user will always provide an intiger upon calling any of the 5 functions
 */

/**
 * @note typedefing it for better readbility
 */
typedef std::numeric_limits<int32_t> limits;

/**
 * @brief Upper and lower limits for 32bit (4Byte) intiger
 */
const int32_t MAX = limits::max();


/** @name printMenu()
 * @brief The function prints a menu for the user
 * @remark Handles UI
 * @return void-type
 */
void printMenu() {
  std::cout << "\n\nWelcome to the recursion assigment. What would you like to test?\n"
            << "[1] mysterySequence\n"
            << "[2] tennisBalls\n"
            << "[3] decToBase2\n"
            << "[4] isDivisibleBy7\n"
            << "[5] ramanjuan\n"
            << "[6] Run tests\n"
            << "[7] Exit\n\n";
  return;
}

/** @name goodbye()
 * @brief The function prompts the user goodbye
 * @remark Handles UI
 * @return void-type
 */
void goodbye() {
  std::cout << "Goodbye!\n\n";
}

/** @name getInput()
 * @brief The function prompts the user to enter a number corresponding to the menu
 * @return int choice (0 < choice < 8)
 */
int getInput() {
  int const MIN = 1;
  int const MAX = 8; //lifetime is functioin call only, does not shadow limit const
  int choice = 0;
  std::cout << "\n[Enter]: ";
  
  while (true) {
    try {
      std::cin >> choice;
      if (std::cin.fail()) { //std::cin.fail() if the input is not an intiger returns true
        /// @link https://cplusplus.com/forum/beginner/2957/
        
        std::cin.clear(); // clear error flags
        std::cin.ignore(10000, '\n'); // ignore up to 10000 characters or until a newline is encountered
        throw std::invalid_argument("[Invalid input]");
      }
      else if (choice < MIN || choice > MAX) {
        throw std::out_of_range("Input out of range. Please enter an integer between 1 and 7.");
      }
      else {
        return choice;
      }
    }
    catch (const std::exception& error) {
      std::cout << error.what() << std::endl;
      std::cout << "[Re-enter]: ";
    }
  }
}

/** @name mysterySequence()
 * @brief Calculates the n-th term of the mystery sequence.
 * The sequence is defined recursively as follows:
 * 
 * @note Computed using a simple math formula
 * a[0] = 2
 * a[n] = a[n-1] * a[n-2] for n >= 1
 * @note Computed using a simple math formula
 * 
 * @param n The term number to calculate.
 * @return The value of the n-th term of the sequence.
 */
int mysterySequence(int n) {
  if (n == 0) { /// @brief base case: the first term of the sequence is 2
    return 2; //a[1]
  } else if (n == 1) {
    return 3;
  } else {
    return mysterySequence(n-1) * mysterySequence(n-2); /// @brief recursive call to get the next term
  }
}

/** @name mysterySequenceFunc()
 * @brief Prompts the user for an input n and calls the mysterySequence function 
 * with n as the argument. 
 * @throw overflow_error
 * @return void-type
 */
void mysterySequenceFunc() {
  int n = 0;
  std::cout << "\n[Enter an index]: ";
  std::cin >> n;
  
  try {
    if (n < 0) {
      throw std::out_of_range("\nIndex should be positive\n");
    } else if (n > 46340) {
      throw std::overflow_error("\nInteger Overflow is bound to happen\n");
    } else {
      int index = mysterySequence(n);
      std::cout << "\nThe [" << n << "th] link in the sequence is " << index << "\n\n";
    }
  } catch (const std::exception& error) {
    std::cout << error.what() << std::endl;
  }
}

/** @name tennisBalls()
 * @brief Calculates the total number of tennis balls in a pyramid of tennis ball cans.
 * @param n The number of levels
 * @return The total number of tennis balls in the pyramid.
 */
int tennisBalls(int n) {
  if(n == 0) { /// @brief base case
    return 0;
  } else { /// @brief recursive case
    int balls = n*n;
    return balls + tennisBalls(n-1);
  }
}

/** @name tennisBallsFunc()
 * @brief Prompts the user to enter the number of cans in the base of a pyramid and 
 *        calculates the total
 *        number of tennis balls in the pyramid.
 * @throw std::overflow_error If n is greater than 46340, which can cause an integer overflow.
 * @return void-type
 */
void tennisBallsFunc() {
  int n = 0;
  std::cout << "\n[Enter the height of the pyramid]: ";
  std::cin >> n;
  
  try {
    if (n > 46340) {
      throw std::overflow_error("\nIntiger Overflow is bound to happen\n");
    } else if(n < 0) {
      throw std::out_of_range("\nHeight should be positive\n");
    }else {
      int result = tennisBalls(n);
      std::cout << "\nA pyramid with " << n << " levels holds " << result << " balls\n\n";
    }
  } catch (const std::exception& error) {
    std::cout << error.what() << std::endl;
  }
}

/** @name decToBase2()
 * @brief Converts an integer to its binary representation as a string. 
 * @param n The integer to convert to binary.
 * @return The binary representation of n as a string.
 */
std::string decToBase2(int n) {
  if (n == 0) { /// @brief base case
    return "0";
  } else if (n == 1) {
    return "1";
  } else { /// @brief recursive case
    int remainder = n % 2;
    return decToBase2(n / 2) + std::to_string(remainder);
    //std::to_string() returns a string with the representation of a value
    /// @link https://cplusplus.com/reference/string/to_string/
  }
}

/** @name decToBase2Func()
 * @brief Converts an integer to its binary representation.
 * @details Uses the decToBase2() function to convert the integer to binary, and prints the result.
 * @throws std::overflow_error If the integer is outside the range of a signed 32-bit integer.
 * @return void-type
 */
void decToBase2Func() {
  int n = 0;
  std::cout << "\n[Enter an integer]: ";
  std::cin >> n;
  
  try {
    if(n > MAX) { //int is defined as a 32 bit int (pre installed compiler on cs1)
      throw std::overflow_error("\nIntiger Overflow\n");
    } else if( n < 0) {
      throw std::out_of_range("\nThe intiger should be positive\n");   
    }else {
      std::cout << "\nThe integer " << n << " as binary: [" << decToBase2(n) << "]\n\n";
    }
  } catch(const std::exception &error) {
    std::cout << error.what() << std::endl;
  }
}

/** @name isDivisibleBy7()
 * @brief Check if an integer is divisible by 7
 * @param n The integer to check
 * @return true if n is divisible by 7, false otherwise
 */
bool isDivisibleBy7(int n) {
  if (n < 0) {
    n = abs(-n); // make n positive because begative numbers can be divisible by 7 too
  }
  
  if (n == 0 || n == 7) { //base case
    return true; // base case
    
  } else if (n < 10) {
    return false; // base case
    
  } else { //recursive case
    int lastDigit = n % 10;
    int remaining = n / 10;
    int doubled = lastDigit * 2;
    int newNumber = remaining - doubled;
    return isDivisibleBy7(newNumber); // recursive case
  }
}

/** @name isDivisibleBy7Func()
 * @brief This function takes an integer input from the user and checks if it is divisible by 7
 * calling the isDivisibleBy7() function.
 * @throw overflow_error error.
 * @return void-type
 */
void isDivisibleBy7Func() {
  int n = 0;
  std::cout << "\n[Enter an integer]: ";
  std::cin >> n;
  
  try{
    if(n > MAX) {
      throw std::overflow_error("\nInteger Overflow\n");
    } else if( n < 0) {
      throw std::out_of_range("\nThe intiger should be positive\n");   
    } else{
      bool isDivisible = isDivisibleBy7(n);
      if(isDivisible) {
        std::cout << "\nThe integer " << n << " is divisible by 7\n\n";
      }else {
        std::cout << "\nThe integer " << n << " is not divisible by 7\n\n";
      }
    }
  } catch(const std::exception &error) {
    std::cout << error.what() << std::endl;
  }
}

/** @name ramanujan()
 * @brief Calculates the value of the Ramanujan series to a specified depth using recursion.
 * @param depth The depth of the Ramanujan series.
 * @param current The current depth of the recursion. Defaults to 0.
 * @return The value of the Ramanujan series at the specified depth.
 */
double ramanujan(int depth, int current){ //current passed as default argument
  if(current > depth) {// base case
    return 0;
  }else { //recursive case
    return (current + 1) * sqrt(6 + current + ramanujan(depth, current + 1));
  }
}

/** @name ramanujanFunc()
 * @brief Computes the value of the Ramanujan series with the given depth using recursion.
 * @param depth The depth of the Ramanujan series to compute.
 * @return The value of the Ramanujan series with the given depth.
 * @throw std::overflow_error If the depth is too large to compute.
 * @throw std::out_of_range If the depth is negative.
 */
void ramanujanFunc() {
  int n = 0;
  std::cout << "\n[Enter the depth of the series]: ";
  std::cin >> n;
  
  try {
    if(n > MAX) {
      throw std::overflow_error("\nInteger Overflow\n");
    } else if(n < 0) {
      throw std::logic_error("\nThe depth should be positive\n"); //if n < 0 we need complex nums
    }else {
      std::cout << "\nResult at depth [" << n << "] is " << ramanujan(n, 0) << "\n"; //current depth = 0 for the first itteration
      std::cout << "\nResult at infinte depth is " << ramanujan(100, 0) << "\n"; //int overflow
      std::cout << "\n";
    }
  }catch (const std::exception &error) {
    std::cout << error.what() << std::endl;
  }
}

/** @name runTest1()
 * @brief Runs the test for mysterySequence() using comparison with expected output and the actual output
 * @return booleans wheter the output mathes (false || true)
 */
bool runTest1(int expectedOutput1[]) {
  
  int input[] = {0, 1, 2, 3, 4, 5, 6, 7};
  int numTests = Tests::TEST1NUM;
  
  for (auto i = 0; i < numTests; i++) {
    if (mysterySequence(input[i]) != expectedOutput1[i]) {
      return false;
    }
  }
  return true;
}

/** @name runTest1helper()
 * @brief This function is a helper function for testing the mysterySequence function for test case 1.
 * The function tests the function for an array of input values and compares the output with the expected output.
 * @return Void-type
 */
void runTest1Helper(int expectedOutput1[]) {
  
  int input[] = {0, 1, 2, 3, 4, 5, 6, 7};
  int numTests = Tests::TEST1NUM;
  
  for (auto i = 0; i < numTests; i++) {
    if (mysterySequence(input[i]) != expectedOutput1[i]) {
      std::cout << "*** For " << input[i] << " expected " << expectedOutput1[i] << " but got " << mysterySequence(input[i]) << std::endl << std::endl;
    }
  }
}

/** @name runTest2()
 * @brief Runs the test for tennisBalls() using comparison with expected output and the actual output
 * @return booleans wheter the output mathes (false || true)
 */
bool runTest2(int expectedOutput2[]){
  int input[] = {0, 1, 3, 10, 12, 25};
  int numTests = Tests::TEST2NUM;
  
  for(auto i = 0; i < numTests; i++) {
    if(tennisBalls(input[i]) != expectedOutput2[i]) {
      return false; //test failed
    }
  }
  return true;
}

/** @name runTest2helper()
 * @brief This function is a helper function for testing the tennisBalls() function for test case 2.
 * The function tests the function for an array of input values and compares the output with the expected output.
 * @return Void-type
 */
void runTest2Helper(int expectedOutput2[]) {
  int input[] = {0, 1, 3, 10, 12, 25};
  int numTests = Tests::TEST2NUM; //cant use size of cuz array is passed as a pointer
  
  for(auto i = 0; i < numTests; i++) {
    if(tennisBalls(input[i]) != expectedOutput2[i]) {
      std::cout << "*** For " << input[i] << " expected " << expectedOutput2[i] << " but got " << tennisBalls(input[i]) << std::endl << std::endl;
    }
  }
}
/** @name runTest3()
 * @brief Runs the test for decToBase2() using comparison with expected output and the actual output
 * @return booleans wheter the output mathes (false || true)
 */
bool runTest3(std::string expectedOutput3[]){
  int input[] = {0, 1, 13, 32, 321, 8324};
  int numTests = Tests::TEST3NUM;
  
  for(auto i = 0; i < numTests; i++) {
    if(decToBase2(input[i]) != expectedOutput3[i]) {
      return false; //test failed
    }
  }
  return true;
}

/** @name runTest3helper()
 * @brief This function is a helper function for testing the decToBase2() function for test case 3.
 * The function tests the function for an array of input values and compares the output with the expected output.
 * @return Void-type
 */
void runTest3Helper(std::string expectedOutput3[]) {  
  int input[] = {0, 1, 13, 32, 321, 8324};
  int numTests = Tests::TEST3NUM;
  
  for(auto i = 0; i < numTests; i++) {
    if(decToBase2(input[i]) != expectedOutput3[i]) {
      std::cout << "*** For " << input[i] << " expected " << expectedOutput3[i] << " but got " << decToBase2(input[i]) << std::endl << std::endl;
    }
  }
}

/** @name runTest4()
 * @brief Runs the test for isDivisbleBy7() using comparison with expected output and the actual output
 * @return booleans wheter the output mathes (false || true)
 */
bool runTest4(bool expectedOutput4[]){
  
  int input[] = {1, 7, 31, 1073, 1729, 5838, 151932};
  int numTests = Tests::TEST4NUM;
  
  for(auto i = 0; i < numTests; i++) {
    if(isDivisibleBy7(input[i]) != expectedOutput4[i]) {
      return false; //test failed
    }
  }
  return true;
}

/** @name runTest4helper()
 * @brief This function is a helper function for testing the isDivisibleBy7() function for test case 4.
 * The function tests the function for an array of input values and compares the output with the expected output.
 * @return Void-type
 */
void runTest4Helper(bool expectedOutput4[]) {
  int input[] = {1, 7, 31, 1073, 1729, 5838, 151932};
  int numTests = Tests::TEST4NUM;
  
  for(auto i = 0; i < numTests; i++) {
    if(isDivisibleBy7(input[i]) != expectedOutput4[i]) {
      if(isDivisibleBy7(input[i])) {
        std::cout << "*** For " << input[i] << " expected [True] but got [False]" << std::endl << std::endl;
      }else if(!isDivisibleBy7(input[i]))
        std::cout << "*** For " << input[i] << " expected [False] but got [True]" << std::endl << std::endl;
    }
  }
}

/** @name runTest5()
 * @brief Runs the test for ramanujan() using assertion 
 * (asserts the output is always less than or equal to 4)
 * @return useless boolean...assert calls abort() upon failure
 */
bool runTest5() {
  double const OUT = 4.01; //const for testing 4.01
  
  int input[] {1, 3, 7, 23, 10, 34, 55, 12, 444, 999};
  double output; //declare var for output
  
  int numTests = Tests::TEST5NUM;
  for(auto i = 0; i < numTests; i++) {
    output = ramanujan(input[i], 0);
    if(output > OUT) {
      return false;
    }
  }
  return true;
}

/** @name runTest5helper()
 * @brief This function is a helper function for testing the ramanujan function for test case 5.
 * The function tests the ramanujan function for an array of input values and compares the output with the expected output.
 * If the output is greater than 4.01, the function prints an error message indicating 
 * that the expected output should be between 3.5 and 4.01.
 * @return Void-type
 */
void runTest5Helper() {
  double const OUT = 4.01; //const for testing 4.01
  double const MIN = 3.5;
  
  int input[] {1, 3, 7, 23, 10, 34, 55, 12, 444, 999};
  double output; //declare var for output
  
  int numTests = TEST5NUM;
  for(auto i = 0; i < numTests; i++) {
    output = ramanujan(input[i], 0);
    if(output > OUT) {
      std::cout << "*** For " << input[i] << " expected " << MIN << "< output <" << OUT << std::endl << std::endl;
    }
  }
}

/**
 * @brief The function creates a map with a key coresponding to the test case and a value form 0-1
 * which represents a boolean value as staticly casted intiger (under the hood)
 * 
 * The string key is chopped up into chars since all of the keys are equal in length. 
 * The 4th char (test number) is passed into the switch statement which calls the helper functions
 * whihc compare the output with the expected output and print all of he missmatches
 * @return Void-type
 * @typedef std::string as a string cuz im lazy to use std::namespace
 */
void runTestsFunc() {
  char const LOOKUP = 'w';
  char const QUIT = 'q';
  
  typedef std::string string; //lazy and I got told using std namespace is bad practice
  /**
   * @brief arrays for testing
   */
  int expectedOutput1[] = {2, 3, 6, 18, 108, 1944, 209952, 408146688};
  int expectedOutput2[] = {0, 1, 14, 385, 650, 5525};
  string expectedOutput3[] = {"0", "1", "1101", "100000", "101000001", "10000010000100"};
  bool expectedOutput4[] = {false, true, false, false, true, true, false}; //testing purposes [1,4,5 T]
  /**
   * @brief arrays for testing
   */
  
  string test1 = "TEST1 ";
  string test2 = "TEST2 ";
  string test3 = "TEST3 ";
  string test4 = "TEST4 ";
  string test5 = "TEST5 ";
  
  /** @note unordered_map
   * [key, value] pairs
   * key is test number [TEST[n]]
   * value is a boolean value (staticly casted I belive) to an int (0,1)
  */
  std::unordered_map<std::string, bool> testValues;

  testValues.reserve(5); //reserve space
  
  std::cout << "\n[Executing]\n" << std::endl;
  usleep(PAUSE);
  
  testValues[test1] = runTest1(expectedOutput1);
  testValues[test2] = runTest2(expectedOutput2);
  testValues[test3] = runTest3(expectedOutput3);
  testValues[test4] = runTest4(expectedOutput4);
  testValues[test5] = runTest5();
  
  bool atLeastOneFailed = false;
  
  for (std::unordered_map<std::string, bool>::const_iterator it = testValues.begin(); it != testValues.end(); ++it) {
    const bool& value = it->second;
    if (value == false) {
      atLeastOneFailed = true;
    }
  }
  
  if (atLeastOneFailed) {
    std::cout << "\n *** SOME TEST-CASES FAILED *** \n" << std::endl;
    std::cout << "[Enter 'w' to search for keys with value = 0, or 'q' to quit]: ";
    char input;
    bool validInput = false;
    while (!validInput) {
      try {
        std::cin >> input;
        if (input != 'w' && input != 'q') {
          throw std::invalid_argument("Invalid input. Please type 'w' or 'q'");
        }
        validInput = true;
      } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
      }
    }
    if (input == LOOKUP) {
      usleep(PAUSE);
      std::cout << "\n*** KEYS WITH VALUE = 0 ***\n\n";
      for (std::unordered_map<std::string, bool>::const_iterator it = testValues.begin(); it != testValues.end(); ++it) {
        const std::string& key = it->first; //key
        const bool& value = it->second; //value
        if (value == false) {
          std::cout << "[->] Key: " << key << "\n\n";
          char testKey = key[4]; //split intiger [TEST[n]] -> n is the key
          
          const char T1 = '1';
          const char T2 = '2';
          const char T3 = '3';
          const char T4 = '4';
          const char T5 = '5';
          /**
           * @brief call helper functions with expected output
          */
          switch(testKey) {
          case T1: {
            runTest1Helper(expectedOutput1);
            break;
          }
          case T2: {
            runTest2Helper(expectedOutput2);
            break;
          }
          case T3: {
            runTest3Helper(expectedOutput3);
            break;
          }
          case T4: {
            runTest4Helper(expectedOutput4);
            break;
          }
          case T5: {
            runTest5Helper();
            break;
          }
          default: {
            std::cout << "Invalid Key obtained" << std::flush;
          }
          }
        }
      }
    } else if(input == QUIT) {
      return;
    }
  } else {
    for (std::unordered_map<std::string, bool>::const_iterator it = testValues.begin(); it != testValues.end(); ++it) {
      const std::string& key = it->first;
      const bool& value = it->second;
      if (value == true) {
        std::cout << key << " PASSED "<< std::endl;
      }
    }
    std::cout << "\n *** ALL TEST-CASES PASSED *** \n" << std::endl;
  }
}


/**
 * @brief This is the main function of the program which displays a menu of options to the user,
 *        and based on the user input, calls one of the functions to perform the desired task.
 * @return Returns EXIT_SUCCESS (same as return 0) upon successful completion of the program.
 */
int main () {
  while(true) {
    printMenu();
    switch(getInput()) { //getInput()
    case 1: {
      mysterySequenceFunc();
      break;
    }
    case 2: {
      tennisBallsFunc();
      break;
    }
    case 3: {
      decToBase2Func();
      break;
    }
    case 4: {
      isDivisibleBy7Func();
      break;
    }
    case 5: {
      ramanujanFunc();
      break;
    }
    case 6: {
      runTestsFunc();
      break;
    }
    case 7: {
      goodbye();
      exit(EXIT_SUCCESS);
      break;
    }
    default:  {
      //do nothing
      break;
    }
    }
  }
  return EXIT_SUCCESS;
}

