#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

const int MAX = 1000'010;
int f[MAX],n,m;
int g[MAX],h[MAX];
vi rf[MAX];

int main(){
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",f + i);
		rf[f[i]].pb(i);
	}
	m = 0;
	range(i,1,n) if(!rf[i].empty()){
		m++;		
		for(int x : rf[i])
			g[x] = m;
		h[m] = i;
	}
	range(i,1,m) if(g[h[i]] != i){
		puts("-1");
		return 0;
	}
	range(i,1,n) if(h[g[i]] != f[i]){
		puts("-1");
		return 0;	
	}
	printf("%d\n",m);
	range(i,1,n) printf("%d%c",g[i]," \n"[i==n]);
	range(i,1,m) printf("%d%c",h[i]," \n"[i==m]);
	return 0;
}
