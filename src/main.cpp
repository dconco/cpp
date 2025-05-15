#include <iostream>
#include "input.cpp"
#include "math.cpp"
#include "random.cpp"

int main()
{
   Input();
   Random();

   int Result{multiply(3, 5)};
   std::cout << std::endl
             << std::endl
             << "Math Result: " << Result << std::endl;

   return 0;
}