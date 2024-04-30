using namespace std;
#include <bits/stdc++.h>
#include <iostream>


int duplicate(vector<int> list, int start, int end){
    vector<int> newlist(list.begin() + start, list.begin() + end + 1);

    sort(newlist.begin(),newlist.end());
    int count =0;
    
    for(int i=0;i<newlist.size()-1;i++){
        if(newlist[i]==newlist[i+1]){
            count++;
        }
    }
    return count;

}

int updateIndices(vector<int> list, int pos, int pageSize) {
    int count = 0;
    int end = pos - 1;
    int start = end - pageSize + 1;
    
    
    while (duplicate(list, start, end) - count != 0) {
        
        int duplicates = duplicate(list, start, end) -  count;
        start -= duplicates;
        count += duplicates;
    }
    
    return start;
}

int findIndex(vector<int> vec, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (vec[i] == value) {
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

vector<int> LRU(vector<int>& curr,vector<int> list,int pos,int pageSize){
    int start = updateIndices(list,pos,pageSize); 
    
    int index = findIndex(curr,pageSize,list[start]);
    cout<<"start: "<<start<<endl;
     curr[index] = list[pos];
    return curr;
}

int main() {
    
    vector<int> list = {7,0,1,2,0,3,0,4,2,3,5,3,2,1,2,8,1,7,9,1};
    vector<vector<int>> ans;
    int pageSize =4 ;
    vector<int> curr;

    for(int i=0;i<list.size();i++){
        if(i<pageSize)
            curr.push_back(list[i]);

        else if(findIndex(curr,pageSize,list[i])==-1)
            curr = LRU(curr,list,i,pageSize);
        ans.push_back(curr);
    }
    printAns(pageSize,ans,list);     
    return 0;
}
