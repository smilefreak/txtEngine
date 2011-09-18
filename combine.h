/*
 *
 * @file combine.h
 * @description deals with the combine command
 *
 */

#ifndef COMBINE_H_
#define COMBINE_H_

#include <iostream>
#include <string>
#include "StateDescriptor.h"

class Item;

class combine{
	
 public:
   combine(std::string id,std::string first_id, std::string second_id);
   ~combine();
   Item* get_combination();
   std::string get_id();
   std::string get_first_id();
   std::string get_second_id();
   std::string get_description();
   void set_combination(Item * item);
   void set_description(StateDescriptor * d);
 private:
   // the description when you combine the things
   StateDescriptor * description;
   // First item_id 
   std::string first_id;
   // Second item_id
   std::string second_id;
   // The item that is the combination
   Item * combination;
   // combine id
   std::string id;
};

#endif 
