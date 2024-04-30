using namespace std;
#include <iostream>
#include <bits/stdc++.h>

int findIndex(vector<int> arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value) {
            return i; 
        }
    }
    return -1; 
}

void printAns(int pageSize,vector<vector<int>> ans,vector<int> list){

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

vector<int> Fifo(queue<int>& que,vector<int>& curr,vector<int> list, int pageSize, int pos){
    int fault = que.front();
    que.pop();
    int index = findIndex(curr,pageSize,fault);
    curr[index] = list[pos];
    que.push(list[pos]);
    return curr;
}

int main() {
    
    vector<int> list = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int pageSize = 3;
    vector<int> curr;
    vector<vector<int>> ans;
    queue<int> que;
    int n= pageSize;
       
    for(int i=0;i<list.size();i++){
        if(que.size()<pageSize){
            curr.push_back(list[i]);
            que.push(list[i]);
        }    
        else if(findIndex(curr,pageSize,list[i])==-1){
                curr = Fifo(que,curr,list,pageSize,i); 
                n++;    
        }
        ans.push_back(curr);     
    }
    printAns(pageSize,ans,list);
    cout<<"N: "<<n<<endl;
    
    
    return 0;
}
