#pragma once

#include <string>
#include <queue>
#include <vector>
#include <mutex>
#include <cstdint>
#include <map>

typedef struct Block {
    std::string blkid;
    int size;
    bool ismeta;
    std::vector<std::string>* blkid_list;
} Block;

typedef struct Message {

} Message;

class Node {
public:
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(uint64_t id)
        : nid_(id)
    {
        used_size_ = 0;
        blk_maps_ = new std::map<uint64_t, uint64_t>();
    }
    ~Node() {
        delete blk_maps_;
    }

    // return true while clash
    bool Put(uint64_t blkid, uint64_t size)
    {
        auto iter = blk_maps_->find(blkid);
        if (iter == blk_maps_->end()) {
            used_size_ += size;
            blk_maps_->insert(std::pair<uint64_t, uint64_t>(blkid, size));
            return false;
        }
        return true;
    }
    uint64_t GetUsedSize() { return used_size_; }
    uint64_t GetId() { return nid_; }

private:
    uint64_t nid_;
    uint64_t used_size_;
    std::map<uint64_t, uint64_t>* blk_maps_ = nullptr;
};