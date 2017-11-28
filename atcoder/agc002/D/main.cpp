#pragma GCC optimize ("O3")
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
#define popcnt(x) __builtin_popcountll(x)
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

const int MAX = 100*1000 + 10;
int fr[MAX],to[MAX];
vi E[MAX];
int n,m,q;
int id[MAX],W[MAX],changeTime[MAX];
map<int,int> snapeShot[MAX];

int find(int a) {
	while(id[a] != a) a = id[a];
	return a;
}

void join(int a,int b,int e){
	a = find(a),b = find(b);
	if(a == b) return;
	if(W[a] < W[b]) swap(a,b);
	id[b] = a;
	W[a] += W[b];
	changeTime[b] = e;
	snapeShot[a][e] = W[a];
}


bool can(int ti,int x,int y,int z) {
	while(x != id[x] && changeTime[x] <= ti) x = id[x];
	while(y != id[y] && changeTime[y] <= ti) y = id[y];
	auto p = snapeShot[x].upper_bound(ti);
	auto q = snapeShot[y].upper_bound(ti);
	--p,--q;
	if(x == y) return p->yy >= z;
	else return p->yy + q->yy >= z;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(e,1,m) {
		scanf("%d %d",fr + e,to + e);
		E[fr[e]].pb(e);
		E[to[e]].pb(e);
	}
	range(i,1,n) id[i] = i,W[i] = 1,snapeShot[i][0] = 1;

	range(e,1,m) join(fr[e],to[e],e);

	scanf("%d",&q);
	loop(i,q) {
		int x,y,z; scanf("%d %d %d",&x,&y,&z);
		int s = 1,e = m;
		while(s < e) {
			int mid = (s + e) >> 1;
			if(can(mid,x,y,z)) e = mid;
			else s = mid + 1;
		}
		printf("%d\n",s);
	}

	return 0;
}
