#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

const int MAX = 300000 + 1000;
int n,k,d;
vi E[MAX];
vi toDelete;
int fr[MAX],to[MAX];
int dist[MAX];
int P[MAX];



int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d %d",&n,&k,&d);
	queue<int> q;
	memset(dist,-1,sizeof dist);
	vi Q;
	loop(i,k){
		int x; scanf("%d",&x);
		Q.pb(x);
	}
	sort(all(Q));
	Q.resize(unique(all(Q)) - Q.begin());
	for(int x : Q){
		q.push(x);
		dist[x] = 0;
	}

	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b);
		fr[i] = a;
		to[i] = b;
		E[a].pb(i);
		E[b].pb(i);
	}

	while(!q.empty()){
		int u = q.front(); q.pop();
		if(dist[u] == d) continue;
		for(int e : E[u]){
			int v = fr[e] + to[e] - u;
			if(dist[v] != -1) {
				if(P[u] == v) continue;
				toDelete.pb(e);
				continue;
			}
			P[v] = u;
			q.push(v);
			dist[v] = dist[u] + 1;
		}
	}
	sort(all(toDelete));
	toDelete.resize(unique(all(toDelete)) - toDelete.begin());
	printf("%d\n",sz(toDelete));
	if(!toDelete.empty()){
		for(int x : toDelete) printf("%d ",x + 1);
		puts("");
	}
	return 0;
}
