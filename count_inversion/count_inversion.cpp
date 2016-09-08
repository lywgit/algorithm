#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int>::size_type sort_and_count_split_inversions(vector<int> & vec, vector<int> & left_half, vector<int> right_half){
    vector<int>::iterator iter = vec.begin(), iter1 = left_half.begin(), iter2 = right_half.begin();
    vector<int>::size_type count(0);
    while (iter != vec.end()){
        if (iter1 == left_half.end()) 
            *iter++ = *iter2++;
        else if (iter2 == right_half.end()) 
            *iter++ = *iter1++;
        else { 
            if (*iter1 > *iter2)  count += (left_half.end() - iter1);
            *iter++ = *iter1<*iter2 ? *iter1++ : *iter2++;
        }
    }
    return count;
}

vector<int>::size_type sort_and_count_inversions(vector<int> & vec){
    vector<int>::size_type size = vec.size();
    if (vec.size() == 1) return 0;

    vector<int>::size_type left_count, right_count, split_count;
    vector<int> left_half(vec.begin(), vec.begin()+size/2); 
    left_count = sort_and_count_inversions(left_half);

    vector<int> right_half(vec.begin()+size/2, vec.end());
    right_count = sort_and_count_inversions(right_half);

    split_count = sort_and_count_split_inversions(vec, left_half, right_half);

    return left_count + right_count + split_count;
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
        //cout << ivec.back()<<endl;
    }
    vector<int>::size_type num_inversions = sort_and_count_inversions(ivec);

    cout << "inversion count: " << num_inversions << endl;

    return 0;
}

