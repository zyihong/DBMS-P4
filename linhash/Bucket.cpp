#include "Bucket.hpp"

#include <iostream>
#include <algorithm>

Bucket::Bucket() : overflowBucket(nullptr)
{

}

Bucket::~Bucket()
{
    if (overflowBucket)
    {
        delete overflowBucket;
    }
}

// Insert the key into the bucket, or one of its overflow buckets.
// Return true if an overflow bucket was used
bool Bucket::insert(std::string input)
{
    // Insert your code here

    return false;
}

// DO NOT MODIFY THIS FUNCTION!
// 
// Print all keys in this bucket and all of its overflow buckets.
// Keys are separated by spaces, and buckets are separated by '|'.
void Bucket::print()
{
    std::cout << "| ";
    for (auto& key : keys)
    {
        std::cout << key << " ";
    }
    std::cout << "|";

    if (overflowBucket)
    {
        overflowBucket->print();
    }
}