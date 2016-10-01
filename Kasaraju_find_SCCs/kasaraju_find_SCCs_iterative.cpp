#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<deque>
#include<iterator>

using namespace std;

int g_t;
int g_s;
int g_counter;
vector<int> g_SCC_counts;
vector<int> g_finish;
vector<int> g_finish_sequence;
vector<int> g_leader;

void print(vector<vector<int> > const & graph) {
    for (int i=1; i< graph.size();i++){
        cout <<i<<": ";
        for (int j=0; j<graph[i].size(); j++){
            cout<<" "<<graph[i][j];
        }
        cout << endl;
    }
}

void DFS_Loop1(vector<vector<int> > g){
    vector<bool> is_explored(g.size()+1, false);
    deque<int> que;
    for (int i=g.size()-1; i>=1; i--){
        if (!is_explored[i]){
            //cout<<"searching que of " << i <<endl;
            is_explored[i] = true;
            que.push_back(i);
            while (!que.empty()){
                int current = que.back();
                if (!g[current].empty()) {
                    int next = g[current].back();
                    g[current].pop_back();
                    if (!is_explored[next]){
                        is_explored[next] = true;
                        //cout << "reaching "<<next<<endl;
                        que.push_back(next);
                    }
                }
                else{
                    int finished_node = que.back();
                    //cout <<"leaving "<<finished_node<<endl;
                    g_t++;
                    g_finish[finished_node] = g_t;
                    g_finish_sequence[g_t] = finished_node ;
                    que.pop_back();
                }
            }
        }      
    }
}

void DFS_Loop2(vector<vector<int> > g){
    vector<bool> is_explored(g.size()+1, false);
    deque<int> que;
    for (int ii=g.size()-1; ii>=1; ii--){
        int i = g_finish_sequence[ii];
        if (!is_explored[i]){
            //cout<<"searching que of " << i <<endl;
            que.push_back(i);
            is_explored[i] = true;
            g_s = i;
            g_counter = 0;
            while (!que.empty()){
                int current = que.back();
                if (!g[current].empty()) {
                    int next = g[current].back();
                    g[current].pop_back();
                    if (!is_explored[next]){
                        is_explored[next] = true;
                        //cout << "reaching "<<next<<endl;
                        que.push_back(next);
                    }
                }
                else{
                    int finished_node = que.back();
                    //cout <<"leaving "<<finished_node<<endl;
                    g_leader[finished_node] = g_s;
                    g_counter++;
                    que.pop_back();
                }
            }
            g_SCC_counts.push_back(g_counter);
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
    g_t = 0;
    g_s = -1;
    g_finish.resize(graph.size());
    g_finish_sequence.resize(graph.size());
    g_leader.resize(graph.size());
    

    cout<<"Loop 1 on reversed graph"<<endl;
    DFS_Loop1(reversed_graph);

    //cout<<"finish time for each node:"<<endl;
    //for (int i=1; i<graph.size(); i++)
        //cout<<i<<": "<<finish[i]<<endl;

    //cout<<"node in order of finishing"<<endl;
    //for (int i=1; i<graph.size(); i++)
        //cout<<i<<": "<<finish_sequence[i]<<endl;

    for (int i=1; i<graph.size(); i++)
        g_leader[i]=-1;
    cout<<"Loop 2 on graph"<<endl;
    DFS_Loop2(graph);

    //cout<<"leader of each node"<<endl;
    //for (int i=1; i<graph.size(); i++)
       // cout<<i<<": "<<g_leader[i]<<endl;
    
    cout <<"Total SCC groups: "<<g_SCC_counts.size()<<endl;
    cout <<"Resulting SCC size (the largest five)"<<endl;
    sort(g_SCC_counts.begin(), g_SCC_counts.end());

    vector<int>::reverse_iterator r_iter = g_SCC_counts.rbegin(); 
    int display_limit = 5;
    i = 0;
    while (r_iter != g_SCC_counts.rend() && i < display_limit){
        cout <<"SCC#"<< (i++)+1 <<" size: "<< *r_iter++ <<endl;
    }    


    return 0;
}


