#include <iostream>
#include <string>
#include <cctype>
#include "header.hxx"

std::string capitalizeEachWord(std::string word)
{
   std::string newWord;

   for (size_t i = 0; i < word.length(); ++i)
   {
      if (i == 0 || word[i - 1] == ' ')
      {
         newWord += std::toupper(word[i]);
      }
      else
      {
         newWord += word[i];
      }
   }

   return newWord;
}