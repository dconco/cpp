#include <iostream>

int Input()
{
   std::cout << "What is your Name?" << std::endl;

   std::string NameValue;
   std::cin >> NameValue;

   std::cout << "Hello " << NameValue << '!';
   return 0;
}