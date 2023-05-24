#include <string>
#include "CovidDB.h"

/** DOCUMENTATION:
 * @author Jakob Balkovec
 * @file run.cpp [Source Code]
 * @note Header file for helper functions
 * @remark this file defines a set of helper functions that most get or check parameters 
 */

#pragma once

/** @brief 
 * @name get_date: Takes a string reference as an argument and returns a string 
 * @name get_country: Takes a string reference as an argument and returns a string.
 * @name get_country: Takes a string reference as an argument and returns a string.
 * @name get_coivd_cases: Takes an integer reference as an argument and returns an integer.
 * @name get_covid_deaths: Takes an integer reference as an argument and returns an integer.
 */
std::string get_date(std::string &date);
std::string get_country(std::string &country);
int get_coivd_cases(int &cases);
int get_covid_deaths(int &deaths);

/** @brief 
 * @name set_data: Takes a DataEntry* pointer and several arguments
 * @param (country, date, cases, deaths) 
 * to set the data.
 */
void set_data(DataEntry* data, std::string country, std::string date, int cases, int deaths);

/** @brief 
 * @name get_input: Takes no arguments and returns an integer.
 * @name goodbye: Takes no arguments and returns void.
 * @name menu: Takes no arguments and returns void.
 * @name run: Takes no arguments and returns void.
*/
int get_input();
void goodbye();
void menu();
void run();

/** @brief 
 * @name valid_month: Takes a string and returns a boolean indicating the validity of the month.
 * @name valid_day: Takes a string and returns a boolean indicating the validity of the day.
 * @name valid_year: Takes a string reference and returns a boolean indicating the validity of */
bool valid_moth(std::string);
bool valid_day(std::string);
bool valid_year(std::string &year);

/**
 * @brief 
 * @name show_last_compiled
 * @param file Name of the file that is being compiled
 * @param date Date of when the file was last compiled
 * @param time Time of when the file was last compiled
 * @param author Author of the code
 * @note all params are arrays of chars
 */
inline void show_last_compiled(const char* file, const char* date, const char* time, const char* author) {
  std::cout << "\n[" << file << "] " << "Last compiled on [" << date << "] at [" << time << "] by [" << author << "]\n" << std::endl;
}


