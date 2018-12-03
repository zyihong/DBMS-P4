#include "ExtSortRange.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <queue>

// initializa Chunk of Disk memory, each page in a group by itself
// create first empty page
ExtSortRange::ExtSortRange() : groupSize(1)
{
	Page* firstPage = new Page;
	pageRange.push_back(firstPage);
}

// delete all page from pageRange
ExtSortRange::~ExtSortRange() 
{
	while (!pageRange.empty()) {
		delete pageRange.back();
		pageRange.pop_back();
	}
}

// given unsorted input values, load them into pages
// create new page when necessary, and bookmark by pageRange vector
void ExtSortRange::load(std::string inputStr) 
{
	std::stringstream iss(inputStr);
	int input;
	while (iss >> input)
	{
		if (!pageRange.back()->load(input)) {
			Page* newPage = new Page;
			newPage->load(input);
			pageRange.push_back(newPage);
		}
	}
}

void ExtSortRange::print()
{
	for (auto page : pageRange) 
	{
		page->print();
	}
	std::cout << " |" << std::endl;
}

void ExtSortRange::extMergeSort()
{
	pass0Sort();
	std::cout << "-->pass 0" << std::endl;
	print();

	int passNum = 1;
	while (passMergeSort()) 
	{
		std::cout << "-->pass " << passNum++ << std::endl;
		print();
	}
	groupSize = 1; // reset groupSize for further sort
}


// TODO: implement pass 0 of external merge sort
// Hint: You may use method functions of Page class
void ExtSortRange::pass0Sort() 
{
	for (auto it = pageRange.begin(); it != pageRange.end(); it++){
		(*it)->sortPage();
	}
}

// TODO: implement one merge sort pass (not pass0) of external merge sort
// return false if no need to sort (actually do nothing)
// Hint: You may use member variable
bool ExtSortRange::passMergeSort() 
{
	if(groupSize >= pageRange.size()){
		return false; // place holder
	}
	else{
		std::vector<Page *> newPageRange;
		Page* outputPage = new Page;
		std::vector<std::vector<int>> inputPages;

		inputPages.resize(BUFFER_PAGE - 1);
		for (int i = 0; i < BUFFER_PAGE - 1; i++){
			std::vector<int> v;
			inputPages[i] = v;
		}

		int round = 0;
		while(true){
			//there is still pages need to be merge
			int base = round * groupSize * (BUFFER_PAGE - 1);
			if(base >= pageRange.size()){break;}
			std::vector<std::vector<std::vector<int>>> chunks;
			chunks.resize(BUFFER_PAGE - 1);
			for (int i = 0; i + base < pageRange.size() && i < groupSize*(BUFFER_PAGE - 1); i++){
				chunks[(i / groupSize)].push_back(pageRange[i + base]->getData());
				delete pageRange[i + base];
				pageRange[i + base] = nullptr;
			}

			//bool chunkFinish = false;
			while(true){
				//read a page per input buffer page
				for (int i = 0; i < BUFFER_PAGE - 1; i++){
					if(inputPages[i].empty() && !chunks[i].empty()){
						inputPages[i] = chunks[i].front();
						//for (int k = 0; k < chunks[i].front().size(); k++){
						//	inputPages[i].push(chunks[i].front()[k]);
						//}
						chunks[i].erase(chunks[i].begin());
					}

				}

				std::vector<int> sortVector;
				for (int i = 0; i < BUFFER_PAGE - 1; i++){
					if (!inputPages[i].empty()){
						sortVector.push_back(inputPages[i][0]);
						//inputPages[i].pop();
						//inputPages[i].erase(inputPages[i].begin());
					}
					//else ()
				}

				if(sortVector.empty()){break;}

				std::sort(sortVector.begin(), sortVector.end());

				int min = sortVector[0];

				for (int i = 0; i < BUFFER_PAGE - 1; i++){
					if (!inputPages[i].empty() && inputPages[i][0] == min){
						inputPages[i].erase(inputPages[i].begin());
						break;
					}
				}

				if(!outputPage->load(min)){
					//output filled
					Page* newSortedPage = new Page;
					for(auto num : outputPage->getData()){
						newSortedPage->load(num);
					}
					newPageRange.push_back(newSortedPage);
					delete outputPage;

					outputPage = new Page;
					outputPage->load(min);
				}

			}

			round++;

		}

		if(!outputPage->getData().empty()){
			Page* newSortedPage = new Page;
			for(auto num : outputPage->getData()){
				newSortedPage->load(num);
			}
			newPageRange.push_back(newSortedPage);
		}

		delete outputPage;

		pageRange = newPageRange;
	}

	groupSize *= (BUFFER_PAGE - 1);
	return true;
}
