/*
 * This file defines the data structure for Data Record
 * DO NOT MODIFY THIS FILE
 */
#ifndef _RECORD_HPP_
#define _RECORD_HPP_

#include <vector>
#include <string>
#include <iostream>

#include "constants.hpp"

using namespace std;

class Record {
public:

    /* Constructor */
    Record(string joinKey, string data);

    /* Copy constructor */
    Record(const Record &r2);

    /* Print the key and data with in record*/
    void print() {cout << "Record with key=" << key << " and data=" << data << "\n";}

    /* Hash value of key in the partition phase */
    size_t partition_hash();

    /* Hash value of key in the probe phase*/
    size_t probe_hash();

    /* Equality comparator */
    bool operator ==(const Record& r2) const;

private:

	string key;
	string data;

};

#endif