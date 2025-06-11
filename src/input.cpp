#include <iostream>
#include <string>
#include "types/generic.hxx"
#include "capitalizeEachWords.cpp"

using namespace std;

int Input()
{
   text_t nameValue;

   do
   {
      if (!nameValue.empty() && nameValue.length() < 3)
      {
         cout << "Name should be greater than 2!" << endl
              << endl;
      }

      cout << "What is your Name? ";
      getline(cin, nameValue);
   } while (nameValue.empty() || nameValue.length() < 3);

   nameValue = capitalizeEachWord(nameValue);

   cout << endl
        << "Hello " << nameValue << '!' << endl;
   return 0;
}