#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
#include <iostream>  
#include <algorithm>  
#define maxn 105  
#define EPS 1e-7  
using namespace std;  
  
int n;  
char st[maxn];  
int stop,num[maxn],l[maxn],r[maxn],sta[maxn];  
struct No  
{  
    int sum;  
    long long co[maxn];  
    void init()  
    {  
        sum=0;  
        memset(co,0,sizeof(co));  
    }  
};  
void addEdge(int u,int v)  
{  
    if (!num[u]) l[u]=v;  
    else r[u]=v;  
    num[u]++;  
}  
void build()  
{  
    stop=0;  
    for (int i=0;st[i];i++)  
    {  
        if (st[i]=='x')  
        {  
            addEdge(sta[stop],i);  
            while (num[sta[stop]]==2&&sta[stop])  
            {  
                addEdge(sta[stop-1],sta[stop]);  
                --stop;  
            }  
        }  
        else sta[++stop]=i;  
    }  
}  
No dfs(int u)  
{  
    No res;  
    res.init();  
    if (st[u]=='x')  
    {  
        res.sum=1;  
        res.co[1]=1;  
        return res;  
    }  
    No L=dfs(l[u]);  
    No R=dfs(r[u]);  
    if (st[u]=='m')  
    {  
        for (int i=0;i<=max(L.sum,R.sum);i++)  
            res.co[i]=L.co[i]+R.co[i];  
        for (int i=0;i<=L.sum;i++)  
            for (int j=0;j<=R.sum;j++)  
                res.co[i+j]-=L.co[i]*R.co[j];  
    }  
    else  
    {  
        for (int i=0;i<=L.sum;i++)  
            for (int j=0;j<=R.sum;j++)  
                res.co[i+j]+=L.co[i]*R.co[j];  
    }  
    res.sum=L.sum+R.sum;  
    return res;  
}  
int main()  
{  
    //freopen("/home/christinass/code/in.txt","r",stdin);  
    int cas;  
    scanf("%d",&cas);  
    while (cas--)  
    {  
        scanf("%s",st);  
        memset(num,0,sizeof(num));  
        build();  
        No res=dfs(0);  
        long double ans=0;  
        for (int i=0;i<=res.sum;i++)  
            ans+=(long double)res.co[i]*i/(i+1);  
        cout << ans << endl;
    }  
    return 0;  
}  

