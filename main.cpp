#include "Node.h"
#include <map>
#include <thread>
#include <string>
#include <vector>

std::string generate_node_id() {
    std::string id = "";

    // TODO
    return id;
}

int main() {
    std::map<std::string, Node*> node_maps;
    std::vector<std::thread*> thread_vecs;

    for (int i = 0; i < 100; i++) {
        std::string nodeid = generate_node_id();
        Node* node = new Node(nodeid);
        node_maps.insert(std::pair<std::string, Node*>(nodeid, node));
    }

    for (auto iter = node_maps.begin(); iter != node_maps.end(); iter++) {
        Node* n = iter->second;
        std::thread *thread = new std::thread(&Node::Start, n);
        thread_vecs.push_back(thread);
    }

    for (auto iter = thread_vecs.begin(); iter != thread_vecs.end(); iter++) {
        std::thread* t = *iter;
        t->join();
        
    }

    return 0;
}