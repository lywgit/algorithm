#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

struct Job{
    double key;
    int weight, length;
};

void swap(Job & a, Job & b){
    Job tmp = b;
    b = a;
    a = tmp;
}

void SortByKeyWeight(vector<Job> & vec){
    // merge sort
    vector<Job>::size_type size = vec.size();
    if (size == 1) return;
    vector<Job> left_half(vec.begin(), vec.begin()+size/2 );
    SortByKeyWeight(left_half);
    vector<Job> right_half(vec.begin()+size/2, vec.end() );
    SortByKeyWeight(right_half);

    vector<Job>::iterator iter = vec.begin(), l_iter = left_half.begin(), r_iter = right_half.begin();
    while (iter != vec.end()){
        if (l_iter == left_half.end())
            *iter++ = *r_iter++;
        else if (r_iter == right_half.end())
            *iter++ = *l_iter++;
        else{
            if (l_iter->key == r_iter->key)
                *iter++ = l_iter->weight > r_iter->weight ? *l_iter++ : *r_iter++;
            else
                *iter++ = l_iter->key > r_iter->key ? *l_iter++ : *r_iter++;
        } 
    }
    return;
}

long WeightedCompletionTime(vector<Job> & vec){
    vector<Job>::iterator iter = vec.begin();
    long completion_time = 0;
    long weighted_sum = 0;
    while (iter != vec.end()){
        completion_time += iter->length;
        weighted_sum += iter->weight * completion_time;
        iter++;
    }
    return weighted_sum;
}

int main(int argc, char* argv []){

    if (argc < 2) {
        cerr << "You need to specify a file name"<< endl;
        return 1;
    }
    ifstream file_stream(argv[1]);
    if (!file_stream){
        cerr << "File "<<argv[1] << " not opened."<<endl;
        return 1;
    }

    int num_jobs; 
    file_stream >> num_jobs;
    vector<Job> jobs;
    jobs.resize(num_jobs);
    int i = 0;
    while (i < num_jobs){
        int w, l;
        file_stream >> w >> l;
        jobs[i].weight = w;
        jobs[i].length = l;
        jobs[i].key = w-l; 
        i++;
    }
    SortByKeyWeight(jobs);    
    long ans1 = WeightedCompletionTime(jobs);
    cout <<"Weighted Completion time (with key = weight - length): " << ans1 <<endl;

    // re-assign key = weight/length
    for (int i=0; i<jobs.size(); i++){
        jobs[i].key = double(jobs[i].weight) / double(jobs[i].length);
    }
    SortByKeyWeight(jobs);    
    long ans2 = WeightedCompletionTime(jobs);
    cout <<"Weighted Completion time (with key = weight / length): " << ans2 <<endl;
    return 0;
}   


