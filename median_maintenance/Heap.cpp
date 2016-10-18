#include<iostream>
#include<string>
#include<vector>
#include"Heap.h"

using namespace std;
void Heap::insert(Node node){
    data_.push_back(node);
    shiftUp(data_.size()-1);
}

void Heap::swap(int i, int j){
    if (i != j ){
        Node temp = data_[i];
        data_[i] = data_[j];
        data_[j] = temp;
    }
}

void Heap::erase(int i){
    if (i > data_.size()-1){
        cerr<<"Error: attempt to erase node index out of range."<<endl;
        exit(1);
    }
    swap(i, data_.size()-1);
    data_.pop_back();
    shiftDown(i);
}

void Heap::shiftUp(int i){
    if (i==0) return;
    if (is_top_of(data_[i], data_[(i-1)/2]) ){
         swap(i, (i-1)/2);
         shiftUp((i-1)/2);
    }
}

void Heap::shiftDown(int i){
    int left = 2*i+1, right = 2*i+2;
    if (left > data_.size()-1) { // no child
        return;
    }
    else if (left == data_.size()-1){ // one child
        //if (data_[left].key_ < data_[i].key_){ 
        if (is_top_of(data_[left], data_[i])){ 
            swap(left, i);
        }
    }
    else{ // two child
        //int smaller = data_[left].key_ < data_[right].key_ ? left : right; 
        int smaller = is_top_of(data_[left], data_[right]) ? left : right; 
        //if (data_[smaller].key_ < data_[i].key_){
        if (is_top_of(data_[smaller], data_[i])){
            swap(smaller, i);
            shiftDown(smaller);
        }
    }
}

Node Heap::peek(){    
    if (data_.empty()){
        cerr<<"Error: attemp to peek while heap is empty."<<endl;
        exit(1);
    }
    return data_[0];
}

Node Heap::pop(){
    Node n = peek();
    swap(0, data_.size()-1);
    data_.pop_back();
    if (!data_.empty())
        shiftDown(0);
    return n;
}


// friend functions
void print_heap(const Heap & h){
    for (int i=0; i<h.data_.size(); i++){
        cout << i<<": "<<h.data_[i].key_<<endl; 
    }
}

