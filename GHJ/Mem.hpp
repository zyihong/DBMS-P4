/*
 * This files defines the data structure for Memory
 * DO NOT MODIFY THIS FILE
 */
#ifndef _MEM_HPP_
#define _MEM_HPP_

#include <vector>
#include <string>

#include "constants.hpp"
#include "Page.hpp"
#include "Disk.hpp"


using namespace std;

class Mem
{
public:

    Mem();

    ~Mem();

    /* Load specific disk page to specific memory page */
    void loadFromDisk(Disk* d, int disk_page_id, int mem_page_id);

    /*
     * Write specific memory page into disk, and reset memory page
     * Return written disk page id
     */
    int flushToDisk(Disk* d, int mem_page_id);

    // reset all memory pages
    void reset();

    /* Print all the records info in Memory*/
    void print();

    /* Return specific memory page */
    Page* mem_page(int page_id);

private:

	vector<Page*> pages;

};

#endif