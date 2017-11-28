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


vp P,C,U,L;
int m,n;

ll f(int x,int y){
	return max(0LL,U[y].xx - L[x].xx + 0LL)*(U[y].yy - L[x].yy);
}

ll solve(int s,int e,int l,int r){
	if(s > e) return 0;
	int m = (s + e) >> 1;
	ll best = 0;
	int bestk = l;
	for(int k = l;k <= r;k++){
		ll tmp = f(m,k);
		if(tmp >= best){
			best = tmp;
			bestk = k;
		}
	}
	ll ret = best;
	ret = max(ret,solve(s,m-1,l,bestk));
	ret = max(ret,solve(m+1,e,bestk,r));
	return ret;
}


int main(){
	scanf("%d %d",&m,&n);
	P.resize(m);
	C.resize(n);

	loop(i,m) scanf("%d %d",&P[i].yy,&P[i].xx);
	loop(i,n) scanf("%d %d",&C[i].yy,&C[i].xx);

	sort(all(P));
	sort(all(C));

	for(auto p : P){
		if(L.empty() || !(L.back().xx <= p.xx && L.back().yy <= p.yy)) L.pb(p);
	}
	for(auto p : C){
		while(!U.empty()  && (U.back().xx <= p.xx && U.back().yy <= p.yy)) U.pop_back();
		U.pb(p);
	}
	cout << solve(0,sz(L)-1,0,sz(U)-1);
}
