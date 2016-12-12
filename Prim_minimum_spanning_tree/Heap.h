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
        bool empty(){ return data_.empty(); };
        int size(){ return data_.size();};
        Node pop();
        Node peek();
        friend void print_heap(const Heap &);
    protected:
        vector<Node> data_;
        void shiftUp(int i);
        void shiftDown(int i);
        void swap(int i, int j);
        void erase(int i); // erase data_[i], not very useful?
        virtual bool is_top_of(const Node & first, const Node & second){
            return first.key_ < second.key_; // default is minimum heap
        }
};

class MaxHeap: public Heap {  
    public: 
        int max_key(){ return peek().key_; };   
    private:
        virtual bool is_top_of(const Node & first, const Node & second){
            return first.key_ > second.key_;
        };
};

class MinHeap: public Heap {  
    public: 
        int min_key(){ return peek().key_; };   
    private:
        virtual bool is_top_of(const Node & first, const Node & second){
            return first.key_ < second.key_;
        };
};


#endif
