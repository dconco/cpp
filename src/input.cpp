#include <iostream>
#include <string>
#include "types/generic.hxx"

int Input()
{
   std::cout << "What is your Name? ";

   text_t nameValue;
   std::getline(std::cin, nameValue);

   std::cout << std::endl
             << "Hello " << nameValue << '!' << std::endl;
   return 0;
}