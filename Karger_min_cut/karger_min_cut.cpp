#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<random>

using namespace std;


int RandomInt(int n){
    return rand() % n;
}

void CleanUp(vector<int> & vec){
    int self_id = vec[0];
    vector<int>::iterator iter = vec.begin()+1;
    while (iter != vec.end()){
        if (*iter == self_id) {
            vec.erase(iter);
            iter = vec.begin()+1;
        }
        else{
            iter++;
        }
    }
}

void Replace(vector<int> & vec, int old_id, int new_id){
    vector<int>::iterator iter = vec.begin();
    for (vector<int>::iterator iter = vec.begin()+1; iter != vec.end(); iter++){
        if (*iter == old_id) *iter =  new_id;
    }
}

void ContractNodes(vector<vector<int> > & graph, int from_node, int to_node){

    //-- copy and add from from_node to to_node
    graph[to_node].insert(graph[to_node].end(), graph[from_node].begin()+1, graph[from_node].end());

    //-- go through nodes connected to from_node and replace their record of from_node id by to_node's
    for (vector<int>::iterator iter = graph[from_node].begin()+1; iter != graph[from_node].end(); iter++){
        int i = 0;
        while (graph[i][0] != *iter) i++;
        Replace(graph[i], graph[from_node][0], graph[to_node][0]);
    }
    //-- clean up self loop in the to_node
    CleanUp(graph[to_node]); 

    //--erase the from node
    graph.erase(graph.begin() + from_node);
    
}


int MinCut(vector<vector<int> > graph){
    if (graph.size() == 2){
        return graph[0].size()-1;
    }
    while (graph.size() > 2){
        int from_node = RandomInt(graph.size());
        int to_node_id = RandomInt(graph[from_node].size()-1) + 1;// will have problem when there's isolated node 
        int to_node = 0;
        while (graph[to_node][0] != graph[from_node][to_node_id]) to_node++;
        ContractNodes(graph, from_node, to_node);
    }
    cout << "final elements:" << graph[0][0]<<" and " << graph[1][0]<<endl;
    
    return graph[0].size()-1;
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

    // read map
    vector<vector<int> > graph;

    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    int i;
    string line;
    while (getline(graph_file, line)){
        istringstream ss(line);
        vector<int> nodes;
        while (ss >> i){
            nodes.push_back(i); 
        } 
        graph.push_back(nodes);
    }

    int min_cut = graph.size()*graph.size();
    int min_cut_count = 0;
    int limit = graph.size()*graph.size()*log(graph.size());
    int trial = 0;
    while (trial++ < limit){
        int result = MinCut(graph);
        min_cut = min_cut < result ? min_cut : result;
        min_cut_count = min_cut < result ? 1 : min_cut_count+1;
        cout <<"trial #"<<trial<<"/"<< limit <<"  result ="<< result <<"  record: "<<min_cut<<endl;
    }
    cout<< "The node number of this map: " << graph.size() << endl;
    cout<< "Final min_cut: "<<min_cut<< "  (occurs "<<min_cut_count << " times in the trial)" << endl;

    return 0;
}

