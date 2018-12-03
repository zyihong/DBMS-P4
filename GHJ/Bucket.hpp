#ifndef _BUCKET_HPP_
#define _BUCKET_HPP_

#include "Page.hpp"

class Bucket {
    
public:

    Bucket();
    // add the disk page id of left relation into this bucket/partition
    void add_left_rel_page(int page_id);
    // add the disk page id of right relation into this bucket/partition
    void add_right_rel_page(int page_id);
    // return a list of page ids in disk from left relation in this bucket/partition
    vector<int> get_left_rel();
    // return a list of page ids in disk from right relation in this bucket/partition
    vector<int> get_right_rel();

    // number of record from left relation in this bucket
    size_t num_left_rel_record = 0;
    // number of record from right relation in this bucket
    size_t num_right_rel_record = 0;

private:
	// list of disk page ids contain the records from left relation in this bucket
    vector<int> left_rel;
    // list of disk page ids contain the records from right relation in this bucket
    vector<int> right_rel;
};


#endif