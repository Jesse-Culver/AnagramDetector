#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include "anagramdetector.h"

void AnagramCheck(std::string userString)
{
	std::string sortedUserString = userString;
	std::vector<std::string> wordVector;
	std::vector<int> matchingWord;
	std::ifstream wordFile("words.txt");
	std::sort(sortedUserString.begin(), sortedUserString.end());

	//Thanks to http://stackoverflow.com/questions/8365013/reading-line-from-text-file-and-putting-the-strings-into-a-vector
	std::copy(std::istream_iterator<std::string>(wordFile),
		std::istream_iterator<std::string>(),
		std::back_inserter(wordVector));

	std::vector<std::string> wordVectorSorted = wordVector;
	for(int i = 0; i<wordVectorSorted.size(); i++)
	{
		std::sort(wordVectorSorted[i].begin(), wordVectorSorted[i].end());
		if(wordVectorSorted[i].compare(sortedUserString)== 0)
			std::cout<<wordVector[i]<<std::endl;
	}
}
