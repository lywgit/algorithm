/* unfinished work
 */

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include<map>
#include"Heap.h"

using namespace std;

void dijkstra_shortest_path(set<int> nodes, vector<vector<int> > edges, int start, map<int,int> & distance){   
    
    // initialize 
    Heap notX;


}



void replace_comma(string & str){
    size_t pos;
    while ( (pos = str.find(',')) != string::npos){
        str.replace(pos, 1, " ");
    }
}

int main(int argc, char *argv[]){

    if (argc < 2){
        cerr << "You need to specify a file name." << endl;
        return 1;
    }
    ifstream graph_file(argv[1]);
    if (!graph_file){
        cerr << "File '"<< argv[1] <<"' does not exist."<<endl;
        return 1;
    }

    // read edges
    vector<vector<int> > edges;
    set<int> nodes;
    int tail, head, weight;
    string line, temp_str;
    int count(0), limit(200);
    while (getline(graph_file, line) && count <limit){
        //cout <<"line content:"<< line<<endl;
        replace_comma(line);
        istringstream ss(line);
        ss >> tail; 
        nodes.insert(tail);
        while (ss >> head >> weight){
            //cout<<head<<" "<<weight<<endl;
            vector<int> e;
            e.push_back(tail);
            e.push_back(head);
            e.push_back(weight);
            edges.push_back(e);
            //cout<<head <<" "<<tail <<" "<<weight<<endl;
        } 
        count++;
    }

    map<int,int> distance;
    int start = 1;
    dijkstra_shortest_path(nodes, edges, start, distance);

    /*
    map<int,int> distance;
    int start = 1;
    dijkstra_shortest_path(nodes, edges, start, distance);
    int iarr[] = {7,37,59,82,99,115,133,165,188,197};
    vector<int> outputs(iarr, iarr+10);
    for (int i=0; i<outputs.size(); i++){
        map<int,int>::iterator iter = distance.find(outputs[i]);
        int d = iter != distance.end() ? iter->second : 1000000;
        cout<<outputs[i] << ": "<<d<<endl;
    }
    */

    



    return 0;

}
