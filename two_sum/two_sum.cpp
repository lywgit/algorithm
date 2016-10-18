#include<iostream>
#include<unordered_set>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;

int main(int argc, char* argv[]){
    
    
    if (argc < 2){
        cerr << "You need to specify a file name." << endl;
        return 1;
    }
    ifstream graph_file(argv[1]);
    if (!graph_file){
        cerr << "File '"<< argv[1] <<"' does not exist."<<endl;
        return 1;
    }
    
    vector<long> list;
    unordered_set<long> hashSet;
    long value;
    int count(0);
    while (graph_file >> value){
        list.push_back(value);
        hashSet.insert(value);
        count++;
    }
    int tCount(0);
    for (int t = -10000; t<=10000; t++){
        for (int i = 0; i< list.size(); i++){
            //cout << list[i]<<endl;
            if (hashSet.count(t-list[i]) != 0 && t-list[i] != list[i] ){
                tCount++;
                cout<<list[i]<<"+"<<t-list[i] <<" = " <<t <<"\t current count="<< tCount <<endl;
                break;
            }
        }
    }
    cout<<"total count:"<<tCount<<endl;
    

    return 0;

}

