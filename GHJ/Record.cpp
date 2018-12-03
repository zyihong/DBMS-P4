#include "Record.hpp"
#include "constants.hpp"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

Record::Record(string joinKey, string data){
    this->key = joinKey;
    this->data = data;
}

Record::Record(const Record &r2){
	key = r2.key;
	data = r2.data;
}

/* h1 used at partition stage */
size_t Record::partition_hash() {
    /* Use stl hash function */
    hash<string> str_hash;
    return str_hash(this->key);
}

/* h2 different from h1 */
size_t Record::probe_hash() {
    /* Use stl hash function */
    hash<string> str_hash;
    return str_hash("key:" + this->key);
}

/* Equality comparator */
bool Record::operator ==(const Record& r2)const {
    hash<string> str_hash;
    /* If two records have different hash values(h2) of key, exit */
    if (str_hash("key:" + this->key)%(MEM_SIZE_IN_PAGE-2) != str_hash("key:" + r2.key)%(MEM_SIZE_IN_PAGE-2)) {
        cerr << "Error: Can not compare two records with different hash values(h2) of key." << endl;
        exit(1);
    }
    if (this->key == r2.key) {
        return true;
    }
    else {
        return false;
    }
}