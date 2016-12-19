#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm> // for sort
#include<unordered_set>
#include<bitset>
#include<sstream>

using namespace std;

// currently 24 is hard-codded

struct Node{
    bitset<24> label;
    int bit_sum;
};

struct Edge{
    Edge(int n1, int n2){
        node1=n1; node2=n2; 
    };
    int node1;
    int node2;
};

int distance(Node e1, Node e2){
    return 24-(e1.label ^ ~e2.label).count();
}

Node FormNode(string l){
    Node n;
    stringstream ss(l);
    for (int i=0; i<24; i++){
        bool temp;
        ss >> temp;
        n.label[i] = temp;
    }
    n.bit_sum = n.label.count();
    return n;
}

void KClustering(vector<Node> nodes, vector<Edge> edges, int & k){
    cout <<"KClustering"<<endl;
    int num_nodes = nodes.size();
    vector<int> parents;
    unordered_set<int> cluster_leaders;
    
    for (int i=0; i<num_nodes;i++) {
        parents.push_back(i);
        cluster_leaders.insert(i);
    }
    
    vector<Edge>::iterator iter = edges.begin();
    while (iter != edges.end()){
        int s1 = parents[iter->node1];
        int s2 = parents[iter->node2];
        if (s1 != s2){
            for (int i=0; i<num_nodes;i++)
                if (parents[i] == s2) parents[i] = s1;
            cluster_leaders.erase(s2);
        }
        iter++;
    }
    k = cluster_leaders.size();
}


int main(int argc, char* argv []){

    if (argc<2){
        cerr <<"You should specify a file name."<<endl;
        return 1;
    }
    ifstream file_stream (argv[1]);
    if (!file_stream){
        cerr <<"Error: File not opened."<<endl;
        return 1;
    }
    int num_node;
    int num_bit;
    file_stream >> num_node >> num_bit;
    cout<< "number of node: "<<num_node<<endl;
    vector<Node> nodes;
    string line;
    getline(file_stream, line);// to discard the first line
    while (getline(file_stream, line)){
        Node n = FormNode(line);   
        nodes.push_back(n);
    }
    cout << "nodes.size()="<<nodes.size()<<endl;
    vector<Edge> distance0;
    vector<Edge> distance1;
    vector<Edge> distance2;

    for (int i=0; i<num_node; i++){
        for (int j=i+1; j<num_node; j++){
           int d = distance(nodes[i],nodes[j]);
           if (d == 0) {
               distance0.push_back(Edge(i,j));
               //cout <<"d=0: "<<nodes[i].label<<" "<<nodes[j].label<<endl;
           }else if (d == 1) {
               distance1.push_back(Edge(i,j));
               //cout <<"d=1: "<<nodes[i].label<<" "<<nodes[j].label<<endl;
           }else if (d == 2) {
               distance2.push_back(Edge(i,j));
               //cout <<"d=2: "<<nodes[i].label<<" "<<nodes[j].label<<endl;
           }
        }
        if ((i+1)%5000==0)
            cout<<i+1<<endl;
    }
    vector<Edge> edges;
    edges.insert(edges.end(), distance0.begin(), distance0.end());
    edges.insert(edges.end(), distance1.begin(), distance1.end());
    edges.insert(edges.end(), distance2.begin(), distance2.end());

    int k; 
    KClustering(nodes, edges, k);
    cout <<"Number of clusters (after mergeing all edges with distance <= 2) : "<< k <<endl;

    return 0;
}



