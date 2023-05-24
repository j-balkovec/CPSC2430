/**
 * @author Jakob Balkovec
 * @brief This is the driver code to the shelter managment program
 * @file main.cpp - Driver Code
 */

/**
 * @note This program represents a shelter managment system with dogs and cats
 * The program as well as the users follow a FIFO system when adopting
 * an animal
 */

#include <iostream>
#include <queue>
#include <string>
#include <memory>
#include "pet.h"

int const MAX = 4;
int const MIN = 1;

/** @name printMenu
 * @brief Prints the menu of the shelter program
 */
void printMenu() {
  std::cout << "\n------- MENU --------\n"
            << "[1] Add an animal\n"
            << "[2] Get an animal\n"
            << "[3] Quit\n"
            << "---------------------\n";
}

/** @name welcome
 * @brief Prompts the user with a welcome message
 */
void welcome() {
  std::cout << "\n\n*** Welcome to our Animal Shelter ***\n" << std::endl;
}

/** @name printShelterStatus
 * @brief Prints the current status of the animal shelter.
 * @param dogs A constant reference to a queue of shared pointers to Pet objects representing the dogs in the shelter.
 * @param cats A constant reference to a queue of shared pointers to Pet objects representing the cats in the shelter.
 */
void printShelterStatus(std::queue<Pet*>& dogs, std::queue<Pet*>& cats) {
  std::cout << "\n------ STATUS -------\n";
  std::cout << "[Dogs]: " << dogs.size() << "\n";
  std::cout << "[Cats]: " << cats.size() << "\n";
  std::cout << "---------------------\n";
}

/** @name addAnimal
 * Adds an animal to the corresponding queue based on its category.
 * @param dogs The queue containing dogs.
 * @param cats The queue containing cats.
 */
void addAnimal(std::queue<Pet*>& dogs, std::queue<Pet*>& cats) {
  std::string category;
  std::string name;
  std::cout << "Enter the category of the animal (dog/cat): ";
  std::cin >> category;
  std::cout << "Enter the name of the animal: ";
  std::cin >> name;
  
  Pet* pet = new Pet(name, category);
  if (category == "dog") {
    dogs.push(pet);
  } else if (category == "cat") {
    cats.push(pet);
  } else {
    std::cout << "Invalid animal category\n";
  }
}

/** @name getAnimal
 * Get an animal from the shelter based on the preferred category.
 * @param dogs Queue of shared pointers to dogs in the shelter.
 * @param cats Queue of shared pointers to cats in the shelter.
 * @throw runtime_error: if no animals are available in 
 *        the shelter or the preferred category is not available.
 */
/** @name getAnimal
 * Get an animal from the shelter based on the preferred category.
 * @param dogs Queue of shared pointers to dogs in the shelter.
 * @param cats Queue of shared pointers to cats in the shelter.
 * @throw runtime_error: if no animals are available in 
 *        the shelter or the preferred category is not available.
 */
void getAnimal(std::queue<Pet*>& dogs, std::queue<Pet*>& cats) {
  std::string category;
  std::cout << "Enter the preferred category of the animal (dog/cat/any): ";
  std::cin >> category;
  
  Pet* pet = nullptr;
  try {
    if (category == "dog") {
      if (dogs.empty()) {
        //throw runtime i guess
        throw std::runtime_error("There is no dog in the shelter now\n");
      }
      pet = dogs.front(); //front of the dogs queue
      dogs.pop(); //pop cuz adopted
    } else if (category == "cat") {
      if (cats.empty()) {
        throw std::runtime_error("There is no cat in the shelter now\n");
      }
      pet = cats.front(); //front of the cats queue
      cats.pop(); //pop cuz adopted
    } else { //if "none"
      if (dogs.empty() && cats.empty()) { //if empty
        throw std::runtime_error("There is no animal in the shelter now\n");
      }
      if (!dogs.empty() && !cats.empty()) {
        if (dogs.front() < cats.front()) {
          pet = dogs.front(); //front of the dogs queue
          dogs.pop(); //pop dog
        } else {
          pet = cats.front(); //front of the cats if cats is less than dogs
          cats.pop(); //pop cat
        }
      } else if (!dogs.empty()) { //if not empty, then pop dog
        pet = dogs.front();
        dogs.pop();
      } else if (!cats.empty()) { //if not empty, then pop cat
        pet = cats.front();
        cats.pop();
      }
    }
  } catch (std::runtime_error& error) {
    std::cout << error.what();
    return;
  }
  
  //print adopted animal using -> to acces through a pointer
  std::cout << "You adopted a " << pet->getCategory() << " named " << pet->getName() << "!\n";
  delete pet; // deallocate pet since it was allocated with new
  std::cin.ignore();
}


/** @name get_input
 * @brief Prompt the user to pick a number from 1 to 3
 * @return 
 */
int getInput() {
  int choice;
  std::cin >> choice;
  
  while(choice > MAX && choice < MIN) {
    std::cout << "\nInvalid!\n";
    std::cin >> choice;
  }
  return choice;
}

/** @name goodbye
 * @brief Prompts the user goodbye
 */
void goodbye() {
  std::cout << "\nThank you, Goodbye!\n\n";
}

/** @name [main]
 * @brief This function initializes two queues to store dogs and cats respectively. 
 * It then enters a loop to display a menu of options
 * to the user and execute their chosen action. The options are:
 * If an invalid option is selected, an error message is
 * printed and the menu is displayed again.
 * @return The exit status of the program. Returns EXIT_SUCCESS if the 
 * program executes successfully, and EXIT_FAILURE if it encounters an error.
 */ 
int main() {
  /**
   * @brief declare variables
   */
  std::queue<Pet*> dogs;
  std::queue<Pet*> cats;
  
  welcome();
  
  while (true) { //infinite loop (could also make a boolean and set it to false in case 3)
    printMenu();
    switch (getInput()) {
    case 1:
      addAnimal(dogs, cats);
      printShelterStatus(dogs, cats);
      break;
    case 2:
      getAnimal(dogs, cats);
      printShelterStatus(dogs, cats);
      break;
    case 3:
      goodbye();
      exit(EXIT_FAILURE);
    default:
      std::cout << "Invalid choice\n"; //default case
      break;
    }
  }
  return EXIT_SUCCESS; //same as return 0, I just think it looks better
}
