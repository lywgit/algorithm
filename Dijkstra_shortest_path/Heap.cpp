#include<iostream>
#include<string>
#include<vector>
#include"Heap.h"

using namespace std;
/*
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
*/
void Heap::insert(Node node){
    data_.push_back(node);
    shift_up(data_.size()-1);
}

void Heap::swap(int i, int j){
    if (i != j ){
        Node temp = data_[i];
        data_[i] = data_[j];
        data_[j] = temp;
    }
}

void Heap::shift_up(int i){
    if (i==0) return;
    if (data_[i].key_ < data_[(i-1)/2].key_){
         swap(i, (i-1)/2);
         shift_up((i-1)/2);
    }
}

void Heap::shift_down(int i){
    int left = 2*i+1, right = 2*i+2;
    if (left > data_.size()-1) {
        return;
    }
    else if (left == data_.size()-1){
        if (data_[left].key_ < data_[i].key_){ 
            swap(left, i);
        }
    }
    else{
        int smaller = data_[left].key_ < data_[right].key_ ? left : right; 
        if (data_[smaller].key_ < data_[i].key_){
            swap(smaller, i);
            shift_down(smaller);
        }
    }
}

Node Heap::pop_min(){
    if (data_.empty()){
        cerr<<"Error: attemp to pop while heap is empty."<<endl;
        exit(1);
    }
    Node n = data_[0];
    swap(0, data_.size()-1);
    data_.pop_back();
    if (!data_.empty())
        shift_down(0);
    return n;
}
void print(Heap h){
    for (int i=0; i<h.data_.size(); i++){
        cout << i<<": "<<h.data_[i].key_<<endl; 
    }
}

/*
int main(){
    Heap h;
    for (int i=100; i>90; i--){
        h.insert(Node (1, i));
    }
    print(h);
    while (!h.empty()){
        Node n = h.pop_min();
        cout<< "popped: "<<n.key_<<endl;
        //print(h);
    }





    return 0;
}

*/
