#include <iostream>
#include "input.cpp"
#include "math.cpp"
#include "random.cpp"
#include "header.hxx"
#include "array.cpp"

int main()
{
   Input();
   Random();

   int Result{Math::multiply(3, 5)};
   std::cout << std::endl
             << std::endl
             << "Math Result: " << Result << std::endl;

   int numbers[5] = {1, 2, 3, 4, 5};
   int size = sizeof(numbers) / sizeof(numbers[0]);
   int element;

   std::cout << std::endl
             << "Enter the element you want to search for: ";
   std::cin >> element;

   int index = searchArray(numbers, size, element);

   if (index < 0)
   {
      std::cout << "'" << element << "' is not in the array!" << std::endl;
   }
   else
   {
      std::cout << "'" << element << "' is at index " << index << std::endl;
   }

   return 0;
}