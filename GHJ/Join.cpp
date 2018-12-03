#include "Join.hpp"
#include <functional>

/*
 * TODO: Student implementation
 * Input: Disk, Memory, Disk page ids for left relation, Disk page ids for right relation
 * Output: Vector of Buckets of size (MEM_SIZE_IN_PAGE - 1) after partition
 */
vector<Bucket> partition(Disk* disk, Mem* mem, pair<int, int> left_rel, pair<int, int> right_rel) {
    vector<Bucket> res(MEM_SIZE_IN_PAGE - 1, Bucket());

    for (int i = left_rel.first; i < left_rel.second; ++i) {
        mem->loadFromDisk(disk, i, 0);
        Page* page = mem->mem_page(0);
        for (size_t j = 0; j < page->size(); ++j) {
            Record rec = page->get_record(j);
            size_t bucket_id = rec.partition_hash() % (MEM_SIZE_IN_PAGE - 1) + 1;
            res[bucket_id-1].num_left_rel_record++;
            mem->mem_page(bucket_id)->loadRecord(rec);
        }
    }
    for (size_t b_id = 1; b_id < MEM_SIZE_IN_PAGE; ++b_id) {
        res[b_id-1].add_left_rel_page(mem->flushToDisk(disk, b_id));
    }

    // clean mem
    mem->reset();

    for (int i = right_rel.first; i < right_rel.second; ++i) {
        mem->loadFromDisk(disk, i, 0);
        Page* page = mem->mem_page(0);
        for (size_t j = 0; j < page->size(); ++j) {
            Record rec = page->get_record(j);
            size_t bucket_id = rec.partition_hash() % (MEM_SIZE_IN_PAGE - 1) + 1;
            res[bucket_id-1].num_right_rel_record++;
            mem->mem_page(bucket_id)->loadRecord(rec);
        }
    }
    for (size_t b_id = 1; b_id < MEM_SIZE_IN_PAGE; ++b_id) {
        res[b_id-1].add_right_rel_page(mem->flushToDisk(disk, b_id));
    }

    // clean mem
    mem->reset();
    return res;
}

/*
 * TODO: Student implementation
 * Input: Disk, Memory, Vector of Buckets after partition
 * Output: Vector of disk page ids for join result
 */
vector<int> probe(Disk* disk, Mem* mem, vector<Bucket>& partitions) {
    vector<int> res;
    int left_size = 0, right_size = 0;
    for (auto & bkt : partitions) {
        left_size += bkt.num_left_rel_record;
        right_size += bkt.num_right_rel_record;
    }
    // load left

    for (auto & bkt: partitions) {
        auto smaller_rel = (left_size <= right_size) ? bkt.get_left_rel() : bkt.get_right_rel();
        auto larger_rel = (left_size <= right_size) ? bkt.get_right_rel() : bkt.get_left_rel();

        auto left_pages = smaller_rel;
        for (auto & left_disk_num : left_pages) {
            mem->loadFromDisk(disk, left_disk_num, 0);
            Page* page = mem->mem_page(0);
            for (size_t j = 0; j < page->size(); ++j) {
                Record rec = page->get_record(j);
                size_t mem_id = rec.probe_hash() % (MEM_SIZE_IN_PAGE - 2) + 1;
                mem->mem_page(mem_id)->loadRecord(rec);
            }
        }

        auto right_pages = larger_rel;
        for (auto & right_disk_num : right_pages) {
            mem->loadFromDisk(disk, right_disk_num, 0);
            Page* page = mem->mem_page(0);
            for (size_t j = 0; j < page->size(); ++j) {
                Record rec = page->get_record(j);
                size_t mem_id = rec.probe_hash() % (MEM_SIZE_IN_PAGE - 2) + 1;
                Page* page_in_mem = mem->mem_page(mem_id);
                for (size_t k = 0; k < page_in_mem->size(); ++k) {
                    if (mem->mem_page(MEM_SIZE_IN_PAGE - 1)->full())
                        res.push_back(mem->flushToDisk(disk, MEM_SIZE_IN_PAGE - 1));
                    if (page_in_mem->get_record(k) == rec)
                        mem->mem_page(MEM_SIZE_IN_PAGE - 1)->loadPair(rec, page_in_mem->get_record(k));
                }
            }
        }

    }
    if (mem->mem_page(MEM_SIZE_IN_PAGE - 1)->size() != 0) {
        res.push_back(mem->flushToDisk(disk, MEM_SIZE_IN_PAGE - 1));
    }


    return res;
}

