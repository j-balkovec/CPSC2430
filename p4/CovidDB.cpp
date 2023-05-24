/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file CovidDB.cpp [Driver Code]
 * @note Driver code for A4
 * 
 * @brief This assigment focuses on using multiple operations regarding HasHTables such as:
 *   - Insertion
 *   - Printing
 *   - Hashing
 *   - Deletion
 *   - [File reading]
 * 
 * Those operations were implemented using a DataEntry and a CovidDB class
 */

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <thread>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "CovidDB.h"

#define LOG

/**
 * @brief Constructs an object of DataEntry type with default parameters
 * @return DataEntry Object
 */
DataEntry::DataEntry() {
  this->date = "\0";
  this->country = "\0";
  this->c_cases = 0;
  this->c_deaths = 0;
}

/**
 * @brief Hashfunction that creates a hash
 * @param country std::string entry -> country in the CSV file
 * @return Hash
 */
int CovidDB::hash(std::string country) {
  int sum = 0;
  int count = 0;
  
  for (char c : country) {
    sum = sum + ((count + 1) * c);
    count++;
  }
  return sum % size; //returns the hash
}

/**
 * @brief Inserts one data entry into the hash table. 
 * @param entry The DataEntry object to be added
 * @return true if record is added, false if record is rejected (date < than current date)
 */
bool CovidDB::add(DataEntry* entry) {
  time_t now = time(0);
  tm* ltm = localtime(&now);
  // DATE FORMAT: mm/dd/yy
  std::string current_date_str = std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday) + "/" + std::to_string(ltm->tm_year % 100);
  std::istringstream iss(current_date_str);
  std::tm current_date = {};
  iss >> std::get_time(&current_date, "%m/%d/%y");
  
  std::tm entry_date = {};
  std::istringstream iss2(entry -> get_date());
  iss2 >> std::get_time(&entry_date, "%m/%d/%y");
  
  if (mktime(&current_date) > mktime(&entry_date)) {
    std::cout << "[Record rejected]" << std::endl;   
    return false;
  }
  
  int index = hash(entry -> get_country());
  assert(index < 17 and index >= 0);
  
  if (HashTable[index].empty()) {
    HashTable[index].push_back((entry));
  } else {
    bool added = false;
    for (DataEntry* existing_entry : HashTable[index]) {
      if (hash(existing_entry->get_country()) == hash(entry->get_country()) &&
          existing_entry->get_country() == entry->get_country()) {
        existing_entry->set_c_cases(existing_entry->get_c_cases() + entry->get_c_cases());
        existing_entry->set_c_deaths(existing_entry->get_c_deaths() + entry->get_c_deaths());
        added = true;
        delete entry;
        break;
      }
    }
    if (!added) {
      HashTable[index].push_back(entry);
    }
  }
  return true;
}

/**
 * @brief Retrieves a data entry with the specific country name
 * @param country The country to search for
 * @return The DataEntry object with the matching country name, or NULL if no such entry exists
 */
DataEntry* CovidDB::get(std::string country) {
  int index = hash(country);
  assert(index < 17);
  
  for (DataEntry* entry : HashTable[index]) {
    if (entry->get_country() == country) {
      return entry;
    }
  }
  return nullptr;
}

/**
 * @brief Fetches the data entry for a specific country and assigns it
 *        to the provided DataEntry pointer.
 * 
 * @param set A pointer to a DataEntry object where the fetched data will be assigned.
 * @param country The name of the country to fetch data for.
 * @return void
 */
void CovidDB::fetch_data(DataEntry* set, std::string country) {
  set = get(country);
  if(set == nullptr) {
    std::cout << "\n[No entry found for: \"" << country << "\"]\n";
    return; //if nullptr don't derefernece
  }
  char const SPACE = ' ';
  std::cout << std::flush;
  std::cout << "\n[Date: " << set -> get_date() << "]," << SPACE
            << "[Country: " << set -> get_country() << "]," << SPACE
            << "[Cases: " << set -> get_c_cases() << "]," <<SPACE
            << "[Deaths: " << set -> get_c_deaths() << "]" << SPACE
            << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

/**
 * @brief Removes the data entry with the specific country name
 * @param country The country to remove
 */
void CovidDB::remove(std::string country) {
  int index = hash(country);
  
  for (auto it = HashTable[index].begin(); it != HashTable[index].end(); ++it) {
    if ((*it)->get_country() == country) {
      delete *it;
      HashTable[index].erase(it);
      return;
    }
  }
  std::cout << "\n[No entry found for: " << country << "]" << std::endl;
}

/**
 * @brief Prints the contents of the hash table using
 *        nested for each loops
 */
void CovidDB::display_table() {
  char const STICK = '|';
  bool is_empty = true;

  /** @note guard against printing an empty table*/
  for(const auto& vec : HashTable) {
    if(!vec.empty()) {
      is_empty = false;
      break;
    }
  }

  if(is_empty) {
    std::cout << "\n[Data Base is empty]\n";
    return;
  }

  /** @note guard against printing an empty table*/
  
  std::cout << "\n[Printing Data Base]\n|\n";
  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << STICK << std::endl;
  }
  std::cout << std::flush; //flush buffer
  std::string const SPACE = " ";
  
  for(auto& vec : HashTable) {
    for(auto& entry : vec) {
      if (entry not_eq nullptr) { //guard against dereferencing nullptr
        std::cout << std::flush;
        std::cout << "[Date: " << entry -> get_date() << "]," << SPACE
                  << "[Country: " << entry -> get_country() << "]," << SPACE
                  << "[Cases: " << entry -> get_c_cases() << "]," << SPACE
                  << "[Deaths: " << entry -> get_c_deaths() << "]"
                  << std::endl;
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  }
  std::cout << std::endl;
  return;
}

/**
 * @brief Logs the contents of the hash table using
 *        nested for each loops and writes them to a .log file
 */
void CovidDB::log() {
  #ifdef LOG
  add_covid_data(COVID_FILE); //add data and log
  std::ofstream covid_file;
  covid_file.open("covid_db.log");

  if (covid_file.is_open()) {
    covid_file << std::flush;

    std::string const SPACE = " ";
    covid_file << "\n\n****************************** COIVD DATA LOG ******************************\n\n\n";
    for (auto& vec : HashTable) {
      for (auto& entry : vec) {
        if (entry != nullptr) {
          covid_file << "[Date: " << entry->get_date() << "]," << SPACE
                     << "[Country: " << entry->get_country() << "]," << SPACE
                     << "[Cases: " << entry->get_c_cases() << "]," << SPACE
                     << "[Deaths: " << entry->get_c_deaths() << "]"
                     << std::endl;
        }
      }
    }
  covid_file.close();
  } else {
    covid_file << "\n[Error opening the file covidDB.log]\n";
    std::exit(EXIT_FAILURE);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "\n------ [Log avalible] ------\n\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::exit(EXIT_SUCCESS);
  return;
}
#else
std::cout << "\n[Define [LOG macro in CovidDB.cpp] to run]\n";
#endif // LOG

/**
 * @brief Reads a CSV file containing COVID data and adds the data to the database.
 * @param COVID_FILE The name of the CSV file to read.
 * @return void
 */
void CovidDB::add_covid_data(std::string const COVID_FILE) {
  std::ifstream file(COVID_FILE);

  /** @note measure timne it takes to fetch and process data*/
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point endTime;

  startTime = std::chrono::steady_clock::now(); //start stopwatch
  
  if (!file) {
    std::cout << "\n[File ERROR]\n " << COVID_FILE << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << std::flush;
  std::cout << "\n[Fetching Data]\n";
  std::cout << std::flush;
  std::string line;
  std::getline(file, line); // skip header line
  
  std::string latest_date_str = "10/31/22"; // initialize to an old date
  std::tm latest_date = {};
  std::istringstream iss(latest_date_str);
  iss >> std::get_time(&latest_date, "%m/%d/%y");
  
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string country, date_str, cases_str, deaths_str;
    std::getline(ss, date_str, ',');
    std::getline(ss, country, ',');
    std::getline(ss, cases_str, ',');
    std::getline(ss, deaths_str, ',');
    
    int cases = std::stoi(cases_str);
    int deaths = std::stoi(deaths_str);
    
    std::tm entry_date = {};
    std::istringstream iss2(date_str);
    iss2 >> std::get_time(&entry_date, "%m/%d/%y");
    
    if (mktime(&entry_date) > mktime(&latest_date)) {
      latest_date_str = date_str;
      latest_date = entry_date;
    } 
    
    DataEntry* entry = new DataEntry(); //#1 allocation
    entry->set_country(country);
    entry->set_date(latest_date_str);
    entry->set_c_cases(cases);
    entry->set_c_deaths(deaths);
    
    add(entry);
  }
  file.close();

  endTime = std::chrono::steady_clock::now(); //stop stopwatch

  std::chrono::duration<double> elapsedSeconds = endTime - startTime;

  /** @note static cast it to an int and round up*/
  auto elapsedSecondsCount = static_cast<int>(std::round(elapsedSeconds.count()));

  std::cout << std::flush; //flush isotream buffer
  std::cout << "|\n|\n|\n[Data Fetched] [Elapsed Time: " << elapsedSecondsCount << "s]\n" << std::flush;
  return;
} 

/**
 * @brief logs memory by running valgrind
 */
void CovidDB::log_memory() {
  #ifdef LOG
  std::cout << "\n[NOTE]: Please quit the program right after it re-runs with \"Valgrind\"\n";
  std::this_thread::sleep_for(std::chrono::seconds(4));
  std::string command = "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --num-callers=20 -s --log-file=valgrind.log ./main";
  std::system(command.c_str());
}
#else
std::cout << "\n[Define [LOG macro in CovidDB.cpp] to run]\n";
#endif

/**
 * @brief Runs a test for a specific function
 * @return boolean wheter the test has passed or failed
 */
bool CovidDB::test_hash() { //1
  int const HASH = 12;
  std::string const KEY = "Japan";

  //parse the key into the hash function
  //expect 13 as shown in the pptx

  auto output = hash(KEY);

  if(output not_eq HASH) {
    std::cout << "\n[Expected " << "\"13\" but got " << output << "]" << std::flush;
    return false;
  }
  return true;
}

/**
 * @brief Runs a test for a specific function
 * @return boolean wheter the test has passed or failed 
 */
bool CovidDB::test_add() { //2
  DataEntry *new_entry = new DataEntry;

  //invoke add() and pass in new_entry
  add(new_entry);

  //check if vector is empty
  for(auto &bucket : HashTable) {
    for([[maybe_unused]]auto &new_bucket : bucket) { //explicitly say unused or the compiler is compalining
      if(HashTable.empty()) {
        std::cout << "\n[Expected \"true\" but got \"false\"]" << std::flush;
        delete new_entry;
        return false;
      }
    }
  }
  delete new_entry;
  return true;
}

/**
 * @brief Runs a test for a specific function
 * @return boolean wheter the test has passed or failed
 */
bool CovidDB::check_collison() { //3
  //get 2 countries that have the same hash key
  /** @note key 0
   * Albania
   * Algeria
   * Czechia
   * Egypt
   * French Polynesia
   * Gambia
   * Marshall Islands
   * Micronesia 
   * Myanmar
   * Norway
   * Germany
   * Qatar
   * Republic of Korea
   * San Marino
  */

  std::string const DATE = "2/3/23";
  DataEntry *col1 = new DataEntry;
  DataEntry *col2 = new DataEntry;

  col1 -> set_country("Germany");
  col2 -> set_country("Norway");

  col1 -> set_date(DATE);
  col2 -> set_date(DATE);

  col1 -> set_c_cases(0);
  col2 -> set_c_cases(0);

  col2 -> set_c_deaths(0);
  col2 -> set_c_deaths(0);

  int hash1 = hash(col1 -> get_country());
  int hash2 = hash(col2 -> get_country());

  assert(hash1 == hash2); //fails if they're not the same (they should be)

  add(col1);
  add(col2);

  bool found_col1 = false;
  bool found_col2 = false;

  // iterate through the vector at the hash position of col1
  for (auto& entry : HashTable[hash1]) {
    if (entry == col1) {
      found_col1 = true;
    } else if (entry == col2) {
      found_col2 = true;
    }
  }

  // iterate through the vector at the hash position of col2
  for (auto& entry : HashTable[hash2]) {
    if (entry == col1) {
      found_col1 = true;
    } else if (entry == col2) {
      found_col2 = true;
    }
  }

  return found_col1 && found_col2;
}

/**
 * @brief Runs a test for a specific function
 * @return boolean wheter the test has passed or failed 
 */
bool CovidDB::test_get() { //4
  std::string const COUNTRY = "Slovenia";
  std::string const DATE = "2/3/23";

  int const DEATHS = 100;
  int const CASES = 1500;

  DataEntry *e = new DataEntry;
  
  e -> set_c_cases(CASES);
  e -> set_c_deaths(DEATHS);
  e -> set_country(COUNTRY);
  e -> set_date(DATE);

  add(e);

  int cases = e -> get_c_cases();
  int deaths = e -> get_c_deaths();

  std::string country = e -> get_country();
  std::string date = e -> get_date();

  if(cases not_eq CASES) {
    std::cout << "\n[Expected \"" << CASES << "\" but got \"" << cases << "\"]";
    return false;
  }

  if(deaths not_eq DEATHS) {
    std::cout << "\n[Expected \"" << DEATHS << "\" but got \"" << deaths << "\"]";
    return false;
  }

  if(country not_eq COUNTRY) {
    std::cout << "\n[Expected \"" << COUNTRY << "\" but got \"" << country << "\"]";
    return false;
  }

  if(date not_eq DATE) {
    std::cout << "\n[Expected \"" << DATE << "\" but got \"" << date << "\"]";
    return false;
  }

  delete e;
  return true;
}

/**
 * @brief Runs a test for a specific function
 * @return boolean wheter the test has passed or failed
 */
bool CovidDB::test_remove() { //5
  std::string const COUNTRY = "Slovenia";
  std::string const DATE = "2/3/23";

  int const DEATHS = 100;
  int const CASES = 1500;

  DataEntry *e = new DataEntry;
  
  e -> set_c_cases(CASES);
  e -> set_c_deaths(DEATHS);
  e -> set_country(COUNTRY);
  e -> set_date(DATE);

  //get hash
  int hash_key = hash(COUNTRY);

  //tarverse the table and check if it's there
  for (auto& entry : HashTable[hash_key]) {
    if (entry not_eq e) {
      std::cout << "\n[Record not found at " << hash_key << "]";
      return false;
    }
  }

  //delete entry
  remove(COUNTRY);

  //tarverse again and check if enrty is still at index
  if(HashTable[hash_key].empty()) {
    return true;

  } else {
    std::cout << "\n[Expected \"nullptr\" but got \"" << &e << "\"]"; //print adress of the pointer
    return false;
  }
  return true;
}

/**
 * @brief Invokes all the test functions and stores the results in a vector
 * @return void-type
 */
void CovidDB::tests() {
  std::cout << "\n\n***** TEST REPORT *****\n\n";
  std::vector<bool> test_results;

  test_results.push_back(test_hash());
  test_results.push_back(test_add());
  test_results.push_back(check_collison());
  test_results.push_back(test_get());
  test_results.push_back(test_remove());

  for(size_t i = 0; i < test_results.size(); i++) {
    if(test_results[i] not_eq true) {
      std::cout << "TEST " << i+1 << " FAILED ###\n";
    }else  {
      std::cout << "TEST " << i+1 << " PASSED ***\n";
    }
  }
  std::cout << "\n\n";
  //std::exit(EXIT_SUCCESS);
}