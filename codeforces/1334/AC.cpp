#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
 
typedef long long ll;
const int N=500005;
const ll INF=1LL<<60;
 
int sz=1;
ll t[N<<2];
 
void add(int k,ll x)
{
	k=k+sz-1;
	t[k]+=x;
	k>>=1;
	
	while(k)
	{
		t[k]=t[k<<1]+t[k<<1|1];
		k>>=1;
	}
}
 
ll query(int k,int l,int r,int a,int b)
{
	if(a>r || b<l)
		return 0LL;
	if(a>=l && b<=r)
		return t[k];
	
	int mid=(a+b)>>1;
	return query(k<<1,l,r,a,mid)+query(k<<1|1,l,r,mid+1,b);
}
 
ll query(int l,int r)
{
	if(l>r)
		return 0LL;
	return query(1,l,r,1,sz);
}
 
int n,m;
int a[N],b[N];
ll P[N];
 
vector<int> pos[N];
ll cost[N];
 
ll calc(int last,int cur,int p,int j)
{
	return cost[pos[last][p]]+query(pos[last][p]+1,pos[cur][j]-1);
}
 
int main()
{
	scanf("%d",&n);
	while(sz<n+1)
		sz<<=1;
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		pos[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&P[i]);
		add(i,P[i]);
	}
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	
	b[++m]=n+1;
	pos[n+1].push_back(n+1);
	
	for(int i=1;i<=n+1;i++)
		cost[i]=INF;
	cost[0]=0LL;
	pos[0].push_back(0);
	
	for(int i=1;i<=m;i++)
	{
		int cur=b[i],last=b[i-1];
		for(int j=(i>1?b[i-2]:0)+1;j<=last;j++)
			for(int k=0;k<pos[j].size();k++)
				if(P[pos[j][k]]>0)
				{
					add(pos[j][k],-P[pos[j][k]]);
//					printf("p[%d]-=%lld\n",pos[j][k],P[pos[j][k]]);
				}
		
		int p=0,bp=-1;
		for(int j=0;j<pos[cur].size();j++)
		{
			while(p<pos[last].size() && pos[last][p]<pos[cur][j])
			{
				if(cost[pos[last][p]]==INF)
				{
					p++;
					continue;
				}
				
				if(bp<0 || calc(last,cur,p,j)<calc(last,cur,bp,j))
					bp=p;
				p++;
			}
			if(bp!=-1)
				cost[pos[cur][j]]=calc(last,cur,bp,j);
//			printf("cost[%d]=%lld\n",pos[cur][j],cost[cur[pos][j]]);
		}
	}
	
	if(cost[n+1]==INF)
		printf("NO\n");
	else
		printf("YES\n%lld\n",cost[n+1]);
	return 0;
}
