#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <set>  
#include <vector>  
#include <map>  
#include <queue>  
#include <set>  
#include <algorithm>  
using namespace std;  
int a[1000001];  
int main()  
{  
    int t;  
    scanf("%d",&t);  
    while(t--){  
        int n,m;  
        scanf("%d %d",&n,&m);  
        a[1]=a[2]=1;  
        for(int i=3;;i++){  
            a[i]=(a[i-1]+a[i-2])%m;  
            if(a[i]==a[2]&&a[i-1]==a[1]){  
                printf("%d %d\n",n,i-2);  
                break;  
            }  
        }  
    }  
    return 0;  
}  

