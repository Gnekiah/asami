#pragma once

#include "Node.h"

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <mutex>
#include <set>
#include "header.h"

class KadNode {
public:
    KadNode(const KadNode&) = delete;
    KadNode& operator=(const KadNode&) = delete;
    KadNode() {
        all_clash_size_ = 0;
        all_used_size_ = 0;
        node_maps_ = new std::map<uint64_t, Node*>();
    }
    ~KadNode() {
        for (auto iter = node_maps_->begin(); iter != node_maps_->end(); iter++)
            delete iter->second;
        delete node_maps_;
    }

    void AddNode(uint64_t id) {
        node_maps_->insert(std::pair<uint64_t, Node*>(id, new Node(id)));
    }
    uint64_t GetAllUsedSize() { return all_used_size_; }
    uint64_t GetAllClashSize() { return all_clash_size_; }

    void PushData(uint64_t objid, uint64_t size) {
        std::map<uint64_t, Node*> xor_map;
        for (auto iter = node_maps_->begin(); iter != node_maps_->end(); iter++) {
            uint64_t xxor = objid ^ iter->first;
            xor_map.insert(std::pair<uint64_t, Node*>(xxor, iter->second));
        }

        int i = 0;
        for (auto iter = xor_map.begin(); iter != xor_map.end() && i < 20; iter++, i++) {
            auto node = iter->second;
            bool ret = node->Put(objid, size);
            if (!ret)
                all_used_size_ += size;
        }
    }

private:
    uint64_t all_clash_size_;
    uint64_t all_used_size_;
    std::map<uint64_t, Node*> *node_maps_ = nullptr;
};