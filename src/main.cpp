#include <iostream>
#include "input.cpp"
#include "math.cpp"

using namespace std;

int main()
{
   Input();

   int Result = divide(10, 5);
   cout << endl
        << endl
        << "Math Result: " << Result << endl;

   return 0;
}