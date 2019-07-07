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

int A[1 << 20],n;

vector<vi> get_cand(int k,int v) {
	int l = 2*k,r = l+1;
	int mn = INT_MAX;
	vector<vi> cands {
		{v,A[l],A[r]},
		{A[l],v,A[r]},
		{A[r],A[l],v},
		{A[r],v,A[l]}};
	for(auto V : cands)
		mn = min(mn,V[0]);
	vector<vi> ret;
	for(auto V : cands)
		if (V[0] == mn)
			ret.push_back(V);
	return ret;
}

int bt(int cur,int depth,int v,bool save) {
	if(depth == 0 || 2*cur > n) return v;
	int l = 2*cur,r = l+1;

	vector<vi> cands = get_cand(cur,v);
	int mn = cands[0][0];
	if(save)
		A[cur] = mn;


	pi best(INT_MAX,INT_MAX);
	for(vi cand : cands) {
		int a = bt(l,depth-1,cand[1],0);
		int b = bt(r,depth-1,cand[2],0);
		pi tmp (a,b);
		if(tmp < best) {
			best = tmp;
			if(save) {
				A[l] = cand[1];
				A[r] = cand[2];
			}
		}
	}



	return mn;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	range(i,1,n) scanf("%d",A + i);
	A[n+1] = INT_MAX;
	for(int k = 1;k <= n/2;k++){
		bt(k,2,A[k],1);

	}
	range(i,1,n) printf("%d%c",A[i]," \n"[i==n]);
	return 0;
}
