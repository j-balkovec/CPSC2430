/**
 * @author Jakob Balkovec
 * @file main.cpp [Driver Code]
 * @note Driver code for lab4
 * 
 * @brief This assigment focuses on using basic operations in a heap such as:
 *   - Insertion
 *   - Deletion
 *   - Peeking
 * 
 * Those operations were implemented using a Shelter class that includes a struct for Pets 
 */

#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <utility>
#include <sstream>
#include <unistd.h>

//#define DEBUG

#pragma message("[" __FILE__"] " "Last compiled on [" __DATE__ "] at [" __TIME__"]")

/**
 * @note percolate down is behaving wierdly
 * deleteMin() might not be correct
*/

/**
 * @struct Pet
 *    - Defines the Pet object
 *    - Includes a constructor
 */
struct Pet {
    std::string name;
    int arrival;
    Pet(std::string name = "", int arrival = 0) : name(name), arrival(arrival) {} //Constructor
};

int const PAUSE = 1000000; //usleep const
//1000000

/**
 * @class PetHeap
 *    - Defines the heap with appropriate methods
 */
class PetHeap {
  private:
    std::vector<Pet*> petHeap;
    void percolateUp(int index);
    void percolateDown(int index);
    void deleteMin();
    Pet* peekMin();

  public:
    PetHeap();
    bool destroyHeap();
    void insert(Pet* pet);
    void adoptOldestPet();
    int numPets();
    void displayPets();

    bool testDestroyHeap();
    bool testInsert(); 
    bool testAdoptOldestPet();
    bool testNumPets(); 
    bool testDisplayPets(); 
    bool testPercolateUp();
    bool testPercolateDown();
    bool testDeleteMin(); 
    bool testPeekMin();

    void runTests();
};

/** CONSTRUCTOR:
 * @name PetHeap::PetHeap()
 * @brief Initializes an empty vector for the Pet pointers
 */
PetHeap::PetHeap() {
  petHeap = std::vector<Pet*> ();
}

/** DESTRUCTOR:
 * @name PetHeap::~PetHeap()
 * @brief Handles memory
 */
bool PetHeap::destroyHeap() {
  if(petHeap.size() == 0) {
    return true;
  }
  for (int i = 0; i < (int)petHeap.size(); i++) {
        delete petHeap[i];
  }
  petHeap.clear();
  if(petHeap.empty()) {
    return true;
  }
  return false;
}

/**
 * @name void PetHeap::percolateUp()
 * @brief Percolates up the element at the given index until the heap property is satisfied.
 * @param index The index of the element to be percolated up.
*/
void PetHeap::percolateUp(int index) {
  /**
   * Parent formula: (i-1)/2
   * 
   * Find parent and compare it to the vector
  */
  if (index == 0) {
    return;
  }

  int parentIndex = (index - 1) / 2;

  if (petHeap[index] -> arrival < petHeap[parentIndex] -> arrival) {
    std::swap(petHeap[index], petHeap[parentIndex]);
    percolateUp(parentIndex);
  }
}

/**
 * @name void PetHeap::insert()
 * @brief Inserts a new pet into the heap and maintains the heap property
 * @param pet The pet to be inserted
 */
void PetHeap::insert(Pet* pet) {
  /**
   * Insert into the array
   * Call percolateUp to maintain the heap
  */
 petHeap.push_back(pet);
 int index = petHeap.size() - 1; //track the index of the pet
 percolateUp((int)index);
}


/**
 * @name void PetHeap::percolateDown()
 * @brief Percolates down the pet heap from the given index to maintain the heap property
 * @param index The index from where to start percolating down
 */
void PetHeap::percolateDown(int index) {
    int childIndex = 2 * index + 1;
    Pet* temp = petHeap[index];
    
    while (childIndex < (int)petHeap.size()) {
        if (childIndex + 1 < (int)petHeap.size() && petHeap[childIndex + 1] -> arrival < petHeap[childIndex] -> arrival) {
            childIndex++;
        }
        if (petHeap[childIndex] -> arrival < temp -> arrival) {
            petHeap[index] = petHeap[childIndex];
            index = childIndex;
            childIndex = 2 * index + 1;
        } else {
            break;
        }
    }
    
    petHeap[index] = temp;
}

/**
 * @name Pet* PetHeap::peekMin()
 * @brief Returns the minimum value of the heap without modifying the heap.
 * @return The minimum Pet object in the heap.
*/
Pet* PetHeap::peekMin() {
  if(petHeap.empty() || petHeap.size() == 0) {
    return nullptr;
  }
  Pet* firstElement = petHeap[0]; //first element
  return firstElement;
}

/**
 * @name void PetHeap::deleteMin()
 * @brief Deletes the minimum element from the heap.
 * If the heap is empty, does nothing. Otherwise, deletes the root element (minimum element)
 * from the heap and reorders the heap using percolateDown() to maintain the heap property.
 */
void PetHeap::deleteMin() {
  if (petHeap.empty()) {
    return;
  }
  // swap the last element with the first one
  std::swap(petHeap[0], petHeap.back());

  // delete the last element
  delete petHeap.back();
  petHeap.pop_back();
  // percolate down to maintain the heap property
  percolateDown(0);
}

/**
 * @name void PetHeap::adoptOldestPet()
 * @brief Adopt the oldest pet in the shelter.
 * @return void
*/
void PetHeap::adoptOldestPet() {
  if(petHeap.empty()) {
    std::cout << "\n[Error: No Pets in the shelter]\n";
    return;
  }

  Pet* oldestPet = peekMin();

  #ifdef DEBUG
  std::cout << "\n[Pet adopted]:\n\n";
  std::cout << "[name]: " << oldestPet -> name << std::endl; 
  std::cout << "[arrival]: " << oldestPet -> arrival << std::endl;
  std::cout << std::flush;
  #endif //DEBUG

  deleteMin();
  return;
}

/**
 * @name int PetHeap::numPets()
 * @brief Returns the number of pets in the PetHeap.
 * @return The number of pets in the PetHeap as an integer.
*/
int PetHeap::numPets() {
  #ifdef DEBUG
  std::cout << "\n[Number of Pets]: " << petHeap.size() << "\n\n";
  #endif //DEBUG

  return petHeap.size();
}

/**
 * @name void PetHeap::displayPets() 
 * @brief Display all pets in the shelter
 */
void PetHeap::displayPets() {
  #ifdef DEBUG
  std::cout << "\n[Displaying Heap]:\n\n";
  #endif // DEBUG

  if(petHeap.size() == 0) {
    std::cout << "[Heap is empty]\n";
  }
  for(Pet* iter : petHeap) {
    #ifdef DEBUG
    std::cout << "[name]: " << iter -> name << std::flush; //flush buffer
    std::cout << "\t[arrival]: "<< iter -> arrival << std::endl;    
    #endif // DEBUG

  }
  return;
}

/** @nam-> name()
 * @brief Prompts the user to enter a name
 * @param name passed by reference
 * @return std::string name
 */
std::string getName(std::string &name) {
  std::cout << "[Enter Name]: ";
  while (true) {
    try {
      std::cin >> name;
      if (std::cin.fail()) {
        throw std::runtime_error("[Invalid input. Please enter a valid name]");
      }
      return name;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }
}

/** @name getArrival()
 * @brief Prompts the user to enter the arrival time
 * @param arrival passed by reference
 * @return (int) arrival
 */
int getArrival(int &arrival) {
  std::cout << "\n[Enter Arrival]: ";
  while (true) {
    try {
      std::cin >> arrival;
      if (std::cin.fail() || arrival < 0) {
        throw std::runtime_error("[Invalid input. Please enter a positive integer]");
      }
      return arrival;
    } catch (const std::runtime_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "\n[Enter Arrival]: ";
    }
  }
}

/**
 * @name int getInput()
 * @brief gets the input for the switch statement
 * @return (int) input
 */
int getInput() {
  int const MIN = 1;
  int const MAX = 7;
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
        throw std::out_of_range("[Input out of range. Please enter an integer between 1 and 16]");
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

/** @name goodbye()
 * @brief The function prompts the user goodbye
 * @remark Handles UI
 * @return void-type
 */
void goodbye() {
  std::cout << "\nGoodbye!\n\n";
}

/**
 * @brief Destroys the heap and prints a message to the console
 * @param heap A reference to the `PetHeap` object to be destroyed.
 */
void isDestroyed(PetHeap &heap) {
  bool dead = false;
  bool retry = false;
  dead = heap.destroyHeap();
  if(dead) {
    #ifdef DEBUG
    std::cout << "\n[Heap Destroyed]\n";
    #endif // DEBUG
  } else {
    #ifdef DEBUG
    std::cout << "\n[Something went wrong]\n";
    #endif // DEBUG
    retry = heap.destroyHeap(); //try again
      if(retry == false) {
        std::cout << "\n[Program is leaking memory!]\n";
        std::cout << "\n[Force Exiting with code 1]\n";
        std::exit(EXIT_FAILURE);
      }

  }
}

/**
 * @name void menu()
 * @brief Prints the menu for the user
 */
void menu() {
  std::cout << "\n\n"
            << "[1]   Insert a Pet\n"
            << "[2]   Adopt a Pet\n"
            << "[3]   Number of Pets in the Heap\n"
            << "[4]   Display Heap\n"
            << "[5]   Run Tests\n"
            << "[6]   Exit\n";
  return;
}

/** @name printTitle()
 * @brief The function prints the title
 * @remark Handles UI
 * @return void-type
 */
void printTitle() {
  std::cout << "\n\n*** Welcome to the Heap assigment *** \n\n";
  std::cout << "Please select one of the following?\n";
}

/**
 * @name PetHeap::testDestroyHeap()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testDestroyHeap() {
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.destroyHeap();
    bool result = false;

    auto numPets = heap.numPets();
    if(numPets == 0) {
      result = true;
    } else {
      std::cout << "\n[Expected [Empty Heap] but still have " <<  numPets << " Pets in the Heap]\n";
    }
    std::cout << "\n*** TEST1 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    return result;
}

/**
 * @name PetHeap::testInsert()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testInsert() {
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    bool result = false;
    auto numPets = heap.numPets();
    if(numPets == 2) {
      result = true;
    } else {
    std::cout << "\n[Expected 2 but got [" <<  numPets << "]]\n";
    }
    std::cout << "\n*** TEST2 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);
    return result;
}

/**
 * @name PetHeap::testAdoptOldestPet()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testAdoptOldestPet() {
  PetHeap heap;
  heap.insert(new Pet("Fluffy", 3));
  heap.insert(new Pet("Spot", 5));
  heap.insert(new Pet("Max", 1));

  heap.adoptOldestPet();
  Pet* oldestPet = heap.peekMin();

  bool result1 = true;
  bool result2 = true;
  auto numPets = heap.numPets();
  if(heap.numPets() != 2) {
    std::cout << "[Expected 2 but got [" << numPets<< "]]\n";
    result1 = false;
  }

  if(oldestPet == nullptr || oldestPet -> name != "Fluffy") {
    std::cout << "[Expected \"Fluffy\" but got [\"";
    if (oldestPet != nullptr) {
      std::cout << oldestPet -> name << "\"]\n";
    } else {
      std::cout << "nullptr\"]\n";
    }
    result2 = false;
  }

  std::cout << "\n*** TEST3 FINISHED ***\n" << std::flush;
  usleep(PAUSE);
  isDestroyed(heap);
  return result1 && result2;
}

/**
 * @name PetHeap::testNumPets()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testNumPets() {
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    bool result = false;
    auto numPets = heap.numPets();

    if(numPets == 2) {
      result = true;
    } else {
      std::cout << "\n[Expected 2 but got [" <<  numPets << "]]\n";
    }
    std::cout << "\n*** TEST4 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);
    return result;
}

/**
 * @name PetHeap::testDisplayPets()
 * @brief Try using string stream
 * @return 
 */
bool PetHeap::testDisplayPets() {
    // Test manually by visually inspecting output
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.displayPets();
    std::cout << "\n*** TEST5 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);
    return true;
}

/**
 * @name PetHeap::testPercolateUp()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testPercolateUp() { //insert calls percolate
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.insert(new Pet("Max", 1));

    bool result = true;

    Pet *pet = heap.peekMin();
    if(pet -> name != "Max") {
      std::cout << "[Expected \"Max\" but got [\"" << pet -> name << "\"]\n";
      result = false;
    }
    std::cout << "\n*** TEST6 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);
    return result;
}

/**
 * @name PetHeap::testPercolateDown() 
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testPercolateDown() { //delete calls percolate down
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.insert(new Pet("Max", 1));
    heap.insert(new Pet("Buddy", 2));

    bool result1 = true;
    bool result2 = true;

    Pet* pet1 = heap.peekMin();
    heap.deleteMin();  
    Pet* pet2 = heap.peekMin();

    if(pet1 == pet2) {
      std::cout << "\n[Expected the Pet to be deleted]\n";
      result1 = false;
    }
    if(pet2 -> name != "Buddy") {
      std::cout << "\n[Expected \"Buddy\" but got " << pet2 -> name << "]\n";
      result2 = false;
    }
    std::cout << "\n*** TEST7 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);    
    return result1 && result2;
}

/**
 * @name PetHeap::testDeleteMin()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testDeleteMin() {
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.insert(new Pet("Max", 1));
    heap.deleteMin();

    bool result = true;
    auto numPets = heap.numPets();
    if(heap.numPets() != 2) {
      std::cout << "\n[Expecetd 2 Pets in the heap but got " << numPets << "]\n";
      result = false;
    }
    Pet* topPet = heap.peekMin();
    if(topPet -> name != "Fluffy") {
      std::cout << "\n[Expected \"Fluffy\" but got " << topPet -> name <<"]\n";
      result = false;
    }
    std::cout << "\n*** TEST8 FINISHED ***\n" << std::flush;
    usleep(PAUSE);
    isDestroyed(heap);    
    return result;
}

/**
 * @name PetHeap::testPeekMin()
 * @brief Runs the test for a certain function
 * @return boolean value wheter the test passed or failed
*/
bool PetHeap::testPeekMin() {
    PetHeap heap;
    heap.insert(new Pet("Fluffy", 3));
    heap.insert(new Pet("Spot", 5));
    heap.insert(new Pet("Max", 1));

    bool result = true;
    Pet* topPet = heap.peekMin();
    if(topPet -> name != "Max") {
      std::cout << "\n[Expected \"Max\" but got " << topPet -> name <<"]\n";
      result = false;
    }
    std::cout << "\n*** TEST9 FINISHED ***\n" << std::flush;
    usleep(PAUSE); 
    isDestroyed(heap);
    return result;
}
/**
 * @name void runTests()
 * @brief Runs tests for all the functions and stores the returned boolean values in a vector
 * @remark calls necessary functions
 */
void PetHeap::runTests() {
  std::vector<bool> testValues;

  std::cout << "\n*** RUNNING ALL TESTS ***\n\n" << std::flush;
  usleep(PAUSE);

  testValues.push_back(testDestroyHeap());
  testValues.push_back(testInsert()); 
  testValues.push_back(testAdoptOldestPet());
  testValues.push_back(testNumPets()); 
  testValues.push_back(testDisplayPets()); 
  testValues.push_back(testPercolateUp());
  testValues.push_back(testPercolateDown());
  testValues.push_back(testDeleteMin()); 
  testValues.push_back(testPeekMin());

  std::cout << "\n\n*** TEST RESULTS ***\n\n";
  for(auto i = 0; i < (int)testValues.size(); i++) {
    if(testValues[i] == true) {
      std::cout << "TEST " << i+1 << " PASSED ***\n";
    }else if(testValues[i] == false) {
      std::cout << "TEST " << i+1 << " FAILED ###\n";
    }
  }
}

/**
 * @brief Main function of the program
 * @return EXIT_SUCESS upon succesful execution
 */
int main() {
  PetHeap heap;
  std::string name = "";
  int arrival = 0;

  enum OP_ID {
    ID_1 = 1,
    ID_2,
    ID_3,
    ID_4,
    ID_5,
    ID_6,
  };
  printTitle();
  while(true) {
    menu();
      switch(getInput()) {
      case OP_ID::ID_1: {
        heap.insert(new Pet(getName(name), getArrival(arrival)));
        break;
      }
        
      case OP_ID::ID_2: {
        heap.adoptOldestPet();
        break;
      }
        
      case OP_ID::ID_3: {
        heap.numPets();
        break;
      }
        
      case OP_ID::ID_4: {
        heap.displayPets();
        break;
      }
        
      case OP_ID::ID_5: {
        heap.runTests();
        break;
      }
        
      case OP_ID::ID_6: {
        isDestroyed(heap);
        goodbye();
        exit(EXIT_SUCCESS);
        break;
      }
        
      default: {
        /** @note do nothing*/
      }
      }
  }
  return EXIT_SUCCESS; 
}