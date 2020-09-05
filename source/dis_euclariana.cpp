#include<iostream>
#include <bits/stdc++.h>
using namespace std;
int main(){
    //cout<<"hola "<<endl;
    int n,nt;
    cin>>n>>nt;
    vector<vector<int>>vec(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<nt;j++){
            vec[i].push_back(1 + rand() % n);
        }

    }
    auto inicio=chrono::system_clock::now();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int c=0;
            for(int k=0;k<nt;k++){
                c=c+ pow((vec[i][k]-vec[j][k]),2);
            }
            c=sqrt(c);
        }
    }
    auto fin=chrono::system_clock::now();
    auto time=std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);
    cout<<time.count()<<"  ms"<<endl;
    return 0;
}