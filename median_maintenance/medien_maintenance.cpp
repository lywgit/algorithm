#include<iostream>
#include<fstream>
#include"Heap.h"
using namespace std;




int main(int argc, char * argv []){

    if (argc < 2){
        cerr << "You need to specify a file name." << endl;
        return 1;
    }
    ifstream stream_file(argv[1]);
    if (!stream_file){
        cerr << "File '"<< argv[1] <<"' does not exist."<<endl;
        return 1;
    }
    MaxHeap smaller_half; 
    MinHeap larger_half;
    int current_key, median(0);
    long median_sum(0);
    int k(0);
    // maintain median at the max value in maximum heap
    // so smaller_half.size() = larger_half.size() or larger_half.size()+1
    // explicitly do the first insert
    stream_file >> current_key;
    k = 1;
    smaller_half.insert(Node(k, current_key)); 
    median_sum += current_key;
    while (stream_file >> current_key){
        k++;
        if (current_key > smaller_half.max_key()){
            larger_half.insert( Node(k, current_key));
            if (larger_half.size() > smaller_half.size()){
                smaller_half.insert(larger_half.pop());
            }
        } 
        else {
            smaller_half.insert( Node(k, current_key));
            if (smaller_half.size() > larger_half.size()+1){
                larger_half.insert(smaller_half.pop());
            }
        }

        median = smaller_half.max_key();
        median_sum += median;
        cout << k <<" median="<<median<<"\tmedian sum="<<median_sum<<endl;
        
    }
    cout<< "Size of the two heaps: " << smaller_half.size()<<" "<<larger_half.size()<<endl
        << "Fianl result: "<<median_sum<<endl
        << "Mod 10000: " <<median_sum % 10000<<endl;
    

    return 0;
}
