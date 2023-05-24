/** @name class Pet                                                               
 * @file pet.h -> @headerfile                                                  
 * @author Jakob Balkovec                                                        
 * @brief Header file for the Pet class for my A1.                             
 *        This file defines the Pet class                                                                   
 */

#ifndef PET_H
#define PET_H

#pragma once

#include <string>

/// @class Pet
class Pet {
private:
  std::string name;
  std::string category;
public:
  Pet(std::string name, std::string category);
  std::string getName();
  std::string getCategory();
};

#endif //PET_H
