#include <iostream>
#include <string>
#include <vector>

#pragma once

static std::string const COVID_FILE = "WHO-COVID-data.csv";

/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file CovidDB.h [Header file]
 * @note Header file for DataEntry and CovidDB class
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


/**
 * @class DataEntry
 * @brief DataEntry class represents a single entry of COVID-19 data 
 *        for a particular date and country.
 * @note This class is immutable once created.
 */
class DataEntry final {
private:
  std::string date;
  std::string country;
  int c_cases;
  int c_deaths;
  
public:
  DataEntry();
  
  /** @note mutators and acessors*/
  
  inline void set_date(std::string set_date) { this->date = set_date;};
  inline void set_country(std::string set_country) { this->country = set_country;};
  inline void set_c_deaths(int set_c_deaths) { this->c_deaths = set_c_deaths;};
  inline void set_c_cases(int set_c_cases) { this->c_cases = set_c_cases;};
  
  inline int get_c_cases() { return c_cases;};
  inline int get_c_deaths() { return c_deaths;};
  
  inline std::string get_date() { return date;};
  inline std::string get_country() { return country;};   
};

/**
 * @brief A hash table implementation to store Covid-19 data by country
 * @class CovidDB
 * @note The hash table size is fixed at 17.
 */
class CovidDB final {
private:
  int size = 17;
  std::vector<std::vector<DataEntry*>> HashTable;
  
public:
  inline CovidDB() {
    HashTable.resize(size);
  }
  
  inline void clear() {
    for (auto& row : HashTable) {
      for (auto& entry : row) {
        delete entry;
      }
      row.clear();
    }
    HashTable.clear();    
    HashTable.shrink_to_fit();
    ///@link https://stackoverflow.com/questions/12587774/destructor-not-being-called
  }

  inline ~CovidDB() { //handles memory
    clear();
    std::cout << "\nDESTROYED\n";
  }
  
  /** @note Copy constructor */
  CovidDB(const CovidDB& other) {
    size = other.size;
    HashTable.resize(size);
    for (int i = 0; i < size; ++i) {
      for (const auto& entry : other.HashTable[i]) {
        HashTable[i].push_back(new DataEntry(*entry));
      }
    }
  }

  /** @note Move constructor */
  CovidDB(CovidDB&& other) noexcept { //noexcept is necessray -> doesn't throw errors
    size = other.size;
    HashTable = std::move(other.HashTable);
    other.size = 0;
  }

  /** @note Overloaded assigment operator*/
  CovidDB& operator=(const CovidDB& other) {
  if (this == &other) {
    return *this;  // Self-assignment, no work needed
  }
  
  // clear the data and resources
  for (auto& row : HashTable) {
    for (auto& entry : row) {
      delete entry;
    }
    row.clear();
  }
  HashTable.clear();
  HashTable.shrink_to_fit();

  // copy the data from the other object
  size = other.size;
  HashTable.resize(size);
  for (int i = 0; i < size; ++i) {
    for (const auto& entry : other.HashTable[i]) {
      HashTable[i].push_back(new DataEntry(*entry));
    }
  }
  return *this;
}

  DataEntry* get(std::string country);
  void fetch_data(DataEntry* set, std::string country);
  bool add(DataEntry* entry);
  void add_covid_data(std::string const COVID_FILE);
  int hash(std::string country);
  void remove(std::string country);
  void display_table(); 
  void log();
  void log_memory();

  bool test_hash(); 
  bool test_add(); 
  bool check_collison();
  bool test_get();
  bool test_remove();
  void tests();
}; 

