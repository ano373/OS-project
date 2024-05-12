using namespace std;
#include <bits/stdc++.h>
#include <iostream>
#define NOT_FOUND -1


int findIndex(vector<int> vec, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (vec[i] == value) {
            return i; 
        }
    }
    return -1; 
}

void printAns(int rows,vector<vector<int>> ans,vector<int> list){

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
        
        int diff = duplicate(list, start, end) -  count;
        start -= diff;
        count += diff;
    }
    
    return start;
}

vector<int> LRU(vector<int>& frame,vector<int> list,int pos,int pageSize){
    int start = updateIndices(list,pos,pageSize); 
    int index = findIndex(frame,pageSize,list[start]);
    frame[index] = list[pos];
    return frame;
}

int main() {
    
    vector<int> list = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    vector<vector<int>> ans;
    int pageSize =3 ;
    vector<int> frame;
    int n=pageSize;

    for(int i=0;i<list.size();i++){
        if(i<pageSize)
            frame.push_back(list[i]);

        else if(findIndex(frame,pageSize,list[i])==NOT_FOUND){
            frame = LRU(frame,list,i,pageSize);
            n++;
        }
        ans.push_back(frame);

    }
    printAns(pageSize,ans,list);     
    cout<<"N: "<<n<<endl;
    return 0;
}
