#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

int t (0);
int s (-1);
int counter;
vector<int> SCC_counts;
vector<int> finish;
vector<int> finish_sequence;
vector<int> leader;
vector<int> groups;

void print(vector<vector<int> > const & graph) {
    for (int i=1; i< graph.size();i++){
        cout <<i<<": ";
        for (int j=0; j<graph[i].size(); j++){
            cout<<" "<<graph[i][j];
        }
        cout << endl;
    }
}

void DFS1(vector<vector<int> > const & g, int i, vector<bool> & is_explored){
    is_explored[i] = true;
    //cout<<"node "<<i<<" has leader "<<::leader[i]<<endl;
    for (int j=0; j<g[i].size(); j++){
        int head = g[i][j];
        if (!is_explored[head]){
            DFS1(g, head, is_explored);
        }
    }
    ::t++;
    ::finish[i] = ::t;
    ::finish_sequence[t] = i;
}

void DFS2(vector<vector<int> > const & g, int i, vector<bool> & is_explored){
    is_explored[i] = true;
    ::leader[i] = ::s;
    ::counter++; 
    //cout<<"node "<<i<<" has leader "<<::leader[i]<<endl;
    for (int j=0; j<g[i].size(); j++){
        int head = g[i][j];
        if (!is_explored[head]){
            DFS2(g, head, is_explored);
        }
    }
}
    
void DFS_Loop1(vector<vector<int> > const & g){
    vector<bool> is_explored(g.size(), false);
    for (int i=g.size()-1; i>=1; i--){
        if (!is_explored[i]){
            ::s = i;
            DFS1(g, i, is_explored);
        }
    }
}

void DFS_Loop2(vector<vector<int> > const & g){
    vector<bool> is_explored(g.size(), false);
    for (int i=g.size()-1; i>=1; i--){
        int node = finish_sequence[i];
        //cout<<"looping node: "<<node<<endl;
        if (!is_explored[node]){
            ::counter = 0;
            ::s = node;
            DFS2(g, node, is_explored);
            ::SCC_counts.push_back(counter);
        }
    }
}


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

    vector<vector<int> > graph, reversed_graph;// not uinsg index 0 of the array 
    int i;
    string line;
    while (getline(graph_file, line)){
        istringstream ss(line);
        int head, tail;
        while (ss >> head >> tail){
            //cout <<head <<" "<<tail<<endl;
            int required_size = max(head, tail)+1;
            if (graph.size() < required_size) 
                graph.resize(required_size);
            if (reversed_graph.size() < required_size) 
                reversed_graph.resize(required_size);
            graph[head].push_back(tail);
            reversed_graph[tail].push_back(head);
        } 
    }
    int num_nodes = graph.size()-1;
    cout <<"Graph read. There are " << num_nodes << " nodes in this directed graph." <<endl;
    //print(graph);
    //print(reversed_graph);
    ::t = 0;
    ::s = -1;
    ::finish.resize(graph.size());
    ::finish_sequence.resize(graph.size());
    ::leader.resize(graph.size());

    DFS_Loop1(reversed_graph);
    //cout<<"finish time for each node:"<<endl;
    for (int i=1; i<graph.size(); i++)
        //cout<<i<<": "<<finish[i]<<endl;

    //cout<<"node in order of finishing"<<endl;
    for (int i=1; i<graph.size(); i++)
        //cout<<i<<": "<<finish_sequence[i]<<endl;

    for (int i=1; i<graph.size(); i++)
        ::leader[i]=-1;
    DFS_Loop2(graph);

    //cout<<"leader of each node"<<endl;
    //for (int i=1; i<graph.size(); i++)
    //    cout<<i<<": "<<::leader[i]<<endl;
    
    cout <<"Total SCC groups: "<<SCC_counts.size()<<endl;
    cout <<"Resulting SCC size from small to large"<<endl;
    sort(SCC_counts.begin(), SCC_counts.end());
    for (int i=0; i< ::SCC_counts.size(); i++){
        cout <<i+1<<"  "<< SCC_counts[i]<<endl;
    }    

    return 0;
}


