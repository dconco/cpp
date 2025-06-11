#include <iostream>
#include "header.hxx"

int searchArray(int array[], int size, int element)
{
   for (int i = 0; i < size; i++)
   {
      if (array[i] == element)
      {
         return i;
      }
   }
   return -1;
}