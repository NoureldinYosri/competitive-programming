



#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
int main(){
ll t;cin>>t;
while(t--){
    ll n;
    cin>>n;
    ll arr[n];
    ll codd=0,ceven=0;

    for(ll i=0;i<n;i++){
        cin>>arr[i];
        if(arr[i]&1){
            codd++;
        }
        else{
            ceven++;
        }
    }

    if(codd==n){
        cout<<0<<endl;
    }

    else if(codd>0){
        cout<<ceven<<endl;
    }

    else{
        ll newArr[n];
        ll mini=INT_MAX;
        ll count=0;

        for(ll i=0;i<n;i++){
            count=0;
            while(arr[i]%2!=1){
                arr[i]/=2;
                count++;
                
            }
            mini=min(mini,count);
            
        }
        cout<<mini+n-1<<endl;
    }
}
    return 0;
}