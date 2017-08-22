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

const int MAX = 100*1000 + 10,BlkSize = 320,num_blks = MAX/BlkSize + 5,oo = 1 << 29;
int n,m;
ll A[MAX],offset[num_blks];
int nxt[MAX],jump[MAX],nxtJ[MAX];
vector<pair<ll,int> > aux;

void build(int l,int r,int lc,int rc,bool debug = 0){
	for(;r >= l;r--) {
		ll val = A[r] + offset[r/BlkSize];
		while(!aux.empty() && aux.back().xx <= val) aux.pop_back();
		if(!aux.empty() && aux.back().yy - r > 100) aux.clear();
		if(lc <= r && r <= rc){
			if(aux.empty()){
				nxt[r] = -1;
				nxtJ[r] = -1;
				jump[r] = oo;
			}
			else {
				nxt[r] = aux.back().yy;
				if(r/BlkSize == nxt[r]/BlkSize) {
					nxtJ[r] = nxtJ[nxt[r]];
					jump[r] = jump[nxt[r]] + 1;
				}
				else {
					nxtJ[r] = nxt[r];
					jump[r] = 1;
				}
			}
		}
		if(debug) {
			for(auto p : aux) {
				prp(p);
			}
			cerr << endl;
			cerr << "val[" << r << "] = " << val << " nxt[" << r << "] = " << nxt[r] << endl;
		}
		aux.pb(mp(val,r));
	}
	aux.clear();
}

void pook(){
	cerr << "A: ";
	for(int i = 0;i < n;i++)
		cerr << A[i] + offset[i/BlkSize] << " ";
	cerr << endl;
	prArr(nxt,n,int);
	prArr(nxtJ,n,int);
	prArr(jump,n,int);
	cerr << "==========================================" << endl;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	aux.reserve(BlkSize);
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%lld",A + i);
	build(0,n-1,0,n-1);
//	pook();

	while(m--) {
		int type; scanf("%d",&type);
		if(type == 1) {
			int cur,k; scanf("%d %d",&cur,&k);
			cur --;
			while(k && nxt[cur] != -1) {
				if(jump[cur] <= k) {
					k -= jump[cur];
					cur = nxtJ[cur];
				}
				else {
					k--;
					cur = nxt[cur];
				}
			}
			printf("%d\n",cur + 1);
		}
		else {
			int l,r,x; scanf("%d %d %d",&l,&r,&x); l--,r--;
			int u = l/BlkSize,v = r/BlkSize;
			if(u == v) {
				for(int i = l;i <= r;i++) A[i] += x;
				l = max(0,l - 100);
				r = min(n-1,r + 100);
				build((max(0,l-100)/BlkSize)*BlkSize,min(n-1,r+100),(max(0,l-100)/BlkSize)*BlkSize,r);
			}
			else {
				for(int t = u + 1;t < v;t++) offset[t] += x;
				for(int i = l;i < (u + 1)*BlkSize;i++) A[i] += x;
				for(int i = v*BlkSize;i <= r;i++) A[i] += x;
				build((max(0,r-100)/BlkSize)*BlkSize,min(n-1,r+100),(max(0,r-100)/BlkSize)*BlkSize,r);
				build((max(0,l-100)/BlkSize)*BlkSize,min(n-1,l+100),(max(0,l-100)/BlkSize)*BlkSize,l);
			}
//			pook();
		}
	}
	return 0;
}
