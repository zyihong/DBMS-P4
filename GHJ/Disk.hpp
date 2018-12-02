#ifndef _DISK_HPP_
#define _DISK_HPP_

#include <vector>
#include <string>
#include <utility>

#include "constants.hpp"
#include "Page.hpp"

using namespace std;

class Disk
{
public:

    Disk();

    ~Disk();

    // Do not directly use this function in Join.cpp
    int diskWrite(Page* p);

    // Do not directly use this function in Join.cpp 
    Page* diskRead(int pos);

    // Inspect the content of page in disk with specific id
    void print(int id);

    // Inspect the content of all pages in disk
    void print();

    // Function used in main.cpp to load relation from txt file
    // Do not use this function in Join.cpp
    pair<int, int> read_data(const char* file_name);


private:

	vector<Page*> pages;

};

#endif