#pragma GCC optimize("O3")
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

const int MAX = 1e5 + 1e2,MAX_BLK = 1000;
int A[MAX],n,blkSize;
int f[MAX_BLK][60];
int ST[MAX << 2][60];

void build(int node,int s,int e){
	if(s == e){
		loop(t,60) ST[node][t] = 1 + (t%A[s] == 0);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	loop(t,60) ST[node][t] = ST[left][t] + ST[right][(t + ST[left][t])%60];
}

void update(int node,int s,int e,int p,int v){
	if(s == e){
		A[s] = v;
		loop(t,60) ST[node][t] = 1 + (t%A[s] == 0);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	loop(t,60) ST[node][t] = ST[left][t] + ST[right][(t + ST[left][t])%60];
}

int query(int node,int s,int e,int l,int r,int t){
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(s < l){
		if(r <= m) return query(left,s,m,l,r,t);
		if(m < l) return query(right,m+1,e,l,r,t);
		int ret = query(left,s,m,l,m,t);
		return ret + query(right,m+1,e,m+1,r,(ret + t)%60);
	}
	else{
		assert(s == l);
		if(e == r) return ST[node][t];
		if(r <= m) return query(left,s,m,l,r,t);
		int ret = ST[left][t];
		return ret + query(right,m+1,e,m+1,r,(ret + t)%60);
	}
}





int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	build(1,0,n-1);	

	int m; scanf("%d",&m);
	while(m--){
		char c; int a,b;
		scanf(" %c %d %d",&c,&a,&b);
		if(c == 'A'){
			a--,b--; b--;
			printf("%d\n",query(1,0,n-1,a,b,0));
		}
		else{
			a--;
			A[a] = b;
			update(1,0,n-1,a,b);
		}
	}
	
	return 0;
}

