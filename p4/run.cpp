#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <thread>
#include <stdexcept>
#include <cctype>
#include <cassert>

#include "run.h"
#include "CovidDB.h"

#define LOG

/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file assignment3.cpp [Driver Code]
 * @note Driver code for A3
 * 
 * @brief This assigment focuses on using multiple operations regarding BST like:
 *   - Insertion
 *   - Traversals
 *   - Searching
 *   - Deletion
 * 
 * Those operations were implemented using a ShelterBST class that includes a struct for Pets and
 * A struct for the TreeNodes.  
 */


/** @todo
 * test and assert
 * Clarify what to print
 * Make the output neater
*/


/** @name OPID (opeartion ID)
 * @enum for the switch statement
 * @brief Every operation has a numerical value
 */
enum OPID {
           ID_1 = 1,
           ID_2 = 2,
           ID_3 = 3,
           ID_4 = 4,
           ID_5 = 5,
           ID_6 = 6,
           ID_7 = 7,
           ID_8 = 8,
           ID_9 = 9
};

/**
 * @brief Displays the menu for user interaction.
 */
void menu() {
  std::cout << "\n*** Welcome to the COVID-19 Data Base ***\n\n"
            << "[1]\tCreate a Hash Table with the WHO file\n"
            << "[2]\tAdd a Data entry\n" //segfault
            << "[3]\tGet a Data entry\n"
            << "[4]\tRemove a Data entry\n" //segfault if no entry
            << "[5]\tDisplay HasH Table\n"
            << "[6]\tLog Data [covid_db.log]\n"
            << "[7]\tLog Memory [valgrind.log]\n"
            << "[8]\tRun Tests\n"
            << "[9]\tQuit\n";
}

/**
 * @brief Takes a string and returns a boolean indicating the validity of the month.
 * 
 * @param month The input month as a string.
 * @return True if the month is valid, false otherwise.
 */
bool valid_moth(std::string month) {
  if(month.length() != 1 and month.length() != 2) {
    return false;
  } else if (std::stoi(month) > 13) {
    return false;
  } else if (std::stoi(month) <  1) {
    return false;
  }
  return true;
}

/**
 * @brief Takes a string and returns a boolean indicating the validity of the day.
 * 
 * @param day The input day as a string.
 * @return True if the day is valid, false otherwise.
 */
bool valid_day(std::string day) {
  if(day.length() != 1 and day.length() != 2) {
    return false;
  } else if (std::stoi(day) > 31) {
    return false;
  } else if (std::stoi(day) <  1) {
    return false;
  }
  return true;
}

/**
 * @brief Takes a string reference and returns a boolean indicating the validity of the year.
 * 
 * @param year The input year as a string reference.
 * @return True if the year is valid, false otherwise.
 */
bool valid_year(std::string &year) {
    if(year.length() == 4) {
      year = year[2] + year [3];
      return true;
    } else if(year.length() != 2) {
      return false;
    }
    return true;
}

/**
 * @brief Takes a string reference as an argument and returns a string.
 *
 * @param date The input date as a string reference.
 * @return The processed date as a string.
 * IMPORTANT: @invariant user does not enter a word input
 */
std::string get_date(std::string &date) {
  
  std::string month = "\0";
  std::string day = "\0";
  std::string year = "\0";

  bool is_valid = false;
  while(not is_valid) {
    std::cout << "[FORMAT: mm/dd/yy][Enter a Date]: ";
    std::getline(std::cin, date);
    std::size_t month_loc = date.find("/");
    std::string month_prev = date.substr(0,month_loc);
    
    
    if(month_prev[0] == 0) {
      month = month_prev[1]; //if preceding 0 -> trim
    } else {
      month = month_prev; //if single digit -> keep
    }
    
    
    std::string s_str = date.substr(month_loc+1);
    std::size_t day_loc = date.find("/");
    std::string day_prev = s_str.substr(0, day_loc);

    if(day_prev[0] == 0) {
      day = day_prev[1];
    } else {
      day = day_prev;
    }

    year = s_str.substr(day_loc+1);
    is_valid = valid_day(day) and valid_moth(month) and valid_year(year);
  }
  return month + "/" + day + "/" + year;
}

/**
 * @brief Takes a string reference as an argument and returns a string.
 *
 * @param country The input country as a string reference.
 * @return The processed country as a string.
 */
std::string get_country(std::string& country) {
  while(true) {
    std::cout << "[Enter a country]: ";
    std::cin >> country;
    std::cin.ignore();
    try {
      // check if the input is a string
      if (!std::all_of(country.begin(), country.end(), [](char c){ return std::isalpha(c); })) {
        throw std::invalid_argument("[Input must be a string]");
        }
      
      bool is_all_lowercase = std::all_of(country.begin(), country.end(), [](char c){ return std::islower(c); });
      
      if (is_all_lowercase) {
        country[0] = std::toupper(country[0]);
        std::transform(country.begin()+1, country.end(), country.begin()+1, [](char c){ return std::tolower(c); });
      } else  {
        return country;
      }
    } catch (const std::exception& e) {
      std::cerr << "\nError: " << e.what() << '\n';
      return "";
    }
  }
  // return the modified string
  return "";
}

/**
 * @brief Takes an integer reference as an argument and returns an integer.
 *
 * @param cases The input Covid cases as an integer reference.
 * @return The processed Covid cases as an integer.
 */
int get_covid_cases(int &cases) {
  typedef std::numeric_limits<int> IntLimits;
  
  const int INT_MAX = IntLimits::max();
  
  std::cout << "[Enter cases]: ";
  std::cin >> cases;
  
  try {
    if(cases < 0) {
      throw std::invalid_argument("[Cases cannot be negative!]");
    }
    if(cases > INT_MAX) {
        throw std::invalid_argument("[Integer overflow!]");
    } else {
      return cases;
    }
    
  } catch (const std::exception& e) {
    std::cerr << "\nError: " << e.what() << std::endl;
    return 0;
  }
  return 0;
}

/**
 * @brief Takes an integer reference as an argument and returns an integer.
 *
 * @param deaths The input Covid deaths as an integer reference.
 * @return The processed Covid deaths as an integer.
 */
int get_covid_deaths(int &deaths) {
  typedef std::numeric_limits<int> IntLimits;
  
  const int INT_MAX = IntLimits::max();
  
  while(true) {
    std::cout << "[Enter deaths]: ";
    std::cin >> deaths;
    try {
      if(deaths < 0) {
        throw std::invalid_argument("[Cases cannot be negative!]");
      }
      if(deaths > INT_MAX) {
        throw std::invalid_argument("[Integer overflow!]");
      } else {
        return deaths;
      }
    } catch (const std::exception& e) {
      std::cerr << "\nError: " << e.what() << std::endl;
      return 0;
    }
  }
  return 0;
}

/**
 * @brief Prompts the user to enter a valid intiger coresponding to one of the valus in the menu
 *        the user is prompted to enter the input again if it's not a number
 *
 * @return The processed input as an integer.
 */
int get_input() {
  int const MIN = 1;
  int const MAX = 9;
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
        throw std::out_of_range("[Input out of range. Please enter an integer between 1 and 7]");
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
  std::cout << "\n\nGoodbye!\n\n";
}

/**
 * @brief Takes a DataEntry* pointer and several arguments (country, date, cases, deaths)
 *        to set the data.
 * 
 * @param data A pointer to a DataEntry object.
 * @param country The country associated with the data.
 * @param date The date associated with the data.
 * @param cases The number of Covid cases associated with the data.
 * @param deaths The number of Covid deaths associated with the data.
 */
void set_data(DataEntry* data, std::string country, std::string date, int cases, int deaths) {
  data->set_country(get_country(country));
  data->set_date(get_date(date));
  data->set_c_cases(get_covid_cases(cases));
  data->set_c_deaths(get_covid_deaths(deaths));
}

/**
 * @brief Executes the main logic of the program in a while(true) loop.
 */
void run() {
  /** DECLARATIONS: */
  std::cout << std::endl << std::endl << std::flush;
  CovidDB data_base;
  DataEntry *data = new DataEntry; //#2 allocation (new DataEntry)
  
  std::string country = "\n";
  std::string date = "\0";
  int cases = 0;
  int deaths = 0;
  /** DECLARATIONS: */
  
  while(true) {
    menu();
    switch(get_input()) {
    case OPID::ID_1: {
      data_base.add_covid_data(COVID_FILE);
      break;
    }
      
    case OPID::ID_2: {
      set_data(data, country, date, cases, deaths);
      bool added = data_base.add(data);
      if(added) {
        std::cout << "\n[Record added]\n";
      } else {
        std::cout << "\n[Failed to add the entry]\n";
      }
      // std::this_thread::sleep_for(std::chrono::seconds(3));
      // system("clear");
      break;
    }
      
    case OPID::ID_3: {
      data_base.fetch_data(data, get_country(country));
      break;
    }
      
    case OPID::ID_4: {
      data_base.remove(get_country(country));
      break;
    }
      
    case OPID::ID_5: {
      data_base.display_table();
      break;
    }
      
    case OPID::ID_6: {
      #ifdef LOG
      data_base.log();
      #else
      std::cout << "\n[Define [LOG macro in run.cpp] to run]\n";
      #endif // LOG
      break;
    }

    case OPID::ID_7: {
      #ifdef LOG
      data_base.log_memory();
      std::exit(EXIT_SUCCESS);
      #else
      std::cout << "\n[Define [LOG macro in run.cpp] to run]\n";
      #endif
      break;
    }

    case OPID::ID_8: {
      data_base.tests();
      std::this_thread::sleep_for(std::chrono::seconds(4));
      system("clear");
      break;
    }

    case OPID::ID_9: {
      goodbye();
      //delete data; //
      std::exit(EXIT_SUCCESS);
      break;
    }

    default: {
      /** @note do nothing...*/
    }
    }
  }
  std::cout << std::endl << std::endl << std::flush;
}
