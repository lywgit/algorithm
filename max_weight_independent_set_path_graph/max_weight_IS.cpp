#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_set>

using namespace std;

struct Vertex{
    Vertex(int i, int w){id = i; weight = w; };
    int id;
    int weight;
};

unordered_set<int> MaxWeightIndependentSet(vector<Vertex> & vertices){
    int num_vertices = vertices.size();
    vector<int> max_weights(num_vertices);  
    max_weights[0] = vertices[0].weight;
    max_weights[1] = vertices[1].weight > vertices[0].weight ? vertices[1].weight : vertices[0].weight;
    for (int i=2; i<num_vertices; i++){
        int case_include = vertices[i].weight + max_weights[i-2];
        int case_not = max_weights[i-1];
        max_weights[i] = case_include > case_not ? case_include : case_not;     
    }
    // reconstruction
    int i = num_vertices-1;
    unordered_set<int> max_weight_set;
    while (i>=2){
        if (vertices[i].weight + max_weights[i-2] > max_weights[i-1]){
            max_weight_set.insert(vertices[i].id);
            i-=2;
        }
        else{
            i-=1;
        }
    } 
    if (i == 0) 
        max_weight_set.insert(vertices[0].id);
    else {
        int j = vertices[0].weight > vertices[1].weight ? 0 : 1;
        max_weight_set.insert(vertices[j].id);
    }
    return max_weight_set;
}

int main(int argc, char* argv[]){

    if (argc<2){
        cerr <<"You should specify a file name."<<endl;
        return 1;
    }
    fstream file_stream (argv[1]);
    if (!file_stream){
        cerr <<"Error: File not opened."<<endl;
        return 1;
    }

    int num_vertices;
    file_stream >> num_vertices;
    cout << "number of vertices: " <<num_vertices <<endl;
    vector<Vertex> vertices;
    int w;
    int id = 1;
    while (file_stream >> w){
        vertices.push_back(Vertex(id++, w)); 
    }
    cout <<"vetices.size = "<<vertices.size()<<endl;

    unordered_set<int> max_weight_set = MaxWeightIndependentSet(vertices);
   
    int check_list[] =  {1, 2, 3, 4, 17, 117, 517, 997}; 
    for (int i=0; i<8; i++){
        cout<<check_list[i]<<"\t"<< max_weight_set.count(check_list[i]) << endl; 
    }
    return 0;
}


