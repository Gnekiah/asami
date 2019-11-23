#include "KadNode.h"
#include "Kad2Node.h"
#include "ECKadNode.h"
#include <map>
#include <thread>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

uint64_t RandDataSize()
{
    // from 4KB -- 4GB
    uint64_t nData = (rand() % (1024 * 1024 * 1024)) * 4;
    if (nData < 1024 * 4)
        return RandDataSize();
    return nData;
}

int main() {
    KadNode kadnode;
    Kad2Node kad2node;
    ECKadNode eckadnode;

    std::vector<uint64_t> kad_used_vec;
    //std::vector<uint64_t> kad_clash_vec;
    std::vector<uint64_t> kad2_used_vec;
    std::vector<uint64_t> kad2_clash_vec;
    std::vector<uint64_t> eckad_used_vec;
    //std::vector<uint64_t> eckad_clash_vec;

    // 1000 nodes
    for (int i = 0; i < 1000; i++) {
        uint64_t r = Rand60();
        kadnode.AddNode(r);
        kad2node.AddNode(r);
        eckadnode.AddNode(r);
    }

    // 100000 objects
    for (int i = 0; i < 10000; i++) {
        if (i % 1000 == 0)
            std::cout << "Write Object " << i << std::endl;

        uint64_t obj_key = Rand60();
        uint64_t obj_size = RandDataSize();
        kadnode.PushData(obj_key, obj_size);
        kad2node.PushData(obj_key, obj_size);
        eckadnode.PushData(obj_key, obj_size);

        kad_used_vec.push_back(kadnode.GetAllUsedSize());
        //kad_clash_vec.push_back(kadnode.GetAllClashSize());
        kad2_used_vec.push_back(kad2node.GetAllUsedSize());
        kad2_clash_vec.push_back(kad2node.GetAllClashSize());
        eckad_used_vec.push_back(eckadnode.GetAllUsedSize());
        //eckad_clash_vec.push_back(eckadnode.GetAllClashSize());
    }

    auto write_fn = [&](std::string path, std::vector<uint64_t> vec1, 
        std::vector<uint64_t> vec2, std::vector<uint64_t> vec3, std::vector<uint64_t> vec4) {
        std::ofstream out(path, std::ios::app);
        auto it1 = vec1.begin();
        auto it2 = vec2.begin();
        auto it3 = vec3.begin();
        auto it4 = vec4.begin();
        for (; it1 != vec1.end(); it1++, it2++, it3++, it4++) {
            out << *it1 << "," << *it2 << "," << *it3 << "," << *it4 << std::endl;
        }
        out.close();
    };

    write_fn("I:/asami/ret.csv", kad_used_vec, kad2_used_vec, eckad_used_vec, kad2_clash_vec);

    return 0;
}