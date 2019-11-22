#include "Node.h"

Node::Node(std::string nodeid)
    : nodeid_(nodeid)
{
    blk_list_ = new std::vector<Block>();
    msg_list_ = new std::queue<Message>();
}

void Node::Start() {


}

void Node::PushMessage(Message msg) {
    msg_list_lock_.lock();
    msg_list_->push(msg);
    msg_list_lock_.unlock();
}