#include <iostream>
#include <string>

#include "ExtSortRange.hpp"


int main()
{
	ExtSortRange ext;
	std::string input;
	while (std::cin >> input)
	{
		if (input == "print")
		{
			ext.print();
		}
		else if (input == "exit")
		{
			break;
		}
		else if (input == "sort")
		{
			ext.extMergeSort();
		}
		else 
		{
			ext.load(input);
		}
	}
	std::cout << "exiting" << std::endl;
}