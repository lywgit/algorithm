#ifndef HEAP_H
#define HEAP_H

#include<iostream>
#include<vector>

using std::vector;

struct Node{
    Node(int id, int key) { id_ = id; key_ = key; };
    int id_;
    int key_;
};

class Heap{
    public:
        void insert(Node node);
        void erase(Node node);
        bool empty(){ return data_.empty();};
        Node pop_min();
        vector<Node> data_;
    private:
        void shift_up(int i);
        void shift_down(int i);
        void swap(int i, int j);
};



#endif
