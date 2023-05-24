/** @name Pet source code                                                            
 * @file pet.cpp                                                               
 * @author Jakob Balkovec                                                        
 * @brief implementation file for the Pet class for A1.                        
 * This file defines the Pet class methods                                                         
 */

#include "pet.h"

/** @name Pet Construcotor
 * @brief Constructor for the Pet class.
 * @param name The name of the pet.
 * @param category The category of the pet (dog/cat).
 */
Pet::Pet(std::string name, std::string category)
  : name(name), category(category) {}

/** @name getName
 * Returns the name of the pet.
 * @return The name of the pet.
 */
std::string Pet::getName() {
  return name;
}

/** @name getCategory
 * Returns the category of the pet.
 * @return The category of the pet.
 */
std::string Pet::getCategory() {
  return category;
}
