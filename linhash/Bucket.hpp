#ifndef _BUCKET_HPP_
#define _BUCKET_HPP_

#include <vector>
#include <string>

#include "constants.hpp"

class Bucket
{
public:

	std::vector<std::string> KeysInThisBuckets;
    Bucket();
    ~Bucket();
    bool insert(std::string input);
    void print();

private:

    std::vector<std::string> keys;
    Bucket* overflowBucket;

};

#endif