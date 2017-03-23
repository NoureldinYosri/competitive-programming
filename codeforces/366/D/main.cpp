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

int f[1001][6000];
int n,m,k;
int fr[3000],to[3000],L[3000],R[3000],aux[6000];
vi E[1001];

int work(int l){
	PQ<pi> pq;
	f[1][l] = INT_MAX; pq.push(mp(f[1][l],1));
	while(!pq.empty()){
		int u = pq.top().yy;
		int d = pq.top().xx;
		pq.pop();
		if(d != f[u][l]) continue;
		for(int e : E[u]){
			int v = fr[e] + to[e] - u;
			d = min(f[u][l],R[e]);
			if(L[e] <= l && l <= R[e] && d > f[v][l]){
				f[v][l] = d;
				pq.push(mp(d,v));
			}
		}
	}
	return f[n][l];
}

int main(){
	scanf("%d %d",&n,&m);
	loop(e,m){
		scanf("%d %d %d %d",fr + e,to + e,L + e,R + e);
		aux[k++] = L[e];
		aux[k++] = R[e];
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	sort(aux,aux + k);
	k = unique(aux,aux + k) - aux;
	loop(e,m){
		L[e] = lower_bound(aux,aux + k,L[e]) - aux;
		R[e] = lower_bound(aux,aux + k,R[e]) - aux;
	}
	memset(f,-1,sizeof f);
	int ans = 0;
	loop(v,k){
		int r = work(v),l = v;
		if(r < v) continue;
		l = aux[l],r = aux[r];
		ans = max(ans,r - l + 1);
	}
	if(!ans){
		puts("Nice work, Dima!");
		return 0;
	}
	cout << ans << endl;
//	cerr << ans << endl;
	
	return 0;
}
