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
    KeysInThisBuckets.push_back(input);
    if(overflowBucket == nullptr){
        //if(keys.size() == MAX_BUCKET_SIZE){
            //overflow
        //}
        if (keys.size() == MAX_BUCKET_SIZE){
            overflowBucket = new Bucket;
            overflowBucket->keys.push_back(input);
            return true;

        }
        else{
            keys.push_back(input);
        }

    }
    else {
        overflowBucket->keys.push_back(input);
        return true;
    }

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