#ifndef _LINHASHIDX_HPP_
#define _LINHASHIDX_HPP_

#include <vector>

#include "Bucket.hpp"
#include "constants.hpp"

class LinHashIdx
{
public:

    LinHashIdx();
    std::vector<std::string> AllKeys;
    void insert(std::string input);
    bool contains(std::string input);
    int getHashNum(int x, unsigned int L);
    void handleSplit(int BucketNum);
    void print();

private:

    std::vector<Bucket*> directory;
    unsigned int next;
    unsigned int level;
    //unsigned int insertionLevel;

};

#endif