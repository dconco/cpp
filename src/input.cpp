#include <iostream>

using namespace std;

int Input()
{
   cout << "What is your Name?" << endl;

   string NameValue;
   cin >> NameValue;

   cout << "Hello " << NameValue;
   return 0;
}