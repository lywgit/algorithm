#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>
#include<map>

using namespace std;


void dijkstra_shortest_path(set<int> nodes, vector<vector<int> > edges, int start, map<int,int> & distance){   
    int num_node = nodes.size();
    set<int> X, notX(nodes);
    set<int> edge_search_list;
    for (int i=0; i< edges.size(); i++){
        edge_search_list.insert(i);
    }
    // add start to X
    X.insert(start);
    notX.erase(notX.find(start));
    distance[start] = 0;
    // loop over edge
    int next = 0;
    while (!notX.empty() && next!=-1){
        int d_min = 99999999;
        int next = -1;
        //cout<<"break point A"<<endl;
        for (set<int>::iterator iter = edge_search_list.begin(); iter != edge_search_list.end(); iter++){
            int iedge = *iter;
            int tail(edges[iedge][0]), head(edges[iedge][1]), weight(edges[iedge][2]);
            //cout<<"break point B"<<endl;
            if (X.count(tail)==1 && notX.count(head)==1){
                //cout<<"break point C"<<endl;
                //cout<<"edge candidate: "<<tail<<"->"<<head<<" w"<<weight<<endl;
                int d = distance[tail] + weight;
                if (d < d_min){
                    //cout<<"break point D"<<endl;
                    d_min = d;
                    next = head;
                    //cout<<"new record node "<<head<<" distance "<<d_min<<endl;

                }
            }
        }
        //cout<<"break point E"<<endl;
        if (next !=-1){
            X.insert(next); 
            notX.erase(notX.find(next));
            distance[next] = d_min;
            cout<<"adding "<<next<<" to X, with distance "<<d_min<<"  ";
            cout<<"number of searched nodes: "<<X.size()<<" /"<<notX.size()<<endl;
        }
    }
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
    int iarr[] = {7,37,59,82,99,115,133,165,188,197};
    vector<int> outputs(iarr, iarr+10);
    for (int i=0; i<outputs.size(); i++){
        map<int,int>::iterator iter = distance.find(outputs[i]);
        int d = iter != distance.end() ? iter->second : 1000000;
        cout<<outputs[i] << ": "<<d<<endl;
    }
    for (int i=0; i<outputs.size(); i++){
        map<int,int>::iterator iter = distance.find(outputs[i]);
        int d = iter != distance.end() ? iter->second : 1000000;
        cout<<d<<",";
    }
    cout<<endl;

    return 0;

}
