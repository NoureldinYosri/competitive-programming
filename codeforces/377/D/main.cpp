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

typedef pair<pi,int> event;
struct st_node{
	int siz;
	int best_r,best_val;
	vi BIT,aux;
	void compress(){
		sort(all(aux));
		aux.resize(unique(all(aux)) - aux.begin());
		BIT = vi(sz(aux),0);
	}
	void add(int p,int v) {
		for(++p;p <= sz(BIT);p += LSOne(p))
			BIT[p - 1] += v;
	}

	int get(int p,vi & BIT) {
		int ret = 0;
		for(++p;p;p ^= LSOne(p))  ret += BIT[p - 1];
		return ret;
	}
	void update(int p,int v) {
		siz += v;
		int idx = lower_bound(all(aux),p) - aux.begin();
		update(idx,v);
	}
};


const int MAX = 300*1000 + 10,MAXV = 300*1000;
int n;
int L[MAX],V[MAX],R[MAX];
int left_pos[MAX];
st_node ST[4*MAX];
event E[2*MAX];


void read_input(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d %d",L + i,V + i,R + i);
}

void preprocess(){
	loop(i,n) {
		E[2*i] = mp(mp(L[i],-1),i);
		E[2*i + 1] = mp(mp(R[i],1),i);
	}
	loop(i,n) if(E[i].xx.yy == -1) left_pos[E[i].yy] = i;
}


void sim_insert(int node,int s,int e,int p,int v) {
	ST[node].aux.pb(v);
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) sim_insert(left,s,m,p,v);
	else sim_insert(right,m+1,e,p,v);
}

void traverse(int node,int s,int e) {
	ST[node].compress();
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	traverse(left,s,m);
	traverse(right,m+1,e);
}

void simulate(){
	loop(i,2*n) {
		if(E[i].xx.yy == -1 ){
			int who = E[i].yy;
			sim_insert(1,1,MAXV,R[who],V[who]);
		}
	}
	traverse(1,1,MAX);
}


void update(int node,int s,int e,int p,int v) {
	ST[node].update(p,v);
	if(s == e ){
		ST[node].best_r = s;
		ST[node].best_val = ST[node].siz;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);

	if(ST[left].best_val > ST[right])
}

void solve(){
	for(int i = 0;i < 2*n;i++){

	}
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	read_input();
	preprocess();
	simulate();
	solve();
	return 0;
}
