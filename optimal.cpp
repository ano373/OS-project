
using namespace std;
#include <bits/stdc++.h>
#include <iostream>
#define NOT_FOUND -1



int findIndex(vector<int> arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value)
            return i; 
        
    }
    return NOT_FOUND; 
}

void printAns(int rows,vector<vector<int>>& ans,vector<int> list){

    for(int i=0;i<list.size();i++)
        cout<<list[i]<<"  ";
    cout<<endl;
    cout<<"............................................................"<<endl;
    int row =0;
    while(rows--){
        for(int i=0;i<ans.size();i++)
            cout<<ans[i][row]<<"| ";
    cout<<endl;
    row++;
    }


}

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

vector<int> LRU(vector<int>& curr,vector<int> list,int pos,int pageSize){
    int start = updateIndices(list,pos,pageSize); 
    
    int index = findIndex(curr,pageSize,list[start]);
     curr[index] = list[pos];
    return curr;
}

bool AllNotFound(vector<int> arr, int size){
    int  count = 0;
    for (int i = 0; i < size; ++i){
        if(arr[i]==NOT_FOUND)
            count++;
    }
    if(count==size) 
        return true;
    else return false;     
}

int FindFault(vector<int> futureidx,int pageSize){
    int value = futureidx[0];
    int farestidx = 0; 
    for(int j=0;j<pageSize;j++){
        if(futureidx[j]==NOT_FOUND){
                farestidx = j;
                break;
            }
        if(futureidx[j]>value){
            value = futureidx[j];
            farestidx = j;
        } 

    }
    return farestidx;
}

vector<int> findFuture(vector<int>& list, int pos, int pageSize,vector<int>& curr) {
    int startidx = pos + 1;
    vector<int> futureidx(pageSize);

    vector<int> remaininglist(list.begin() + startidx, list.end());
    for (int j = 0; j < pageSize; j++)
        futureidx[j] = findIndex(remaininglist, remaininglist.size(), curr[j]);

    return futureidx;
}

vector<int> optimal(vector<int>& curr,vector<int> list,int pageSize,int pos){
    vector<int> futureidx(pageSize,NOT_FOUND);
    futureidx = findFuture(list,pos,pageSize,curr);

    //optimal
    if(!AllNotFound(futureidx,pageSize)){
        int index = FindFault(futureidx,pageSize);
        curr[index] = list[pos];
    } 
     else
         curr =  LRU(curr,list,pos,pageSize);
    return curr;    
}

int main() {

    vector<int> list = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int pageSize = 3;
    vector<int> curr;
    vector<vector<int>> ans;
     int n=pageSize;
    for(int i=0;i<list.size();i++){
        if(i<pageSize){
            curr.push_back(list[i]);

        }else if(findIndex(curr,pageSize,list[i])==NOT_FOUND){
            curr = optimal(curr,list,pageSize,i);
            n++;
        }
        ans.push_back(curr);
    }
    printAns(pageSize,ans,list);
    cout<<"N: "<<n<<endl;




    return 0;
}
