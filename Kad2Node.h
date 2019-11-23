#pragma once

#include "Node.h"

#include <string>
#include <queue>
#include <vector>
#include <map>
#include <mutex>
#include "header.h"

class Kad2Node {
public:
    Kad2Node(const Kad2Node&) = delete;
    Kad2Node& operator=(const Kad2Node&) = delete;
    Kad2Node() {
        all_clash_size_ = 0;
        all_used_size_ = 0;
        node_maps_ = new std::map<uint64_t, Node*>();
    }
    ~Kad2Node() {
        for (auto iter = node_maps_->begin(); iter != node_maps_->end(); iter++)
            delete iter->second;
        delete node_maps_;
    }

    void AddNode(uint64_t id) {
        node_maps_->insert(std::pair<uint64_t, Node*>(id, new Node(id)));
    }
    uint64_t GetAllUsedSize() { return all_used_size_; }
    uint64_t GetAllClashSize() { return all_clash_size_; }

    // 4+4 codec, with 4 duplication
    void PushData(uint64_t objid, uint64_t _size) {
        uint64_t objid1 = Rand60();
        uint64_t objid2 = Rand60();
        uint64_t objid3 = Rand60();
        uint64_t objid4 = Rand60();
        uint64_t objid5 = Rand60();
        uint64_t objid6 = Rand60();
        uint64_t objid7 = Rand60();
        uint64_t objid8 = Rand60();
        uint64_t size = _size / 4;

        std::set<uint64_t> node_grp;

        std::map<uint64_t, Node*> xor_map1;
        std::map<uint64_t, Node*> xor_map2;
        std::map<uint64_t, Node*> xor_map3;
        std::map<uint64_t, Node*> xor_map4;
        std::map<uint64_t, Node*> xor_map5;
        std::map<uint64_t, Node*> xor_map6;
        std::map<uint64_t, Node*> xor_map7;
        std::map<uint64_t, Node*> xor_map8;
        for (auto iter = node_maps_->begin(); iter != node_maps_->end(); iter++) {
            uint64_t xxor1 = objid1 ^ (iter->first);
            uint64_t xxor2 = objid2 ^ (iter->first);
            uint64_t xxor3 = objid3 ^ (iter->first);
            uint64_t xxor4 = objid4 ^ (iter->first);
            uint64_t xxor5 = objid5 ^ (iter->first);
            uint64_t xxor6 = objid6 ^ (iter->first);
            uint64_t xxor7 = objid7 ^ (iter->first);
            uint64_t xxor8 = objid8 ^ (iter->first);
            xor_map1.insert(std::pair<uint64_t, Node*>(xxor1, iter->second));
            xor_map2.insert(std::pair<uint64_t, Node*>(xxor2, iter->second));
            xor_map3.insert(std::pair<uint64_t, Node*>(xxor3, iter->second));
            xor_map4.insert(std::pair<uint64_t, Node*>(xxor4, iter->second));
            xor_map5.insert(std::pair<uint64_t, Node*>(xxor5, iter->second));
            xor_map6.insert(std::pair<uint64_t, Node*>(xxor6, iter->second));
            xor_map7.insert(std::pair<uint64_t, Node*>(xxor7, iter->second));
            xor_map8.insert(std::pair<uint64_t, Node*>(xxor8, iter->second));
        }

        auto push_fn = [&](std::map<uint64_t, Node*> st) {
            int i = 0;
            for (auto iter = st.begin(); iter != st.end() && i < 4; iter++, i++) {
                auto n = iter->second;
                bool ret = n->Put(iter->first, size);
                if (!ret)
                    all_used_size_ += size;
                node_grp.insert(n->GetId());
            }
        };

        push_fn(xor_map1);
        push_fn(xor_map2);
        push_fn(xor_map3);
        push_fn(xor_map4);
        push_fn(xor_map5);
        push_fn(xor_map6);
        push_fn(xor_map7);
        push_fn(xor_map8);

        int cnt = node_grp.size();
        _ASSERTE(cnt <= 32);
        all_clash_size_ += size * (32 - cnt);
    }

private:
    uint64_t all_clash_size_;
    uint64_t all_used_size_;
    std::map<uint64_t, Node*>* node_maps_ = nullptr;
};