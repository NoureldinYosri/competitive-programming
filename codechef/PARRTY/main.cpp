#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 2*200*1000 + 10,DEPTH = 5,BLKSIZE = 230;

int T,N,M,Q;
int ST[MAX],EN[MAX];
vp I;
vi Hate[MAX];
vi LeftMate;
vi blks[(MAX + BLKSIZE - 1)/BLKSIZE + 1];
int blkSize;


void transform(){
	LeftMate.clear();
	map<int,int> M;
	for(int i = 1;i <= N;i++) {
		ST[i] = LeftMate.size();
		for(int h : Hate[i]){
			int v = -1;
			if(M.count(h)) v = M[h];
			M[h] = sz(LeftMate);
			LeftMate.push_back(v);
		}
		EN[i] = sz(LeftMate)-1;
	}
}

void build(){
	int n = sz(LeftMate);
//	blkSize = sqrt(n);
	blkSize = BLKSIZE;
	int m = (n-1+blkSize-1)/blkSize + 1;
	loop(i,m) blks[i].clear();
	for(int i = 0;i < n;i++)
		blks[i/blkSize].push_back(LeftMate[i]);
	loop(i,m) sort(all(blks[i]));
}

void canonize(){
	static vp aux;
	aux.clear();
	sort(all(I));
	int s = -1,e = -2;
	for(auto p : I) {
		if(p.xx <= e+1)
			e = max(e,p.yy);
		else {
			if(s != -1) aux.emplace_back(s,e);
			s = p.xx;
			e = p.yy;
		}
	}
	if(s != -1) aux.emplace_back(s,e);
	I.swap(aux);
}



bool solve(){
	static vi leftOver,candBlks;
	leftOver.clear();
	candBlks.clear();
	for(auto p : I){
		int s = p.xx,e = p.yy;
		int u = s/blkSize,v = e/blkSize;
		if(u == v) {
			for(;s <= e;s++) {
				if(LeftMate[s] != -1)
					leftOver.pb(LeftMate[s]);
			}
		}
		else {
			for(int i = s,L = (u+1)*blkSize;i < L;i++) {
				if(LeftMate[i] != -1)
					leftOver.pb(LeftMate[i]);
			}
			for(int i = v*blkSize;i <= e;i++) {
				if(LeftMate[i] != -1)
					leftOver.pb(LeftMate[i]);
			}
			for(++u;u < v;u++)
				candBlks.push_back(u);
		}
	}
	sort(all(leftOver));
	int i = 0;
	for(auto p : I) {
		while(i < sz(leftOver) && leftOver[i] < p.xx) i++;
		if(i == sz(leftOver)) break;
		if(leftOver[i] <= p.yy) return 1;
	}
	for(int u : candBlks) {
		vi & V = blks[u];
		auto ptr = V.begin();
		for(auto p : I) {
			ptr = lower_bound(ptr,V.end(),p.xx);
			if(ptr == V.end()) break;
			if(*ptr <= p.yy) return 1;
		}
	}

	return 0;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&N,&M);
		loop(i,N+1) Hate[i].clear();
		loop(i,M) {
			int a,b;
			scanf("%d %d",&a,&b);
			Hate[a].pb(i);
			Hate[b].pb(i);
		}
		transform();
		build();
		scanf("%d",&Q);
		loop(i,Q) {
			I.clear();
			int m; scanf("%d",&m);
			loop(j,m) {
				int l,r;
				scanf("%d %d",&l,&r);
				l = ST[l];
				r = EN[r];
				if(r < l) continue;
				I.emplace_back(l,r);
			}
			canonize();
			puts(solve() ? "NO" : "YES");
		}
	}
	return 0;
}
