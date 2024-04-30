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

vector<int> MRU(vector<int> curr,vector<int> list,int pos,int pageSize){
    int index = findIndex(curr,pageSize,list[pos-1]);
    curr[index] = list[pos];
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
            curr = MRU(curr,list,i,pageSize);
            n++;
            }
        ans.push_back(curr);
    }
    printAns(pageSize,ans,list);
    cout<<"N: "<<n<<endl;

}