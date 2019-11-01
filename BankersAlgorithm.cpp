#include <iostream>
#include <vector>
using namespace std;

//struct detailing state of process and its resource request status
struct resourceRequestStruct{
    //process or thread id, maximun number of resource to request, number of resources currently allocated
    int id, max, alloc;
};

class BankersAlgorithm{
    private:
    vector<resourceRequestStruct> resourceRequests; //all process/thread resource request
    int availableResources; //total number of resources available in the system
    vector<vector<int>> safe; //holds all safe sequences
    //recursive algorithm
    void recursiveBanker(vector<int> currentSeq, vector<resourceRequestStruct> remainingReq, int availableRes);


    public:
    //constructor
    BankersAlgorithm(int available) : availableResources(available) {}
    //initialize test case
    void initialize(vector<resourceRequestStruct> structs);
    //wrapper function for algorithm, calls recursive function and prints results
    void safeSequences();
    

};

int main(){
    BankersAlgorithm B(7);
    vector<resourceRequestStruct> testSample = { {1,2,1}, {2,6,1}, {3,6,0}, {4,6,2}, {5,3,1} };
    B.initialize(testSample);
    B.safeSequences();
}

void BankersAlgorithm:: recursiveBanker(vector<int> currentSeq, vector<resourceRequestStruct> remainingReq, int availableRes){
    if(remainingReq.empty()){
        safe.push_back(currentSeq);
    }

    else{

        vector<resourceRequestStruct> reqBuffer;
        vector<int> seqBuffer;

        for(int i = 0; i < remainingReq.size(); i++){
            int maxReq = remainingReq[i].max - remainingReq[i].alloc;
            if(maxReq <= availableRes){
                reqBuffer = remainingReq;
                seqBuffer = currentSeq;
                reqBuffer.erase(reqBuffer.begin() + i);
                seqBuffer.push_back(remainingReq[i].id);
                recursiveBanker(seqBuffer, reqBuffer, availableRes + remainingReq[i].alloc);
            }
        }
    }
}

void BankersAlgorithm::initialize(vector<resourceRequestStruct> structs){
    for(auto request : structs){
        resourceRequests.push_back(request);
        availableResources -= request.alloc;
    }
}

void BankersAlgorithm::safeSequences(){
    safe.clear();
    recursiveBanker({},resourceRequests,availableResources);
    for(auto seq : safe){
        for (auto i : seq){
            cout << i << " ";
        }
        cout << endl;
    }
}
