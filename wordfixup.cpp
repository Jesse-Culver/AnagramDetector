#include "wordfixup.h"
std::string WordFixUp(std::string input, int location)
{
        for(int i = location; i<input.size(); i++)
        {
                if(i != input.size())
                        input[i] = input[i+1];
                else
                        input[i] = '\0';
        }
        input.resize(input.size()-1);
        return input;
}

