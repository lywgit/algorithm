#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

long comparison_count = 0;       
enum PivotMethod {First, Final, MedianOfThree } method;

inline void swap(int & a, int & b){
    int temp = a; a = b; b = temp; 
}


void QuickSort(vector<int> & array, vector<int>::size_type ibeg, vector<int>::size_type iend){
    vector<int>::size_type size = iend - ibeg;
    if (size <=1) return;   
    if (::method == Final) 
        swap(array[iend-1], array[ibeg]); 
    else if (::method == MedianOfThree){
        vector<int>::size_type imid = ibeg + (size - 1)/2 ;
        if ((array[imid] - array[ibeg]) * (array[imid] - array[iend-1]) < 0)
            swap(array[imid], array[ibeg]);
        else if ((array[iend-1]-array[ibeg]) * (array[iend-1] - array[imid]) < 0)
            swap(array[iend-1], array[ibeg]);
    }

    int pivot = array[ibeg];
    vector<int>::size_type i, iboundary;
    i = ibeg+1;
    iboundary = ibeg+1;
    for ( ; i<iend; i++){
        if (array[i] < pivot){
            swap(array[i], array[iboundary]);
            iboundary++;
        }
    }
    swap(array[ibeg], array[iboundary-1]);

    QuickSort(array, ibeg, iboundary-1);
    QuickSort(array, iboundary, iend);    
    ::comparison_count += (iend - ibeg-1);
}



int main(int argc, char* argv []){
    
    if (argc <2) {
        cerr << "You need to specify the file name." << endl;
        return 1;
    }

    ifstream array_file(argv[1]);
    if (!array_file) {
        cerr << "File '"<< argv[1] << "' does not exist." << endl;
        return 1;
    }

    vector<int> ivec, ivec_original_copy;
    int ival;
    while (array_file >> ival){
        ivec.push_back(ival);
        ivec_original_copy.push_back(ival);
    }
    

    method = First;
    ivec = ivec_original_copy;
    comparison_count = 0;
    QuickSort(ivec, 0, ivec.size());
    cout<< "Method: First" << endl
        << "comparison count: "<< comparison_count << endl;

    method = Final;
    ivec = ivec_original_copy;
    comparison_count = 0;
    QuickSort(ivec, 0, ivec.size());
    cout<< "Method: Final" << endl
        <<"comparison count: "<< comparison_count << endl;

    method = MedianOfThree;
    ivec = ivec_original_copy;
    comparison_count = 0;
    QuickSort(ivec, 0, ivec.size());
    cout<< "Method: Median of three" << endl
        <<"comparison count: "<< comparison_count << endl;
    
    for (int i=0; i<ivec.size()-1; i++){
        if (ivec[i] > ivec[i+1] )
            cout <<ivec[i]<<" "<<ivec[i+1]<<endl;
    }

    return 0;
}


