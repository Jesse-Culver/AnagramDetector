#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "anagramdetector.h"

//We take the users string sort all letters alphabetically then compare it to our word list by sorting the letters in each word alphabetically
//If it comes back as true that means both the users word and the dictionay word contain the same characters
int AnagramCheck(char *inputFromUser, char *resultText)
{
	std::string sortedUserString(inputFromUser);
	int resultCount = 0;
	//Clean resultText
	for(int i = 0; i < (1024*16); i++)
	{
		resultText[i] = '\0';
	}

	std::vector<std::string> wordVector;
	std::vector<int> matchingWord;
	std::ifstream wordFile("words.txt");
	//Sort letters in string alphabetically
	std::sort(sortedUserString.begin(), sortedUserString.end());

	//Thanks to http://stackoverflow.com/questions/8365013/reading-line-from-text-file-and-putting-the-strings-into-a-vector
	std::copy(std::istream_iterator<std::string>(wordFile),
		std::istream_iterator<std::string>(),
		std::back_inserter(wordVector));

	std::vector<std::string> wordVectorSorted = wordVector;
	for(int i = 0; i<wordVectorSorted.size(); i++)
	{
		//Sort letters in word alphabetically
		std::sort(wordVectorSorted[i].begin(), wordVectorSorted[i].end());
		//Compare the two sorted words
		if(wordVectorSorted[i].compare(sortedUserString)== 0)
		{
			std::string tempString = wordVector[i] + "\n";
			strncat(resultText, tempString.c_str(), tempString.length()+1);
			resultCount++;
		}
	}
	return resultCount;
}
