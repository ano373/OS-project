using namespace std;
#include <bits/stdc++.h>
#include <iostream>
#define NOT_FOUND -1

int findIndex(vector<int>& arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value)
            return i; 
        
    }
    return NOT_FOUND; 
}

void printAns(int pageSize,vector<vector<int>>& ans,vector<int> list){

    for(int i=0;i<list.size();i++)
        cout<<list[i]<<"  ";
    cout<<endl;
    cout<<"............................................................"<<endl;
    int row =0;
    while(pageSize--){
        for(int i=0;i<ans.size();i++)
            cout<<ans[i][row]<<"| ";
    cout<<endl;
    row++;
    }


}

bool AllSameFreq(unordered_map<int, int>& map) {
    const int& firstValue = map.begin()->second;
    for (const auto& pair : map) {
        if (pair.second != firstValue) 
            return false;
    }
    return true;
}

int HighestFreqValue(unordered_map<int, int>& map){
    pair<int, int> maxPair;
    int maxFreq = 0;

    for (const auto& pair : map) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            maxPair = pair;
        }
    }

    return maxPair.first;

}

unordered_map<int, int> trackFreq(vector<int>& list, int index, vector<int>& curr) {
    unordered_map<int, int> map;
    for (int val : curr) {
        int freq = 0;
        for (int i = 0; i <= index; ++i) {
            if (list[i] == val)
                freq++;
        }
        map[val] = freq;
        
    }
    return map;
}

vector<int> MRU(vector<int> curr,vector<int> list,int pos,int pageSize){
    int index = findIndex(curr,pageSize,list[pos-1]);
    curr[index] = list[pos];
    return curr;

}

vector<int> MFU(vector<int>& curr,vector<int>& list,int pos, int pageSize){
    unordered_map<int, int> map = trackFreq(list,pos-1,curr);
    if(!AllSameFreq(map)){
        int value = HighestFreqValue(map);
        int index = findIndex(curr,pageSize,value);
        curr[index] =  list[pos];
    }
    else curr = MRU(curr,list,pos,pageSize);

    
    return curr;
}



int main(){
    vector<int> list = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int pageSize = 3;
    vector<int> curr;
    vector<vector<int>> ans;
    int n=pageSize;

    for(int i=0;i<list.size();i++){
        if(i<pageSize){
            curr.push_back(list[i]);

        }else if(findIndex(curr,pageSize,list[i])==NOT_FOUND){
            curr = MFU(curr,list,i,pageSize);
            n++;
            }
        ans.push_back(curr);
    }
    printAns(pageSize,ans,list);
    cout<<"N: "<<n<<endl;



    return 0;
}