
using namespace std;
#include <bits/stdc++.h>
#include <iostream>
#define MAX_VALUE 9999
#define NOT_FOUND -1



int findIndex(vector<int> arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value)
            return i; 
        
    }
    return NOT_FOUND; 
}

bool AllNotFound(int arr[], int size){
    int  count = 0;
    for (int i = 0; i < size; ++i){
        if(arr[i]==NOT_FOUND)
            count++;
    }
    

    if(count==size) 
        return true;
    else return false;     


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

vector<int> LRU(vector<int>& curr,vector<int> list,int pos,int pageSize){
    
    int count =0;
    int end = pos-1;
    int start = end-pageSize +1;
    while(duplicate(list,start,end)-count!=0){
        start -= duplicate(list,start,end);
        count += duplicate(list,start,end);            
    } 
    
    int index = findIndex(curr,pageSize,list[start]);
    curr[index] = list[pos];
    return curr;
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


int main() {

    vector<int> list = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1,4,3};
    int pageSize = 3;
    vector<int> curr;
    vector<vector<int>> ans;

    for(int i=0;i<list.size();i++){

        if(i<pageSize){
            curr.push_back(list[i]);


        //optimal
        }else if(findIndex(curr,pageSize,list[i])==-1){
            int startidx = i+1;
            int futureidx[pageSize];

            vector<int> remaininglist(list.begin() + startidx, list.end());
            for(int j=0;j<pageSize;j++)
                futureidx[j] = findIndex(remaininglist,remaininglist.size(),curr[j]);

            //optimal
            if(!AllNotFound(futureidx,pageSize)){
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
                curr[farestidx] = list[i];
            
                //LRU (all of them wasnt found in the remininglist [all have "NOT_FOUND"])
             }else{
                   curr =  LRU(curr,list,i,pageSize);
             }
        }
         ans.push_back(curr);
    }
    printAns(pageSize,ans,list);




    return 0;
}