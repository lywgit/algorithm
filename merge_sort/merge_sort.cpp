#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void MergeSort(vector<int> & vec){
    vector<int>::size_type size = vec.size();
    if (vec.size() == 1) return;

    vector<int> left_half(vec.begin(), vec.begin()+size/2); 
    MergeSort(left_half);

    vector<int> right_half(vec.begin()+size/2, vec.end());
    MergeSort(right_half);

    vector<int>::iterator iter = vec.begin(), iter1 = left_half.begin(), iter2 = right_half.begin();
    while (iter != vec.end()){
        if (iter1 == left_half.end()) 
            *iter++ = *iter2++;
        else if (iter2 == right_half.end()) 
            *iter++ = *iter1++;
        else  
            *iter++ = *iter1<*iter2 ? *iter1++ : *iter2++;
    }
    return;
}


int main (int argc, char *argv[]){
    
    if (argc <2) {
        cerr << "You need to specify the file name." << endl;
        return 1;
    }

    ifstream array_file(argv[1]);
    if (!array_file) {
        cerr << "File '"<< argv[1] << "' does not exist." << endl;
        return 1;
    }
    vector<int> ivec;
    int i;
    while (array_file >> i){
        ivec.push_back(i);
        cout << ivec.back()<<endl;
    }
    MergeSort(ivec);

    vector<int>::iterator iter = ivec.begin();
    while (iter != ivec.end()){
        cout << *iter++<<endl;
    }
    


    return 0;
}

