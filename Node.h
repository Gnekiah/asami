#pragma once

#include <string>
#include <queue>
#include <vector>
#include <mutex>

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
    Node(std::string nodeid);
    void Start();

    void PushMessage(Message msg);

private:
    std::string nodeid_;
    std::vector<Block>* blk_list_ = nullptr;
    std::queue<Message>* msg_list_ = nullptr;
    std::mutex msg_list_lock_;
};