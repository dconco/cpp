#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include "header.hxx"

int Random()
{
   long elapsedSeconds = time(nullptr);
   // srand(ElapsedSeconds);

   // int num{rand()};

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<int> dist(elapsedSeconds);

   int num{dist(gen)};

   std::cout << std::endl
             << "Random Function: " << num;
   return 0;
}