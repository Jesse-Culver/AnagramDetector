#include <algorithm>
#include <iostream>
#include "interface.h"
#include "anagramdetector.h"
#include "wordfixup.h"
void Interface()
{
	bool validinput = false;
	std::string userword;
	std::string tempword;
	validinput = false;
	std::cout<<"Please provide a word and the program will check if it can be made into an anagram for another word"<<std::endl;
	while(!validinput)
	{
		userword.erase(userword.begin(), userword.end());//Make sure we are clean
		tempword.erase(tempword.begin(), tempword.end());
		std::getline(std::cin,tempword);
		for(int i = 0; i<tempword.length(); i++)//cleanup input
		{
			if(!isalpha(tempword[i])|| tempword[i] == ' ')
				tempword = WordFixUp(tempword,i);
			std::transform(tempword.begin(), tempword.end(), tempword.begin(), ::tolower); //common one liner I found online
			if(!tempword.empty())
				validinput = true;
		}
	}
	userword = tempword;
	#ifdef DEBUG_
	std::cout<<"Word is: "<<userword<<"*"<<std::endl;
	#endif
	AnagramCheck(userword);
}

