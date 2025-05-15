#include <iostream>
#include <ctime>

int Random()
{
   long ElapsedSeconds = time(nullptr);
   srand(ElapsedSeconds);

   int num{rand()};
   std::cout << std::endl
             << "Random Function: " << num;
   return 0;
}